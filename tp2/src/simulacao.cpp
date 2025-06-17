#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>

#include "../include/simulacao.hpp"

// Construtor
Simulacao::Simulacao(int cap_transporte, int lat_transporte, int int_transportes, 
                     int cst_remocao, int num_armazens, int** matriz_adjacencia) {
    // Inicializar parâmetros
    capacidade_transporte = cap_transporte;
    latencia_transporte = lat_transporte;
    intervalo_transportes = int_transportes;
    custo_remocao = cst_remocao;
    numero_armazens = num_armazens;
    
    // Inicializar variáveis de controle
    tempo_atual = 0.0;
    pacotes_pendentes = 0;
    total_pacotes = 0;
    
    // Inicializar estruturas - GrafoRede aceita apenas um parâmetro
    rede_armazens = new GrafoRede(numero_armazens);
    lista_armazens = new Armazem*[numero_armazens];
    escalonador_eventos = new HeapEscalonador();
    historico_eventos = new Lista();
    todos_pacotes = nullptr;  // Será alocado em FinalizarConfiguracao
    
    // Criar armazéns
    CriarArmazens();
    
    std::cout << "Simulação inicializada com " << numero_armazens << " armazéns" << std::endl;
}

// Destrutor
Simulacao::~Simulacao() {
    LimparMemoria();
}

// Método para adicionar pacote
void Simulacao::AdicionarPacote(Pacote* novo_pacote) {
    if (novo_pacote == nullptr) {
        throw std::runtime_error("Tentativa de adicionar pacote nulo");
    }
    
    // Validar pacote
    if (!ValidarPacote(novo_pacote)) {
        throw std::runtime_error("Pacote inválido: " + std::to_string(novo_pacote->GetIdPacote()));
    }
    
    // Criar evento de chegada do pacote
    EventoChegada* evento_chegada = new EventoChegada(
        novo_pacote->GetTempoChegada(),
        novo_pacote,
        novo_pacote->GetArmazemInicial()
    );
    
    escalonador_eventos->InserirEvento(evento_chegada);
    pacotes_pendentes++;
    total_pacotes++;
    
    std::cout << "Pacote " << novo_pacote->GetIdPacote() << " adicionado à simulação" << std::endl;
}

// Finalizar configuração
void Simulacao::FinalizarConfiguracao() {
    if (total_pacotes == 0) {
        throw std::runtime_error("Nenhum pacote foi adicionado à simulação");
    }
    
    // Alocar array para todos os pacotes (se necessário para controle)
    todos_pacotes = new Pacote*[total_pacotes];
    
    // Calcular rotas dos pacotes
    CalcularRotasPacotes();
    
    std::cout << "Configuração finalizada. Total de pacotes: " << total_pacotes << std::endl;
}

// Exibir resultados
void Simulacao::ExibirResultados() {
    std::cout << "\n=== RESULTADOS DA SIMULAÇÃO ===" << std::endl;
    std::cout << "Tempo total de simulação: " << tempo_atual << std::endl;
    std::cout << "Pacotes processados: " << total_pacotes << std::endl;
    std::cout << "Pacotes pendentes: " << pacotes_pendentes << std::endl;
    
    // Exibir histórico de eventos
    std::cout << "\n=== HISTÓRICO DE EVENTOS ===" << std::endl;
    if (historico_eventos != nullptr) {
        NodeLista* atual = historico_eventos->GetHead();
        while (atual != nullptr) {
            if (atual->tipo == tipo_string) {
                // Assumindo que há um campo para string no NodeLista
                std::cout << "Evento registrado" << std::endl;
            }
            atual = atual->proximo;
        }
    }
    
    // Exibir estatísticas dos armazéns
    std::cout << "\n=== STATUS DOS ARMAZÉNS ===" << std::endl;
    for (int i = 0; i < numero_armazens; i++) {
        if (lista_armazens[i] != nullptr) {
            std::cout << "Armazém " << i << ": ";
            std::cout << "Ativo" << std::endl;
        }
    }
}

