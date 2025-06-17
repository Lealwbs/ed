#include "../include/simulacao.hpp"
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>

// Construtor: inicializa parâmetros e estruturas básicas
Simulacao::Simulacao(int cap_transporte, int lat_transporte, int int_transportes, 
                     int cst_remocao, int num_armazens, int** matriz_adjacencia) {
    this->capacidade_transporte = cap_transporte;
    this->latencia_transporte = lat_transporte;
    this->intervalo_transportes = int_transportes;
    this->custo_remocao = cst_remocao;
    this->numero_armazens = num_armazens;
    
    // Inicialização das estruturas
    this->rede_armazens = new GrafoRede(numero_armazens);
    this->lista_armazens = new Armazem*[numero_armazens];
    this->escalonador_eventos = new HeapEscalonador();
    this->historico_eventos = new Lista();
    
    // Controle inicial
    this->tempo_atual = 0.0;
    this->pacotes_pendentes = 0;
    this->todos_pacotes = nullptr;
    this->total_pacotes = 0;
    
    // Constrói a rede de armazéns baseada na matriz de adjacência
    for (int i = 0; i < numero_armazens; i++) {
        for (int j = 0; j < numero_armazens; j++) {
            if (matriz_adjacencia[i][j] == 1) {
                rede_armazens->AdicionarAresta(i, j);
            }
        }
    }
    
    CriarArmazens();
}

// Destrutor: libera toda memória alocada
Simulacao::~Simulacao() {
    delete rede_armazens;
    delete escalonador_eventos;
    delete historico_eventos;
    
    // Libera armazéns
    if (lista_armazens != nullptr) {
        for (int i = 0; i < numero_armazens; i++) {
            delete lista_armazens[i];
        }
        delete[] lista_armazens;
    }
    
    // Libera todos os pacotes criados
    if (todos_pacotes != nullptr) {
        for (int i = 0; i < total_pacotes; i++) {
            delete todos_pacotes[i];
        }
        delete[] todos_pacotes;
    }
}

// Cria instâncias dos armazéns da simulação
void Simulacao::CriarArmazens() {
    for (int i = 0; i < numero_armazens; i++) {
        lista_armazens[i] = new Armazem(i, numero_armazens);
    }
}

// Adiciona um pacote à simulação
void Simulacao::AdicionarPacote(Pacote* novo_pacote) {
    // Realoca array se necessário
    if (todos_pacotes == nullptr) {
        todos_pacotes = new Pacote*[1];
        total_pacotes = 0;
    } else {
        Pacote** temp = new Pacote*[total_pacotes + 1];
        for (int i = 0; i < total_pacotes; i++) {
            temp[i] = todos_pacotes[i];
        }
        delete[] todos_pacotes;
        todos_pacotes = temp;
    }
    
    todos_pacotes[total_pacotes] = novo_pacote;
    total_pacotes++;
    pacotes_pendentes++;
}

// Finaliza configuração e prepara simulação
void Simulacao::FinalizarConfiguracao() {
    CalcularRotasPacotes();
    
    // Agenda eventos iniciais de chegada dos pacotes
    for (int i = 0; i < total_pacotes; i++) {
        Pacote* p = todos_pacotes[i];
        p->SetEstado(Pacote::Chegada_Escalonada);
        
        // Cria evento de chegada usando a classe especializada
        EventoChegada* evento_chegada = new EventoChegada(
            p->GetTempoChegada(), 
            p, 
            p->GetArmazemInicial()
        );
        
        escalonador_eventos->InserirEvento(evento_chegada);
    }
}

// Calcula rotas para todos os pacotes usando algoritmo de caminho mínimo
void Simulacao::CalcularRotasPacotes() {
    for (int i = 0; i < total_pacotes; i++) {
        Pacote* p = todos_pacotes[i];
        Lista* rota = rede_armazens->GetRota(*rede_armazens, p->GetArmazemInicial(), 
                                            p->GetArmazemFinal());
        p->SetRota(rota);
    }
}

