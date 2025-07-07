#include "../include/SistemaLogistico.hpp"
#include <iostream>

// --- Declarações dos Helpers Recursivos ---
namespace {
    // A declaração do template genérico é suficiente.
    template <typename T>
    void deletarNosRecursivo(T* no);

    // Helpers para imprimir os dados das árvores
    void imprimirEventosRecursivo(NodeAVL<Evento*, int>* no);
    void imprimirPacotesRecursivo(NodeAVL<Pacote*, int>* no);
    void imprimirClientesRecursivo(NodeAVL<Cliente*, std::string>* no);
}

// --- Construtor e Destrutor ---

SistemaLogistico::SistemaLogistico() : proximoIdEvento(0) {}

SistemaLogistico::~SistemaLogistico() {
    deletarNosRecursivo(eventos.raiz);
    deletarNosRecursivo(pacotes.raiz);
    deletarNosRecursivo(clientes.raiz);
}

// --- Métodos Privados Auxiliares (GET/CREATE) ---

Pacote* SistemaLogistico::obterOuCriarPacote(int idPacote) {
    Pacote* pacote = pacotes.buscar(idPacote);
    if (pacote == nullptr) {
        pacote = new Pacote(idPacote);
        pacotes.inserir(pacote, idPacote);
    }
    return pacote;
}

Cliente* SistemaLogistico::obterOuCriarCliente(const std::string& nome) {
    if (nome.empty()) {
        return nullptr;
    }
    Cliente* cliente = clientes.buscar(nome);
    if (cliente == nullptr) {
        cliente = new Cliente(nome);
        clientes.inserir(cliente, nome);
    }
    return cliente;
}

// --- Processamento e Consultas ---

void SistemaLogistico::processarEvento(const Evento evento) {
    Evento* novoEvento = new Evento(evento);
    eventos.inserir(novoEvento, proximoIdEvento++);

    Pacote* pacoteAssociado = obterOuCriarPacote(novoEvento->getIdPacote());
    pacoteAssociado->adicionarEvento(*novoEvento);

    if (novoEvento->getTipoEvento() == TipoEvento::RG) {
        Cliente* remetente = obterOuCriarCliente(novoEvento->getRemetente());
        if(remetente) {
            remetente->addPacoteRemetente(pacoteAssociado->getId());
        }

        Cliente* destinatario = obterOuCriarCliente(novoEvento->getDestinatario());
        if(destinatario) {
            destinatario->addPacoteDestinatario(pacoteAssociado->getId());
        }
    }
}

void SistemaLogistico::consultarPacote(int idPacote) {
    Pacote* pacote = pacotes.buscar(idPacote);

    if (pacote == nullptr) {
        std::cout << "ERRO: Pacote " << idPacote << " nao encontrado." << std::endl;
        return;
    }

    // std::cout << "Historico do pacote " << Utils::intToString(idPacote, 3) << ":" << std::endl;
    std::cout << pacote->getHistoricoEventos().GetTamanho() << std::endl;
    pacote->getHistoricoEventos().Imprime();
    //std::cout << std::endl;
}

void SistemaLogistico::consultarUltimoEvento(int idPacote) {
    Pacote* pacote = pacotes.buscar(idPacote);

    if (pacote == nullptr) {
        std::cout << "ERRO: Pacote " << idPacote << " nao encontrado." << std::endl;
        return;
    }

    Evento* ultimoEvento = pacote->getUltimoEvento();
    if (ultimoEvento != nullptr) {
        std::cout << ultimoEvento->getInfo() << std::endl;
    } else {
        std::cout << "Nenhum evento associado ao pacote " << idPacote << "." << std::endl;
    }
}