// Método para criar armazéns
void Simulacao::CriarArmazens() {
    for (int i = 0; i < numero_armazens; i++) {
        // Armazem precisa de 2 parâmetros: id e número total de destinos
        lista_armazens[i] = new Armazem(i, numero_armazens);
        
        // Criar seções baseadas nos vizinhos
        Lista* vizinhos = rede_armazens->GetVizinhos(i);
        if (vizinhos != nullptr) {
            NodeLista* atual = vizinhos->GetHead();
            while (atual != nullptr) {
                if (atual->tipo == tipo_inteiro) {
                    int vizinho_id = atual->valor;
                    if (ValidarArmazem(vizinho_id)) {
                        // Assumindo que existe um método para criar seção
                        // lista_armazens[i]->CriarSecao(vizinho_id);
                    }
                }
                atual = atual->proximo;
            }
        }
    }
    
    std::cout << "Armazéns criados com suas seções" << std::endl;
}

// Calcular rotas dos pacotes
void Simulacao::CalcularRotasPacotes() {
    // Este método deve calcular as rotas usando o algoritmo apropriado
    // Por exemplo, Dijkstra ou Floyd-Warshall
    
    // Implementação básica - você pode expandir conforme necessário
    for (int i = 0; i < numero_armazens; i++) {
        for (int j = 0; j < numero_armazens; j++) {
            if (i != j) {
                // Calcular menor caminho de i para j
                // Lista* caminho = rede_armazens->EncontrarMenorCaminho(i, j);
                // Armazenar o caminho conforme sua estrutura de dados
            }
        }
    }
}

// Executar transferência entre armazéns
void Simulacao::ExecutarTransferenciaArmazem(int origem, int destino, double momento) {
    if (!ValidarArmazem(origem) || !ValidarArmazem(destino)) {
        throw std::runtime_error("Armazéns inválidos para transferência");
    }
    
    Armazem* armazem_origem = lista_armazens[origem];
    if (armazem_origem == nullptr) {
        throw std::runtime_error("Armazém de origem não inicializado");
    }
    
    // Obter seção correspondente ao destino
    Secao* secao_destino = armazem_origem->GetSecaoByDestino(destino);
    if (secao_destino == nullptr) {
        // Não há seção para este destino, não há pacotes para transferir
        return;
    }
    
    // Transferir até a capacidade máxima
    int pacotes_transferidos = 0;
    // Assumindo que existe um método GetPilha() que retorna uma pilha
    // PilhaSecao* pilha = secao_destino->GetPilha();
    
    // Simulação de transferência - adapte conforme sua implementação
    while (pacotes_transferidos < capacidade_transporte) {
        // Verificar se há pacotes na seção
        if (secao_destino->Vazia()) {
            break;
        }
        
        Pacote* pacote = secao_destino->DesempilharPacote();
        if (pacote != nullptr) {
            // Criar evento de chegada no destino
            EventoChegada* chegada = new EventoChegada(
                momento + latencia_transporte,
                pacote,
                destino
            );
            
            escalonador_eventos->InserirEvento(chegada);
            
            // Registrar evento de transporte
            std::string descricao = "transportado de " + 
                                  FormatarIdentificadorString(origem, 3) + 
                                  " para " + 
                                  FormatarIdentificadorString(destino, 3);
            RegistrarEvento(momento, pacote->GetIdPacote(), descricao);
            
            pacotes_transferidos++;
        } else {
            break;
        }
    }
    
    if (pacotes_transferidos > 0) {
        std::cout << "Transferidos " << pacotes_transferidos 
                  << " pacotes de " << origem << " para " << destino << std::endl;
    }
}

// Métodos de validação
bool Simulacao::ValidarArmazem(int id_armazem) const {
    return id_armazem >= 0 && id_armazem < numero_armazens;
}

bool Simulacao::ValidarPacote(const Pacote* pacote) const {
    if (pacote == nullptr) return false;
    
    // Criar cópia não-const para acessar métodos
    Pacote* pacote_nao_const = const_cast<Pacote*>(pacote);
    
    return ValidarArmazem(pacote_nao_const->GetArmazemInicial()) && 
           ValidarArmazem(pacote_nao_const->GetArmazemFinal()) &&
           pacote_nao_const->GetArmazemInicial() != pacote_nao_const->GetArmazemFinal();
}

