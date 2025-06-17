#include "../include/simulacao.hpp"
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>

// Construtor - inicializa todos os parâmetros e estruturas
Simulacao::Simulacao(int capacidade_transporte, 
                     int latencia_transporte, 
                     int intervalo_transportes, 
                     int custo_remocao, 
                     int numero_armazens, 
                     int** matriz_adjacencia,
                     int numero_pacotes) {
    
    this->capacidade_transporte = capacidade_transporte;
    this->latencia_transporte = latencia_transporte;
    this->intervalo_transportes = intervalo_transportes;
    this->custo_remocao = custo_remocao;
    this->numero_armazens = numero_armazens;
    this->numero_pacotes = numero_pacotes;
    
    // Inicializa estruturas principais
    this->rede_armazens = new GrafoRede(numero_armazens);
    this->lista_armazens = new Armazem*[numero_armazens];
    this->escalonador_eventos = new HeapEscalonador();
    this->historico_eventos = new Lista();
    this->todos_pacotes = new Pacote*[numero_pacotes];
    
    // Inicializa armazéns
    for (int i = 0; i < numero_armazens; i++) {
        lista_armazens[i] = new Armazem(i, numero_armazens);
    }
    
    // Constrói o grafo da rede a partir da matriz de adjacência
    for (int i = 0; i < numero_armazens; i++) {
        for (int j = 0; j < numero_armazens; j++) {
            if (matriz_adjacencia[i][j] == 1) {
                rede_armazens->AdicionarAresta(i, j);
            }
        }
    }
    
    // Inicializa controles da simulação
    this->tempo_atual = 0.0;
    this->pacotes_pendentes = 0;
    
    std::cout << "SUCCESS: Simulacao construtor" << std::endl;
}

// Destrutor - libera toda a memória alocada
Simulacao::~Simulacao() {
    LimparMemoria();
}

// Adiciona um pacote à simulação
void Simulacao::AdicionarPacote(double tempo_chegada, int id_pacote, int armazem_inicial, int armazem_final) {
    // Cria o pacote
    Pacote* novo_pacote = new Pacote(tempo_chegada, id_pacote, armazem_inicial, armazem_final);
    
    // Calcula a rota usando BFS no grafo
    Lista* rota = rede_armazens->GetRota(*rede_armazens, armazem_inicial, armazem_final);
    novo_pacote->SetRota(rota);
    novo_pacote->SetEstado(Pacote::Chegada_Escalonada);
    
    // Armazena o pacote no array
    todos_pacotes[pacotes_pendentes] = novo_pacote;
    pacotes_pendentes++;
    
    // Cria evento de chegada inicial
    EventoChegada* evento_chegada = new EventoChegada(tempo_chegada, novo_pacote, armazem_inicial);
    escalonador_eventos->InserirEvento(evento_chegada);
    std::cout << "SUCCESS: Pacote adicionado" << std::endl;
}

// Prepara a simulação (inicializa transportes)
void Simulacao::PrepararSimulacao() {

    std::cout << "Preparando Simulacao..." << std::endl;
    // Encontra o tempo do primeiro evento para iniciar os transportes
    double tempo_inicial = 0.0;
    if (!escalonador_eventos->Vazio()) {
        // Como não temos method para "espiar" o próximo evento sem removê-lo,
        // vamos usar o tempo do primeiro pacote adicionado
        if (pacotes_pendentes > 0) {
            tempo_inicial = todos_pacotes[0]->GetTempoChegada();
        }
    }
    
    std::cout << "SUCCESS: Preparar Simulacao" << std::endl;
    IniciarTransportes(tempo_inicial);
    std::cout << "SUCCESS: Transportes Iniciados" << std::endl;
}