// Método principal que executa toda a simulação
void Simulacao::ExecutarSimulacao() {
    bool primeiro_pacote_processado = false;
    
    // Loop principal da simulação
    while (!escalonador_eventos->Vazio() && pacotes_pendentes > 0) {
        Evento* proximo_evento = escalonador_eventos->ExtrairEvento();
        
        // Inicializa transportes no tempo do primeiro pacote
        if (!primeiro_pacote_processado && proximo_evento->GetTipo() == Evento::Chegada) {
            IniciarTransportesAutomaticos(proximo_evento->GetTempo());
            primeiro_pacote_processado = true;
        }
        
        // Atualiza relógio da simulação
        if (proximo_evento->GetTempo() > tempo_atual) {
            tempo_atual = proximo_evento->GetTempo();
        }
        
        // Processa evento baseado no tipo
        switch (proximo_evento->GetTipo()) {
            case Evento::Chegada:
                ProcessarEventoChegada(proximo_evento);
                break;
            case Evento::Transporte:
                ProcessarEventoTransporte(proximo_evento);
                break;
        }
        
        delete proximo_evento;
    }
}

// Inicia os transportes automáticos periódicos
void Simulacao::IniciarTransportesAutomaticos(double tempo_inicial) {
    for (int i = 0; i < numero_armazens; i++) {
        Lista* vizinhos = rede_armazens->GetVizinhos(i);
        
        // Percorre vizinhos usando a estrutura de lista
        NodeLista* current = vizinhos->GetHead();
        
        while (current != nullptr) {
            if (current->tipo == tipo_inteiro) {
                int vizinho_id = current->valor;
                
                // Evita duplicação de rotas usando comparação de índices
                if (i < vizinho_id) {
                    // Agenda transporte i -> vizinho_id
                    EventoTransporte* transporte_ida = new EventoTransporte(
                        tempo_inicial + intervalo_transportes,
                        i,
                        vizinho_id
                    );
                    escalonador_eventos->InserirEvento(transporte_ida);
                    
                    // Agenda transporte vizinho_id -> i
                    EventoTransporte* transporte_volta = new EventoTransporte(
                        tempo_inicial + intervalo_transportes,
                        vizinho_id,
                        i
                    );
                    escalonador_eventos->InserirEvento(transporte_volta);
                }
            }
            current = current->proximo;
        }
    }
}

// Processa evento de chegada de pacote em armazém
void Simulacao::ProcessarEventoChegada(Evento* evento) {
    // Faz cast para EventoChegada para acessar os dados específicos
    EventoChegada* evento_chegada = static_cast<EventoChegada*>(evento);
    Pacote* pacote = evento_chegada->GetPacote();
    int armazem_atual = evento_chegada->GetArmazemChegada();
    
    // Verifica se chegou ao destino final
    if (armazem_atual == pacote->GetArmazemFinal()) {
        pacote->SetEstado(Pacote::Entregue);
        std::string id_formatado = FormatarIdentificadorString(armazem_atual, 3);
        RegistrarEvento(evento->GetTempo(), pacote->GetIdPacote(), 
                       "entregue em " + id_formatado);
        pacotes_pendentes--;
        
    } else {
        // Armazena pacote na seção apropriada
        Secao* secao_destino = lista_armazens[armazem_atual]->GetSecaoByDestino(pacote->GetProximoSalto());
        secao_destino->EmpilharPacote(pacote);
        
        std::string id_atual = FormatarIdentificadorString(armazem_atual, 3);
        std::string id_proximo = FormatarIdentificadorString(pacote->GetProximoSalto(), 3);
        RegistrarEvento(evento->GetTempo(), pacote->GetIdPacote(), 
                       "armazenado em " + id_atual + " na secao " + id_proximo);
    }
}

// Processa evento de transporte automático
void Simulacao::ProcessarEventoTransporte(Evento* evento) {
    // Faz cast para EventoTransporte para acessar os dados específicos
    EventoTransporte* evento_transporte = static_cast<EventoTransporte*>(evento);
    int origem = evento_transporte->GetArmazemOrigem();
    int destino = evento_transporte->GetArmazemDestino();
    
    // Reagenda próximo transporte nesta rota
    EventoTransporte* proximo_transporte = new EventoTransporte(
        tempo_atual + intervalo_transportes,
        origem,
        destino
    );
    escalonador_eventos->InserirEvento(proximo_transporte);
    
    // Executa a transferência de pacotes
    ExecutarTransferenciaArmazem(origem, destino, tempo_atual);
}