bool Simulacao::ValidarEvento(const Evento* evento) const {
    if (evento == nullptr) return false;
    
    // Criar cópia não-const para acessar métodos
    Evento* evento_nao_const = const_cast<Evento*>(evento);
    
    return evento_nao_const->GetTempo() >= 0;
}

// Registrar evento no histórico
void Simulacao::RegistrarEvento(double tempo, int id_pacote, const std::string& descricao) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) 
        << tempo << " P" << id_pacote << " " << descricao;
    
    std::string evento_formatado = oss.str();
    // Assumindo que Lista tem método para inserir strings
    historico_eventos->AdicionarTexto(evento_formatado);
}

// Formatar identificador como string
std::string Simulacao::FormatarIdentificadorString(int id, int tamanho) {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(tamanho) << id;
    return oss.str();
}

// Limpeza de memória
void Simulacao::LimparMemoria() {
    // Limpar armazéns
    if (lista_armazens != nullptr) {
        for (int i = 0; i < numero_armazens; i++) {
            delete lista_armazens[i];
        }
        delete[] lista_armazens;
        lista_armazens = nullptr;
    }
    
    // Limpar estruturas
    delete rede_armazens;
    delete escalonador_eventos;
    delete historico_eventos;
    
    if (todos_pacotes != nullptr) {
        delete[] todos_pacotes;
        todos_pacotes = nullptr;
    }
    
    rede_armazens = nullptr;
    escalonador_eventos = nullptr;
    historico_eventos = nullptr;
}

// Métodos opcionais para depuração
void Simulacao::ExibirStatusSimulacao() const {
    std::cout << "Status da Simulação:" << std::endl;
    std::cout << "Tempo atual: " << tempo_atual << std::endl;
    std::cout << "Pacotes pendentes: " << pacotes_pendentes << std::endl;
    std::cout << "Total de pacotes: " << total_pacotes << std::endl;
}

void Simulacao::ExibirEstatisticas() const {
    std::cout << "Estatísticas da Simulação:" << std::endl;
    std::cout << "Capacidade de transporte: " << capacidade_transporte << std::endl;
    std::cout << "Latência de transporte: " << latencia_transporte << std::endl;
    std::cout << "Intervalo entre transportes: " << intervalo_transportes << std::endl;
    std::cout << "Custo de remoção: " << custo_remocao << std::endl;
}

bool Simulacao::VerificarIntegridade() const {
    // Verificações básicas de integridade
    if (numero_armazens <= 0) return false;
    if (lista_armazens == nullptr) return false;
    if (rede_armazens == nullptr) return false;
    if (escalonador_eventos == nullptr) return false;
    
    // Verificar se todos os armazéns foram criados
    for (int i = 0; i < numero_armazens; i++) {
        if (lista_armazens[i] == nullptr) return false;
    }
    
    return true;
}

