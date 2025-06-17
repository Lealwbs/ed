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
    };
    
    // Constrói o grafo da rede a partir da matriz de adjacência
    for (int i = 0; i < numero_armazens; i++) {
        for (int j = 0; j < numero_armazens; j++) {
            if (matriz_adjacencia[i][j] == 1) {
                rede_armazens->AdicionarAresta(i, j);
            };
        };
    };
    
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
    PrepararSimulacao();
    bool primeiro_pacote_processado = false;

    std::cout << "SUCCESS: ExecutarSimulacao v0" << std::endl;
    int count = 0;
    // Loop principal da simulação
    while (!escalonador_eventos->Vazio() && pacotes_pendentes > 0) {
        // Remove o próximo evento
        Evento* proximo_evento = escalonador_eventos->ExtrairEvento();
        
        //std::cout << "SUCCESS: Qtde pacotes pendentes: " << pacotes_pendentes << std::endl;
        //if( count++ == 200) break;

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
    ImprimirLog();
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

// void Simulador::processarChegadaPacote(ChegadaPacoteEvento* evento) {
    Pacote* pacote = evento->GetPacote();
    int armazemId = evento->GetArmazemChegada();
    
    char msgBuffer[100];
    std::string idBuffer;

    // Verifica se o armazém atual é o destino final do pacote.
    if (armazemId == pacote->GetArmazemFinal()) {
        pacote->SetEstado(Pacote::Entregue);
        idBuffer = FormatarIdentificadorString(armazemId, 3);
        sprintf(msgBuffer, "entregue em %s", idBuffer.c_str());
        RegistrarLog(evento->GetTempo(), pacote->GetIdPacote(), msgBuffer);
        pacotes_pendentes--; // Decrementa o contador de pacotes ativos.
    
    } else {
        // Se não for o destino, armazena o pacote na seção correta.
        lista_armazens[armazemId]->AddPacote(pacote);
        idBuffer = FormatarIdentificadorString(armazemId, 3);
        std::string idBufferProx = FormatarIdentificadorString(pacote->GetProximoSalto(), 3);
        sprintf(msgBuffer, "armazenado em %s na secao %s", idBuffer.c_str(), idBufferProx.c_str());
        RegistrarLog(evento->GetTempo(), pacote->GetIdPacote(), msgBuffer);
    }
}

// Processa evento de transporte de pacotes
void Simulacao::ProcessarEventoTransporte(EventoTransporte* evento) {

    int origemId = evento->GetArmazemOrigem();
    int destinoId = evento->GetArmazemDestino();

    // Reagenda o próximo evento de transporte para esta rota, mantendo o ciclo.
    Evento* proximoTransporte = new EventoTransporte(tempo_atual + intervalo_transportes, origemId, destinoId);
    escalonador_eventos->InserirEvento(proximoTransporte);

    Secao* secao = lista_armazens[origemId]->getSecaoPorDestino(destinoId);
    if (secao == nullptr || secao->Vazia()) {
        return; // Nenhum pacote para transportar.
    }

    PilhaPacotes* pilha = secao->pilha_pacotes();
    int numPacotesNaSecao = pilha->getTamanho();
    Pacote** pacotesNaSecaoLIFO = pilha->getPacotes();

    // Determina quantos pacotes transportar, limitado pela capacidade do veículo.
    int pacotesATransportarCount = (numPacotesNaSecao < capacidadeTransporte) ? numPacotesNaSecao : capacidadeTransporte;
    
    // Simula uma seleção FIFO (primeiro a entrar, primeiro a sair) a partir da pilha LIFO.
    // Os pacotes que chegaram primeiro estão no fundo da pilha (final do array).
    Pacote** pacotesSelecionados = new Pacote*[pacotesATransportarCount];
    for (int i = 0; i < pacotesATransportarCount; ++i) {
        pacotesSelecionados[i] = pacotesNaSecaoLIFO[numPacotesNaSecao - 1 - i];
    }
    
    double tempoDaOperacao = relogio;
    PilhaPacotes pilhaTemporaria;
    
    char msgBuffer[100];
    char idOrigemBuffer[4], idDestinoBuffer[4];
    formatarId(origemId, 3, idOrigemBuffer);
    formatarId(destinoId, 3, idDestinoBuffer);

    // FASE 1: Desempilha todos os pacotes, separando os que serão transportados.
    while (!pilha->vazia()) {
        Pacote* pacoteDoTopo = pilha->desempilhar();
        tempoDaOperacao += custoRemocao; // Adiciona custo de remoção.
        
        sprintf(msgBuffer, "removido de %s na secao %s", idOrigemBuffer, idDestinoBuffer);
        registrarLog(tempoDaOperacao, pacoteDoTopo->getId(), msgBuffer);
        
        bool transportarEste = false;
        for (int i = 0; i < pacotesATransportarCount; ++i) {
            if (pacotesSelecionados[i] == pacoteDoTopo) {
                transportarEste = true;
                break;
            }
        }

        if (!transportarEste) {
            pilhaTemporaria.empilhar(pacoteDoTopo); // Guarda para reempilhar depois.
        }
    }
    
    // FASE 2: Processa os pacotes selecionados, agendando sua chegada ao destino.
    for (int i = 0; i < pacotesATransportarCount; ++i) {
        Pacote* pacote = pacotesSelecionados[i];
        pacote->avancarRota();
        pacote->setEstado(Pacote::EM_TRANSITO);

        sprintf(msgBuffer, "em transito de %s para %s", idOrigemBuffer, idDestinoBuffer);
        registrarLog(tempoDaOperacao, pacote->getId(), msgBuffer);

        Evento* chegadaEv = new ChegadaPacoteEvento(tempoDaOperacao + latenciaTransporte, pacote, destinoId);
        escalonador.Inserir(chegadaEv);
    }

    // FASE 3: Reempilha os pacotes que não foram transportados de volta na seção.
    while (!pilhaTemporaria.vazia()) {
        Pacote* pacoteParaRearmazenar = pilhaTemporaria.desempilhar();
        pilha->empilhar(pacoteParaRearmazenar);
        sprintf(msgBuffer, "rearmazenado em %s na secao %s", idOrigemBuffer, idDestinoBuffer);
        registrarLog(tempoDaOperacao, pacoteParaRearmazenar->getId(), msgBuffer);
    }
    
    // Libera a memória dos arrays temporários.
    delete[] pacotesNaSecaoLIFO;
    delete[] pacotesSelecionados;
}


// Registra um evento no histórico
void Simulacao::RegistrarLog(double tempo, int id_pacote, std::string descricao) {
    char buffer[256];
    std::string id_formatado = FormatarIdentificadorString(id_pacote, 3);
    
    sprintf(buffer, "%07d pacote %s %s", 
            static_cast<int>(round(tempo)), 
            id_formatado.c_str(), 
            descricao.c_str());
    
    historico_eventos->AdicionarTexto(std::string(buffer));
}

// Imprime o histórico de eventos
void Simulacao::ImprimirLog() {
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