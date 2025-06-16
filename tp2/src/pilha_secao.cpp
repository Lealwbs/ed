#include "../include/pilha_secao.hpp"
#include <iostream>

// ###################
// PILHA DE PACOTES
// ###################

PilhaPacotes::PilhaPacotes() {
    topo = nullptr;
    tamanho = 0;
}

PilhaPacotes::~PilhaPacotes() {
    while (!Vazia()) {
        Desempilhar();  // Remove os nós, mas não deleta os pacotes (gerenciados externamente)
    }
}

void PilhaPacotes::Empilhar(Pacote* pacote) {
    NodePilhaPacotes* novo = new NodePilhaPacotes{pacote, topo};
    topo = novo;
    ++tamanho;
}

Pacote* PilhaPacotes::Desempilhar() {
    if (Vazia()) return nullptr;

    NodePilhaPacotes* temp = topo;
    Pacote* pacote_topo = temp->pacote;
    topo = topo->next;

    delete temp;
    --tamanho;

    return pacote_topo;
}

Pacote* PilhaPacotes::DesempilharSemRemover() {
    // Apenas retorna o pacote do topo sem remover ele
    if (Vazia()) return nullptr;
    return topo->pacote;
}

bool PilhaPacotes::Vazia() {
    return topo == nullptr;
}

int PilhaPacotes::GetTamanho() {
    return tamanho;
}

Pacote** PilhaPacotes::GetPacotesInArray() { // Cria um array com a cópia dos pacotes da pilha
    if (Vazia()) return nullptr;

    Pacote** array = new Pacote*[tamanho];
    NodePilhaPacotes* atual = topo;
    int i = 0;
    while (atual != nullptr) {
        array[i++] = atual->pacote;
        atual = atual->next;
    }
    return array;
}

void PilhaPacotes::Imprimir() {
    NodePilhaPacotes* atual = topo;
    std::cout << "(TOPO)";
    while (atual != nullptr) {
        std::cout << " " << atual->pacote->GetIdPacote();
        // std::cout << "TESTE";
        atual = atual->next;
    }
    std::cout << " (BASE)" << std::endl;
}


// ###################
// PILHA DE SEÇÃO
// ###################

Secao::Secao(){
    armazem_destino = -1; // Inicializa o armazém destino como inválido
    pilha_pacotes = new PilhaPacotes();
}

Secao::~Secao() {
    delete pilha_pacotes;
}

void Secao::EmpilharPacote(Pacote* pacote) {
    pilha_pacotes->Empilhar(pacote);
}

Pacote* Secao::DesempilharPacote() {
    return pilha_pacotes->Desempilhar();
}

int Secao::GetArmazemDestino() {
    return armazem_destino;
}

void Secao::SetArmazemDestino(int destino) {
    armazem_destino = destino;
}

bool Secao::Vazia() {
    return pilha_pacotes->Vazia();
}

int Secao::GetTamanho() {
    return pilha_pacotes->GetTamanho();
}

void Secao::Print() {
    std::cout << "Secao para armazem destino (" << armazem_destino << "): ";
    pilha_pacotes->Imprimir();
}