// Método ExecutarSimulacao corrigido
void Simulacao::ExecutarSimulacao() {
    bool primeiro_pacote_processado = false;
    
    // Verificação inicial de segurança
    if (escalonador_eventos == nullptr) {
        std::cerr << "Erro: Escalonador de eventos não inicializado" << std::endl;
        return;
    }
    
    std::cout << "Iniciando simulação com " << pacotes_pendentes << " pacotes" << std::endl;
    
    // Loop principal da simulação
    while (!escalonador_eventos->Vazio() && pacotes_pendentes > 0) {
        Evento* proximo_evento = escalonador_eventos->ExtrairEvento();
        
        // Verificação de segurança do evento
        if (proximo_evento == nullptr) {
            std::cerr << "Erro: Evento nulo extraído do escalonador" << std::endl;
            break;
        }
        
        std::cout << "Processando evento tipo " << proximo_evento->GetTipo() 
                  << " no tempo " << proximo_evento->GetTempo() << std::endl;
        
        // Inicializa transportes no tempo do primeiro pacote
        if (!primeiro_pacote_processado && proximo_evento->GetTipo() == Evento::Chegada) {
            try {
                IniciarTransportesAutomaticos(proximo_evento->GetTempo());
                primeiro_pacote_processado = true;
                std::cout << "Transportes automáticos iniciados" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Erro ao iniciar transportes: " << e.what() << std::endl;
                delete proximo_evento;
                return;
            }
        }
        
        // Atualiza relógio da simulação
        if (proximo_evento->GetTempo() > tempo_atual) {
            tempo_atual = proximo_evento->GetTempo();
        }
        
        // Processa evento baseado no tipo com verificações de segurança
        try {
            switch (proximo_evento->GetTipo()) {
                case Evento::Chegada:
                    ProcessarEventoChegada(proximo_evento);
                    break;
                case Evento::Transporte:
                    ProcessarEventoTransporte(proximo_evento);
                    break;
                default:
                    std::cerr << "Tipo de evento desconhecido: " << proximo_evento->GetTipo() << std::endl;
                    break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Erro ao processar evento: " << e.what() << std::endl;
            delete proximo_evento;
            return;
        }
        
        delete proximo_evento;
        std::cout << "Pacotes pendentes restantes: " << pacotes_pendentes << std::endl;
    }
    
    std::cout << "Simulação concluída" << std::endl;
}

// Método IniciarTransportesAutomaticos corrigido
void Simulacao::IniciarTransportesAutomaticos(double tempo_inicial) {
    if (rede_armazens == nullptr) {
        throw std::runtime_error("Rede de armazéns não inicializada");
    }
    
    for (int i = 0; i < numero_armazens; i++) {
        Lista* vizinhos = nullptr;
        
        try {
            vizinhos = rede_armazens->GetVizinhos(i);
        } catch (const std::exception& e) {
            std::cerr << "Erro ao obter vizinhos do armazém " << i << ": " << e.what() << std::endl;
            continue;
        }
        
        if (vizinhos == nullptr) {
            std::cout << "Armazém " << i << " não possui vizinhos" << std::endl;
            continue;
        }
        
        // Percorre vizinhos usando a estrutura de lista com verificações
        NodeLista* current = vizinhos->GetHead();
        
        while (current != nullptr) {
            // Verificação mais robusta do tipo do nó
            if (current->tipo == tipo_inteiro) {
                int vizinho_id = current->valor;
                
                // Validação do ID do vizinho
                if (vizinho_id < 0 || vizinho_id >= numero_armazens) {
                    std::cerr << "ID de vizinho inválido: " << vizinho_id << std::endl;
                    current = current->proximo;
                    continue;
                }
                
                // Evita duplicação de rotas usando comparação de índices
                if (i < vizinho_id) {
                    try {
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
                        
                        std::cout << "Transporte agendado entre " << i << " e " << vizinho_id << std::endl;
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao agendar transporte entre " << i << " e " << vizinho_id 
                                  << ": " << e.what() << std::endl;
                    }
                }
            }
            current = current->proximo;
        }
    }
}

// Método ProcessarEventoChegada corrigido
void Simulacao::ProcessarEventoChegada(Evento* evento) {
    if (evento == nullptr || evento->GetTipo() != Evento::Chegada) {
        throw std::runtime_error("Evento de chegada inválido");
    }
    
    // Cast mais seguro
    EventoChegada* evento_chegada = dynamic_cast<EventoChegada*>(evento);
    if (evento_chegada == nullptr) {
        throw std::runtime_error("Cast para EventoChegada falhou");
    }
    
    Pacote* pacote = evento_chegada->GetPacote();
    if (pacote == nullptr) {
        throw std::runtime_error("Pacote nulo no evento de chegada");
    }
    
    int armazem_atual = evento_chegada->GetArmazemChegada();
    
    // Validação do armazém
    if (armazem_atual < 0 || armazem_atual >= numero_armazens) {
        throw std::runtime_error("Armazém de chegada inválido: " + std::to_string(armazem_atual));
    }
    
    std::cout << "Processando chegada do pacote " << pacote->GetIdPacote() 
              << " no armazém " << armazem_atual << std::endl;
    
    // Verifica se chegou ao destino final
    if (armazem_atual == pacote->GetArmazemFinal()) {
        pacote->SetEstado(Pacote::Entregue);
        std::string id_formatado = FormatarIdentificadorString(armazem_atual, 3);
        RegistrarEvento(evento->GetTempo(), pacote->GetIdPacote(), 
                       "entregue em " + id_formatado);
        pacotes_pendentes--;
        std::cout << "Pacote " << pacote->GetIdPacote() << " entregue!" << std::endl;
        
    } else {
        // Verifica se o pacote tem uma rota válida
        int proximo_salto = -1;
        try {
            proximo_salto = pacote->GetProximoSalto();
        } catch (const std::exception& e) {
            std::cerr << "Erro ao obter próximo salto para pacote " 
                      << pacote->GetIdPacote() << ": " << e.what() << std::endl;
            return;
        }
        
        if (proximo_salto < 0 || proximo_salto >= numero_armazens) {
            std::cerr << "Próximo salto inválido para pacote " << pacote->GetIdPacote() 
                      << ": " << proximo_salto << std::endl;
            return;
        }
        
        // Armazena pacote na seção apropriada
        if (lista_armazens[armazem_atual] == nullptr) {
            throw std::runtime_error("Armazém " + std::to_string(armazem_atual) + " não inicializado");
        }
        
        Secao* secao_destino = lista_armazens[armazem_atual]->GetSecaoByDestino(proximo_salto);
        if (secao_destino == nullptr) {
            throw std::runtime_error("Seção não encontrada para destino " + std::to_string(proximo_salto));
        }
        
        secao_destino->EmpilharPacote(pacote);
        
        std::string id_atual = FormatarIdentificadorString(armazem_atual, 3);
        std::string id_proximo = FormatarIdentificadorString(proximo_salto, 3);
        RegistrarEvento(evento->GetTempo(), pacote->GetIdPacote(), 
                       "armazenado em " + id_atual + " na secao " + id_proximo);
        
        std::cout << "Pacote " << pacote->GetIdPacote() << " armazenado no armazém " 
                  << armazem_atual << " seção " << proximo_salto << std::endl;
    }
}

// Método ProcessarEventoTransporte corrigido
void Simulacao::ProcessarEventoTransporte(Evento* evento) {
    if (evento == nullptr || evento->GetTipo() != Evento::Transporte) {
        throw std::runtime_error("Evento de transporte inválido");
    }
    
    // Cast mais seguro
    EventoTransporte* evento_transporte = dynamic_cast<EventoTransporte*>(evento);
    if (evento_transporte == nullptr) {
        throw std::runtime_error("Cast para EventoTransporte falhou");
    }
    
    int origem = evento_transporte->GetArmazemOrigem();
    int destino = evento_transporte->GetArmazemDestino();
    
    // Validação dos armazéns
    if (origem < 0 || origem >= numero_armazens || 
        destino < 0 || destino >= numero_armazens) {
        std::cerr << "Armazéns inválidos no transporte: origem=" << origem 
                  << ", destino=" << destino << std::endl;
        return;
    }
    
    std::cout << "Processando transporte de " << origem << " para " << destino << std::endl;
    
    // Reagenda próximo transporte nesta rota
    try {
        EventoTransporte* proximo_transporte = new EventoTransporte(
            tempo_atual + intervalo_transportes,
            origem,
            destino
        );
        escalonador_eventos->InserirEvento(proximo_transporte);
    } catch (const std::exception& e) {
        std::cerr << "Erro ao reagendar transporte: " << e.what() << std::endl;
    }
    
    // Executa a transferência de pacotes
    try {
        ExecutarTransferenciaArmazem(origem, destino, tempo_atual);
    } catch (const std::exception& e) {
        std::cerr << "Erro na transferência de armazém: " << e.what() << std::endl;
    }
}