// Executa transferência de pacotes entre armazéns
void Simulacao::ExecutarTransferenciaArmazem(int origem, int destino, double momento) {
    Secao* secao = lista_armazens[origem]->GetSecaoByDestino(destino);
    
    if (secao == nullptr || secao->Vazia()) {
        return; // Nenhum pacote para transportar
    }
    
    // Obtém quantidade de pacotes na seção
    int total_pacotes_secao = secao->GetTamanho();
    
    // Calcula quantos pacotes transportar
    int pacotes_a_transportar = (total_pacotes_secao < capacidade_transporte) ? 
                                total_pacotes_secao : capacidade_transporte;
    
    // Array para armazenar pacotes que serão transportados
    Pacote** pacotes_selecionados = new Pacote*[pacotes_a_transportar];
    
    double tempo_operacao = momento;
    Secao pilha_temporaria;
    
    std::string id_origem = FormatarIdentificadorString(origem, 3);
    std::string id_destino = FormatarIdentificadorString(destino, 3);
    
    // FASE 1: Remove pacotes da seção e seleciona os que serão transportados (FIFO)
    int contador_selecionados = 0;
    while (!secao->Vazia() && contador_selecionados < pacotes_a_transportar) {
        Pacote* pacote_topo = secao->DesempilharPacote();
        tempo_operacao += custo_remocao;
        
        RegistrarEvento(tempo_operacao, pacote_topo->GetIdPacote(), 
                       "removido de " + id_origem + " na secao " + id_destino);
        
        // Seleciona para transporte (FIFO - os primeiros removidos são transportados)
        pacotes_selecionados[contador_selecionados] = pacote_topo;
        contador_selecionados++;
    }
    
    // Remove os pacotes restantes temporariamente
    while (!secao->Vazia()) {
        Pacote* pacote_topo = secao->DesempilharPacote();
        tempo_operacao += custo_remocao;
        
        RegistrarEvento(tempo_operacao, pacote_topo->GetIdPacote(), 
                       "removido de " + id_origem + " na secao " + id_destino);
        
        pilha_temporaria.EmpilharPacote(pacote_topo);
    }
    
    // FASE 2: Processa pacotes selecionados para transporte
    for (int i = 0; i < pacotes_a_transportar; i++) {
        Pacote* pacote = pacotes_selecionados[i];
        pacote->AvancarRota();
        pacote->SetEstado(Pacote::Armazenado);
        
        RegistrarEvento(tempo_operacao, pacote->GetIdPacote(), 
                       "em transito de " + id_origem + " para " + id_destino);
        
        // Agenda chegada no destino usando EventoChegada
        EventoChegada* evento_chegada = new EventoChegada(
            tempo_operacao + latencia_transporte,
            pacote,
            destino
        );
        escalonador_eventos->InserirEvento(evento_chegada);
    }
    
    // FASE 3: Reempilha pacotes não transportados
    while (!pilha_temporaria.Vazia()) {
        Pacote* pacote_rearmazenar = pilha_temporaria.DesempilharPacote();
        secao->EmpilharPacote(pacote_rearmazenar);
        RegistrarEvento(tempo_operacao, pacote_rearmazenar->GetIdPacote(), 
                       "rearmazenado em " + id_origem + " na secao " + id_destino);
    }
    
    // Limpa memória temporária
    delete[] pacotes_selecionados;
}

// Registra evento no histórico para posterior exibição
void Simulacao::RegistrarEvento(double tempo, int id_pacote, const std::string& descricao) {
    std::ostringstream oss;
    std::string id_pacote_formatado = FormatarIdentificadorString(id_pacote, 3);
    
    // Formata tempo como inteiro arredondado com 7 dígitos
    oss << std::setfill('0') << std::setw(7) << static_cast<int>(round(tempo)) 
        << " pacote " << id_pacote_formatado << " " << descricao;
    
    // Adiciona como texto na lista ao invés de inteiro
    historico_eventos->AdicionarTexto(oss.str());
}

// Formata identificador numérico com zeros à esquerda
std::string Simulacao::FormatarIdentificadorString(int id, int tamanho) {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(tamanho) << id;
    return oss.str();
}

// Exibe todos os resultados da simulação
void Simulacao::ExibirResultados() {
    historico_eventos->Imprimir();
}