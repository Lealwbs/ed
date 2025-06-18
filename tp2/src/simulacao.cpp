#include "../include/simulacao.hpp"
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>

// Construtor: inicializa os parâmetros da simulação e as estruturas de dados.
Simulacao::Simulacao(int capacidade_transporte, 
                     int latencia_transporte, 
                     int intervalo_transportes, 
                     int custo_remocao, 
                     int numero_armazens, 
                     int** matriz_adjacencia,
                     int numero_pacotes) {
    
    // Atribui os parâmetros da simulação
    this->capacidade_transporte = capacidade_transporte;
    this->latencia_transporte = latencia_transporte;
    this->intervalo_transportes = intervalo_transportes;
    this->custo_remocao = custo_remocao;
    this->numero_armazens = numero_armazens;
    this->numero_pacotes = numero_pacotes;
    
    // Inicializa as estruturas de dados principais
    this->rede_armazens = new GrafoRede(numero_armazens);
    this->lista_armazens = new Armazem*[numero_armazens];
    this->escalonador_eventos = new HeapEscalonador(numero_pacotes * 2); // Capacidade inicial
    this->historico_eventos = new Lista();
    this->todos_pacotes = new Pacote*[numero_pacotes];
    
    // Inicializa os armazéns
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
    
    // Inicializa variáveis de controle da simulação
    this->tempo_atual = 0.0;
    this->pacotes_pendentes = 0;
}

// Destrutor: libera toda a memória alocada.
Simulacao::~Simulacao() {
    LimparMemoria();
}

// Adiciona um novo pacote ao sistema e agenda sua chegada inicial.
void Simulacao::AdicionarPacote(double tempo_chegada, int id_pacote, int armazem_inicial, int armazem_final) {
    Pacote* novo_pacote = new Pacote(tempo_chegada, id_pacote, armazem_inicial, armazem_final);
    
    Lista* rota = rede_armazens->GetRota(*rede_armazens, armazem_inicial, armazem_final);

    // Verifica se a rota é válida. Uma rota válida deve existir e começar no armazém inicial.
    // std::cout << std::endl << "rota->GetHead()->valor: " << rota->GetHead()->valor << std::endl;
    // std::cout << "armazem_inicial: " << armazem_inicial << std::endl << std::endl;

    if (rota == nullptr || rota->Vazia() || rota->GetHead()->valor != armazem_inicial) {
        // Imprime um alerta para o usuário saber que o pacote não pode ser entregue.
        std::cerr << "[ALERTA] Pacote " << id_pacote << " de " << armazem_inicial 
                  << " para " << armazem_final << ": Nenhuma rota valida encontrada. Pacote descartado." << std::endl;
        
        // Libera a memória alocada para o pacote e a rota inválida para evitar memory leaks.
        delete novo_pacote;
        if (rota != nullptr) {
            delete rota;
        }
        // Não insere o pacote na simulação, evitando o loop infinito.
        return; 
    }

    novo_pacote->SetRota(rota);
    novo_pacote->SetEstado(Pacote::Chegada_Escalonada);
    
    todos_pacotes[id_pacote] = novo_pacote;
    pacotes_pendentes++;
    
    EventoChegada* evento_chegada = new EventoChegada(tempo_chegada, novo_pacote, armazem_inicial);
    escalonador_eventos->InserirEvento(evento_chegada);
};

// Inicia os eventos de transporte para todas as rotas da rede.
void Simulacao::IniciarTransportes(double tempo_inicial) {
    for (int i = 0; i < numero_armazens; i++) {
        Lista* vizinhos = rede_armazens->GetVizinhos(i);
        NodeLista* atual = vizinhos->GetHead();
        
        while (atual != nullptr) {
            int vizinho_id = atual->valor;
            // Para evitar duplicar eventos (0->1 e 1->0), agenda ambos de uma vez
            if (i < vizinho_id) {
                EventoTransporte* evento_ida = new EventoTransporte(tempo_inicial + intervalo_transportes, i, vizinho_id);
                escalonador_eventos->InserirEvento(evento_ida);
                
                EventoTransporte* evento_volta = new EventoTransporte(tempo_inicial + intervalo_transportes, vizinho_id, i);
                escalonador_eventos->InserirEvento(evento_volta);
            }
            atual = atual->proximo;
        }
    }
}