// Executa a simulação principal
void Simulacao::ExecutarSimulacao() {
    bool primeiro_pacote_processado = false;

    std::cout << "SUCCESS: ExecutarSimulacao v0" << std::endl;

    // Loop principal da simulação
    while (!escalonador_eventos->Vazio() && pacotes_pendentes > 0) {
        // Remove o próximo evento
        Evento* proximo_evento = escalonador_eventos->ExtrairEvento();
        
        std::cout << "SUCCESS: Qtde pacotes pendentes: " << pacotes_pendentes << std::endl;

        // Lógica para inicializar os transportes a partir do tempo do primeiro evento de pacote
        if (!primeiro_pacote_processado && proximo_evento->GetTipo() == Evento::Chegada) {
            double tempo_primeiro_pacote = proximo_evento->GetTempo();
            IniciarTransportes(tempo_primeiro_pacote);
            primeiro_pacote_processado = true;
        }
        
        // Atualiza o tempo atual
        if (proximo_evento->GetTempo() > tempo_atual) {
            tempo_atual = proximo_evento->GetTempo();
        }
        
        // Processa o evento baseado no tipo
        if (proximo_evento->GetTipo() == Evento::Chegada) {
            ProcessarEventoChegada(static_cast<EventoChegada*>(proximo_evento));
        }
        else if (proximo_evento->GetTipo() == Evento::Transporte) {
            ProcessarEventoTransporte(static_cast<EventoTransporte*>(proximo_evento));
        }
        
        // Libera memória do evento processado
        delete proximo_evento;
    }
    
    // Imprime o histórico de eventos
    ImprimirHistoricoEventos();
}

// Inicializa os eventos de transporte
void Simulacao::IniciarTransportes(double tempo_inicial) {
    for (int i = 0; i < numero_armazens; i++) {
        Lista* vizinhos = rede_armazens->GetVizinhos(i);
        
        // Percorre os vizinhos do armazém i
        NodeLista* atual = vizinhos->GetHead();
        while (atual != nullptr) {
            int vizinho_id = atual->valor;
            
            // Evita duplicação de rotas (i < vizinho_id)
            if (i < vizinho_id) {
                // Cria eventos de transporte para ambas as direções
                EventoTransporte* evento_ida = new EventoTransporte(
                    tempo_inicial + intervalo_transportes, i, vizinho_id);
                escalonador_eventos->InserirEvento(evento_ida);
                
                EventoTransporte* evento_volta = new EventoTransporte(
                    tempo_inicial + intervalo_transportes, vizinho_id, i);
                escalonador_eventos->InserirEvento(evento_volta);
            }
            
            atual = atual->proximo;
        }
    }
}

// Processa evento de chegada de pacote
void Simulacao::ProcessarEventoChegada(EventoChegada* evento) {
    Pacote* pacote = evento->GetPacote();
    int armazem_id = evento->GetArmazemChegada();
    
    // Verifica se chegou ao destino final
    if (armazem_id == pacote->GetArmazemFinal()) {
        // Pacote entregue
        pacote->SetEstado(Pacote::Entregue);
        pacotes_pendentes--;
        
        std::string mensagem = "entregue em " + FormatarIdentificadorString(armazem_id, 3);
        RegistrarEvento(evento->GetTempo(), pacote->GetIdPacote(), mensagem);
    }
    else {
        // Armazena o pacote na seção apropriada
        lista_armazens[armazem_id]->AddPacote(pacote);
        pacote->SetEstado(Pacote::Armazenado);
        
        std::string mensagem = "armazenado em " + FormatarIdentificadorString(armazem_id, 3) + 
                              " na secao " + FormatarIdentificadorString(pacote->GetProximoSalto(), 3);
        RegistrarEvento(evento->GetTempo(), pacote->GetIdPacote(), mensagem);
    }
}

