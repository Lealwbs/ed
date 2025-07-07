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
        std::cout << "ERRO: Cliente " << nomeCliente << " nao encontrado." << std::endl;
        return;
    };

    // std::cout << "Pacotes associados a " << nomeCliente << ":" << std::endl;
    Vetor& pacotesRemetidos = cliente->getpacotesComoRemetente();
    Vetor& pacotesRecebidos = cliente->getpacotesComoDestinatario();
    int qtdeTotalPacotes = pacotesRemetidos.GetTamanho() + pacotesRecebidos.GetTamanho();

    // Para cada evento que o cliente participou, será impresso o Evento e o último evento do pacote associado.
    std::cout << qtdeTotalPacotes*2 << std::endl; 

    Vetor temp;

    for (int i = 0; i < pacotesRemetidos.GetTamanho(); ++i) {
        int idPacote = pacotesRemetidos.GetItem(i);
        std::cout << Utils::intToString(idPacote, 3) << " (remetente)" << std::endl;
        temp.InsereFinal(idPacote);
        //consultarUltimoEvento(idPacote);
    };
    
    for (int i = 0; i < pacotesRecebidos.GetTamanho(); ++i) {
        int idPacote = pacotesRecebidos.GetItem(i);
        std::cout << Utils::intToString(idPacote, 3) << " (destinatario)" << std::endl;
        temp.InsereFinal(idPacote);
        //consultarUltimoEvento(idPacote);
    };

    for(int i = 0; i < temp.GetTamanho(); i++) {
        consultarUltimoEvento(temp.GetItem(i));
    };

    //std::cout << std::endl;
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



// 0000200 PC 003 <consulta 2>
// 5 <n1 - numero de linhas da resposta da consulta 1>
// 0000001 EV RG 003 JOAO MARIA 000 003
// 0000002 EV AR 003 000 002
// 0000104 EV RM 003 000 002
// 0000104 EV TR 003 000 002
// 0000124 EV AR 003 002 003

// 0300 PC 002 <consulta 4>
// 7 <n1 - numero de linhas da resposta da consulta 1>
// 0000080 EV RG 002 PEDRO LUISA 000 003
// 0000093 EV AR 002 000 002
// 0000102 EV RM 002 000 002
// 0000104 EV UR 002 000 002
// 0000202 EV RM 002 000 002
// 0000202 EV TR 002 000 002
// 0000222 EV AR 002 002 003

// 0000210 CL JOAO <consulta 3>
// 4 <n1 - numero de linhas da resposta da consulta 1>
// 0000001 EV RG 003 JOAO MARIA 000 003
// 0000070 EV RG 007 JOAO JOSE 000 003
// 0000203 EV TR 003 002 003
// 0000203 EV TR 007 002 003

// 0000150 CL LUISA <consulta 1>
// 6 <n1 - numero de linhas da resposta da consulta 1>
// 0000006 EV RG 006 LUISA ANDRE 003 002
// 0000012 EV RG 005 BERNARDO LUISA 002 003
// 0000080 EV RG 002 PEDRO LUISA 000 003
// 0000104 EV UR 002 000 002
// 0000122 EV EN 005 003
// 0000123 EV EN 006 002


// <consulta 1>
// <n1 - numero de linhas da resposta da consulta 1>
// <linha 1 da resposta a consulta 1>
// ...
// <linha n1 da resposta a consulta 1>
// <consulta 2>
// ...