void SistemaLogistico::consultarCliente(const std::string& nomeCliente) {
    Cliente* cliente = clientes.buscar(nomeCliente);

    if (cliente == nullptr) {
        //std::cout << "ERRO: Cliente " << nomeCliente << " nao encontrado." << std::endl;
        std::cout << "0" << std::endl; //Nada encontrado
        return;
    }

    // 1. Usa dois vetores temporários para armazenar os eventos a serem impressos.
    EventosVetor eventosDeRegistro;
    EventosVetor ultimosEventosDosPacotes;
    Vetor pacotesJaProcessados; // Para evitar processar o mesmo pacote duas vezes

    // Função auxiliar para encontrar e armazenar os eventos de uma lista de pacotes
    auto processarPacotes = [&](Vetor& idsDosPacotes) {
        for (int i = 0; i < idsDosPacotes.GetTamanho(); ++i) {
            int idPacote = idsDosPacotes.GetItem(i);

            // Se já processamos este pacote, pulamos para o próximo
            if (pacotesJaProcessados.Pesquisa(idPacote) != -1) {
                continue;
            }

            Pacote* pacote = pacotes.buscar(idPacote);
            if (pacote) {
                EventosVetor& historico = pacote->getHistoricoEventos();
                if (historico.GetTamanho() > 0) {
                    // O evento de registro (RG) é sempre o primeiro
                    eventosDeRegistro.InsereFinal(*historico.GetItem(1));

                    // O último evento é obtido pelo método do pacote
                    ultimosEventosDosPacotes.InsereFinal(*pacote->getUltimoEvento());
                }
            }
            // Marca o pacote como processado
            pacotesJaProcessados.InsereFinal(idPacote);
        }
    };

    // 2. Processa os pacotes onde o cliente é remetente e destinatário
    processarPacotes(cliente->getpacotesComoRemetente());
    processarPacotes(cliente->getpacotesComoDestinatario());

    // 3. Ordena as duas listas de eventos pela data/hora.
    eventosDeRegistro.OrdenaPorDataHora();
    ultimosEventosDosPacotes.OrdenaPorDataHora();

    // 4. Imprime a saída no formato exato da especificação.
    int totalLinhas = eventosDeRegistro.GetTamanho() + ultimosEventosDosPacotes.GetTamanho();
    std::cout << totalLinhas << std::endl;

    // Imprime primeiro todos os eventos de registro (agora ordenados)
    eventosDeRegistro.Imprime();
    // Depois, imprime todos os últimos eventos de cada pacote (agora ordenados)
    ultimosEventosDosPacotes.Imprime();
}

// --- Funções de Depuração ---

void SistemaLogistico::imprimirEventos() {
    std::cout << "\n--- LISTA DE EVENTOS ---" << std::endl;
    if (eventos.estaVazia()) {
        std::cout << "Nenhum evento no sistema." << std::endl;
        return;
    }
    imprimirEventosRecursivo(eventos.raiz);
}

void SistemaLogistico::imprimirPacotes() {
    std::cout << "\n--- LISTA DE PACOTES ---" << std::endl;
    if (pacotes.estaVazia()) {
        std::cout << "Nenhum pacote no sistema." << std::endl;
        return;
    }
    imprimirPacotesRecursivo(pacotes.raiz);
}

void SistemaLogistico::imprimirClientes() {
    std::cout << "\n--- LISTA DE CLIENTES ---" << std::endl;
    if (clientes.estaVazia()) {
        std::cout << "Nenhum cliente no sistema." << std::endl;
        return;
    }
    imprimirClientesRecursivo(clientes.raiz);
}


// --- Implementação dos Helpers Recursivos ---
namespace {
    template <typename T>
    void deletarNosRecursivo(T* no) {
        if (no != nullptr) {
            deletarNosRecursivo(no->esquerda);
            deletarNosRecursivo(no->direita);
            delete no->dado;
        }
    }

    void imprimirEventosRecursivo(NodeAVL<Evento*, int>* no) {
        if (no != nullptr) {
            imprimirEventosRecursivo(no->esquerda);
            std::cout << no->dado->getInfo() << std::endl;
            imprimirEventosRecursivo(no->direita);
        }
    }

    void imprimirPacotesRecursivo(NodeAVL<Pacote*, int>* no) {
        if (no != nullptr) {
            imprimirPacotesRecursivo(no->esquerda);
            std::cout << "Pacote ID: " << no->dado->getId() << std::endl;
            imprimirPacotesRecursivo(no->direita);
        }
    }

    void imprimirClientesRecursivo(NodeAVL<Cliente*, std::string>* no) {
        if (no != nullptr) {
            imprimirClientesRecursivo(no->esquerda);
            std::cout << "Cliente: " << no->dado->getNome() << std::endl;
            imprimirClientesRecursivo(no->direita);
        }
    }
}