void Simulacao::ProcessarEventoTransporte(EventoTransporte* evento) {
    if (pacotes_pendentes == 0) return;
    int origem_id = evento->GetArmazemOrigem();
    int destino_id = evento->GetArmazemDestino();

    // Agenda o próximo transporte nesta rota
    EventoTransporte* proximo_transporte = new EventoTransporte(
        tempo_atual + intervalo_transportes, origem_id, destino_id);
    escalonador_eventos->InserirEvento(proximo_transporte);

    // Obtém a seção correspondente ao destino
    Secao* secao = lista_armazens[origem_id]->GetSecaoByDestino(destino_id);
    if (secao == nullptr || secao->Vazia()) {
        return; // Nenhum pacote para transportar
    }

    int num_pacotes_secao = secao->GetTamanho();
    int pacotes_a_transportar = std::min(num_pacotes_secao, capacidade_transporte);

    // Obtem todos os pacotes da seção em um array
    Pacote** pacotes_na_secao = new Pacote*[num_pacotes_secao];
    for (int i = 0; i < num_pacotes_secao; i++) {
        pacotes_na_secao[i] = secao->DesempilharPacote();
    }

    // Seleciona pacotes FIFO (do fundo do array)
    Pacote** pacotes_selecionados = new Pacote*[pacotes_a_transportar];
    for (int i = 0; i < pacotes_a_transportar; i++) {
        pacotes_selecionados[i] = pacotes_na_secao[num_pacotes_secao - 1 - i];
    }

    double tempo_operacao = tempo_atual;

    // FASE 1: Registrar remoção de todos os pacotes
    for (int i = 0; i < num_pacotes_secao; i++) {
        Pacote* pacote = pacotes_na_secao[i];

        if (pacote->GetEstado() == Pacote::Entregue) {
            continue; // Pula pacotes já entregues
        }

        tempo_operacao += custo_remocao;
        std::string mensagem = "removido de " + FormatarIdentificadorString(origem_id, 3) +
                            " na secao " + FormatarIdentificadorString(destino_id, 3);
        RegistrarEvento(tempo_operacao, pacote->GetIdPacote(), mensagem);
    }

    // FASE 2: Processar pacotes selecionados para transporte
    for (int i = 0; i < pacotes_a_transportar; i++) {
        Pacote* pacote = pacotes_selecionados[i];

        // Verifica se há próximo salto antes de avançar
        if (pacote->GetProximoSalto() == -1) {
            std::cerr << "[ERRO] Pacote " << pacote->GetIdPacote()
                      << " não possui próximo salto antes de transporte. Ignorado." << std::endl;
            continue;
        }

        // Avança a rota
        pacote->AvancarRota();
        pacote->SetEstado(Pacote::Chegada_Escalonada);

        std::string mensagem = "em transito de " + FormatarIdentificadorString(origem_id, 3) +
                               " para " + FormatarIdentificadorString(destino_id, 3);
        RegistrarEvento(tempo_operacao, pacote->GetIdPacote(), mensagem);

        // Agenda chegada no destino
        EventoChegada* evento_chegada = new EventoChegada(
            tempo_operacao + latencia_transporte, pacote, destino_id);
        escalonador_eventos->InserirEvento(evento_chegada);
    }

    // FASE 3: Reempilhar os pacotes não transportados
    for (int i = 0; i < num_pacotes_secao; i++) {
        bool foi_transportado = false;
        for (int j = 0; j < pacotes_a_transportar; j++) {
            if (pacotes_na_secao[i] == pacotes_selecionados[j]) {
                foi_transportado = true;
                break;
            }
        }

        if (!foi_transportado) {
            secao->EmpilharPacote(pacotes_na_secao[i]);
            std::string mensagem = "rearmazenado em " + FormatarIdentificadorString(origem_id, 3) +
                                   " na secao " + FormatarIdentificadorString(destino_id, 3);
            RegistrarEvento(tempo_operacao, pacotes_na_secao[i]->GetIdPacote(), mensagem);
        }
    }

    // Libera memória
    delete[] pacotes_na_secao;
    delete[] pacotes_selecionados;
}


// Registra um evento no histórico
void Simulacao::RegistrarEvento(double tempo, int id_pacote, std::string descricao) {
    char buffer[256];
    std::string id_formatado = FormatarIdentificadorString(id_pacote, 3);
    
    sprintf(buffer, "%07d pacote %s %s", 
            static_cast<int>(round(tempo)), 
            id_formatado.c_str(), 
            descricao.c_str());
    
    historico_eventos->AdicionarTexto(std::string(buffer));
}

// Imprime o histórico de eventos
void Simulacao::ImprimirHistoricoEventos() {
    historico_eventos->Imprimir();
}

// Formata um identificador com zeros à esquerda
std::string Simulacao::FormatarIdentificadorString(int id, int tamanho) {
    char buffer[10];
    sprintf(buffer, "%0*d", tamanho, id);
    return std::string(buffer);
}

// Limpa toda a memória alocada
void Simulacao::LimparMemoria() {
    // Limpa armazéns
    if (lista_armazens != nullptr) {
        for (int i = 0; i < numero_armazens; i++) {
            delete lista_armazens[i];
        }
        delete[] lista_armazens;
    }
    
    // Limpa pacotes
    if (todos_pacotes != nullptr) {
        for (int i = 0; i < numero_pacotes; i++) {
            if (todos_pacotes[i] != nullptr) {
                delete todos_pacotes[i];
            }
        }
        delete[] todos_pacotes;
    }
    
    // Limpa outras estruturas
    delete rede_armazens;
    delete escalonador_eventos;
    delete historico_eventos;
}