// Contém o laço principal que executa a simulação.
void Simulacao::ExecutarSimulacao() {
    bool primeiro_pacote_processado = false;

    // A simulação continua enquanto houver eventos na fila e pacotes não entregues.
    while (!escalonador_eventos->Vazio() && pacotes_pendentes > 0) {
        Evento* proximo_evento = escalonador_eventos->ExtrairEvento();

        // Inicializa os transportes com base no tempo de chegada do primeiro pacote
        if (!primeiro_pacote_processado && proximo_evento->GetTipo() == Evento::Chegada) {
            tempo_primeiro_pacote = proximo_evento->GetTempo();
            IniciarTransportes(tempo_primeiro_pacote);
            primeiro_pacote_processado = true;
        }
        
        // Avança o relógio da simulação
        if (proximo_evento->GetTempo() > tempo_atual) {
            tempo_atual = proximo_evento->GetTempo();
        }
        
        // Processa o evento de acordo com seu tipo
        if (proximo_evento->GetTipo() == Evento::Chegada) {
            ProcessarEventoChegada(static_cast<EventoChegada*>(proximo_evento));
        } else if (proximo_evento->GetTipo() == Evento::Transporte) {
            ProcessarEventoTransporte(static_cast<EventoTransporte*>(proximo_evento));
        }
        
        delete proximo_evento; // Libera a memória do evento processado
    }
    
    ImprimirLog(); // Imprime o log de eventos no final
}

// Processa a chegada de um pacote em um armazém.
void Simulacao::ProcessarEventoChegada(EventoChegada* evento) {
    Pacote* pacote = evento->GetPacote();
    int armazemId = evento->GetArmazemChegada();
    
    char msgBuffer[100];
    std::string idBuffer;

    if (armazemId == pacote->GetArmazemFinal()) { // Se for o armazem final, ele conclui a entrega
        pacote->SetEstado(Pacote::Entregue);
        idBuffer = FormatarIdentificadorString(armazemId, 3);
        sprintf(msgBuffer, "entregue em %s", idBuffer.c_str());
        RegistrarLog(evento->GetTempo(), pacote->GetIdPacote(), msgBuffer);
        pacotes_pendentes--;
    } else { // Se não for o armazém final, armazena o pacote na seção correta
        lista_armazens[armazemId]->AddPacote(pacote);
        std::string idBufferProx = FormatarIdentificadorString(pacote->GetProximoSalto(), 3);
        idBuffer = FormatarIdentificadorString(armazemId, 3);
        sprintf(msgBuffer, "armazenado em %s na secao %s", idBuffer.c_str(), idBufferProx.c_str());
        RegistrarLog(evento->GetTempo(), pacote->GetIdPacote(), msgBuffer);
    }
}

// Processa um evento de transporte, movendo pacotes de um armazém para outro.
void Simulacao::ProcessarEventoTransporte(EventoTransporte* evento) {
    int origemId = evento->GetArmazemOrigem();
    int destinoId = evento->GetArmazemDestino();

    // Reagenda o próximo evento de transporte para esta rota.
    Evento* proximoTransporte = new EventoTransporte(tempo_atual + intervalo_transportes, origemId, destinoId);
    escalonador_eventos->InserirEvento(proximoTransporte);

    Secao* secao = lista_armazens[origemId]->GetSecaoByDestino(destinoId);
    if (secao == nullptr || secao->Vazia()) {
        return; // Nada a transportar.
    }

    PilhaPacotes* pilha = secao->GetPilhaPacotes();
    int numPacotesNaSecao = pilha->GetTamanho();
    Pacote** pacotesNaSecaoLIFO = pilha->GetPacotesInArray();

    int pacotesATransportarCount = (numPacotesNaSecao < capacidade_transporte) ? numPacotesNaSecao : capacidade_transporte;
    
    // Pacotes que chegaram primeiro estão no fundo da pilha (final do array).
    Pacote** pacotesSelecionados = new Pacote*[pacotesATransportarCount];
    for (int i = 0; i < pacotesATransportarCount; ++i) {
        pacotesSelecionados[i] = pacotesNaSecaoLIFO[numPacotesNaSecao - 1 - i];
    }
    
    double tempoDaOperacao = tempo_atual;
    PilhaPacotes pilhaTemporaria;
    
    char msgBuffer[100];
    std::string idOrigemBuffer = FormatarIdentificadorString(origemId, 3);
    std::string idDestinoBuffer = FormatarIdentificadorString(destinoId, 3);

    // FASE 1: Desempilha pacotes, separando os que serão transportados.
    while (!pilha->Vazia()) {
        Pacote* pacoteDoTopo = pilha->Desempilhar();
        tempoDaOperacao += custo_remocao;
        
        sprintf(msgBuffer, "removido de %s na secao %s", idOrigemBuffer.c_str(), idDestinoBuffer.c_str());
        RegistrarLog(tempoDaOperacao, pacoteDoTopo->GetIdPacote(), msgBuffer);
        
        bool transportarEste = false;
        for (int i = 0; i < pacotesATransportarCount; ++i) {
            if (pacotesSelecionados[i] == pacoteDoTopo) {
                transportarEste = true;
                break;
            }
        }
        if (!transportarEste) {
            pilhaTemporaria.Empilhar(pacoteDoTopo);
        }
    }
    
    // FASE 2: Agenda a chegada dos pacotes selecionados no destino.
    for (int i = 0; i < pacotesATransportarCount; ++i) {
        Pacote* pacote = pacotesSelecionados[i];
        pacote->AvancarRota();
        pacote->SetEstado(Pacote::Chegada_Escalonada); // Estado que indica trânsito

        sprintf(msgBuffer, "em transito de %s para %s", idOrigemBuffer.c_str(), idDestinoBuffer.c_str());
        RegistrarLog(tempoDaOperacao, pacote->GetIdPacote(), msgBuffer);

        Evento* chegadaEv = new EventoChegada(tempoDaOperacao + latencia_transporte, pacote, destinoId);
        escalonador_eventos->InserirEvento(chegadaEv);
    }

    // FASE 3: Reempilha os pacotes que não foram transportados.
    while (!pilhaTemporaria.Vazia()) {
        Pacote* pacoteParaRearmazenar = pilhaTemporaria.Desempilhar();
        pilha->Empilhar(pacoteParaRearmazenar);
        sprintf(msgBuffer, "rearmazenado em %s na secao %s", idOrigemBuffer.c_str(), idDestinoBuffer.c_str());
        RegistrarLog(tempoDaOperacao, pacoteParaRearmazenar->GetIdPacote(), msgBuffer);
    }
    
    delete[] pacotesNaSecaoLIFO;
    delete[] pacotesSelecionados;
}

// Formata e armazena uma linha de log.
void Simulacao::RegistrarLog(double tempo, int id_pacote, std::string descricao) {
    char buffer[256];
    std::string id_formatado = FormatarIdentificadorString(id_pacote, 3);
    
    sprintf(buffer, "%07d pacote %s %s", (int)round(tempo), id_formatado.c_str(), descricao.c_str());
    historico_eventos->AdicionarTexto(std::string(buffer));
}

// Imprime todos os logs armazenados.
void Simulacao::ImprimirLog() {
    historico_eventos->Imprimir();
}

// Formata um número para uma string com preenchimento de zeros.
std::string Simulacao::FormatarIdentificadorString(int id, int tamanho) {
    char buffer[10];
    sprintf(buffer, "%0*d", tamanho, id);
    return std::string(buffer);
}

// Libera toda a memória alocada dinamicamente.
void Simulacao::LimparMemoria() {
    if (lista_armazens != nullptr) {
        for (int i = 0; i < numero_armazens; ++i) {
            delete lista_armazens[i];
        }
        delete[] lista_armazens;
    }
    
    if (todos_pacotes != nullptr) {
        for (int i = 0; i < numero_pacotes; ++i) {
            delete todos_pacotes[i];
        }
        delete[] todos_pacotes;
    }
    
    delete rede_armazens;
    delete escalonador_eventos;
    delete historico_eventos;
}