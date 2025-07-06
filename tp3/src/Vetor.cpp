#include "../include/Vetor.hpp"
#include <iostream>
#include <stdexcept>

// Construtor e Destrutor
Vetor::Vetor() {
    primeiro = nullptr;
    ultimo = nullptr;
    tamanho = 0;
};

Vetor::~Vetor() {
    Limpa();
};

// Métodos de acesso
int Vetor::GetItem(int pos) {
    if (pos < 0 || pos >= tamanho) {
        throw std::out_of_range("Posição inválida");
    }
    
    Node* no = Posiciona(pos);
    return no->valor;
};

void Vetor::SetItem(int item, int pos) {
    if (pos < 0 || pos >= tamanho) {
        throw std::out_of_range("Posição inválida");
    }
    
    Node* no = Posiciona(pos);
    no->valor = item;
};

int Vetor::GetTamanho() {
    return tamanho;
};

bool Vetor::Vazio() {
    return tamanho == 0;
};

void Vetor::InsereInicio(int item) {
    Node* novo = new Node;
    novo->valor = item;
    novo->prox = primeiro;
    
    primeiro = novo;
    
    if (ultimo == nullptr) {
        ultimo = novo;
    };
    
    tamanho++;
};

void Vetor::InsereFinal(int item) {
    Node* novo = new Node;
    novo->valor = item;
    novo->prox = nullptr;
    
    if (ultimo == nullptr) {
        primeiro = ultimo = novo;
    } else {
        ultimo->prox = novo;
        ultimo = novo;
    };
    
    tamanho++;
};

void Vetor::InserePosicao(int item, int pos) {
    if (pos < 0 || pos > tamanho) {
        throw std::out_of_range("Posição inválida para inserção");
    };
    
    if (pos == 0) {
        InsereInicio(item);
        return;
    };
    
    if (pos == tamanho) {
        InsereFinal(item);
        return;
    };
    
    Node* anterior = Posiciona(pos, true);
    Node* novo = new Node;
    novo->valor = item;
    novo->prox = anterior->prox;
    anterior->prox = novo;
    
    tamanho++;
};

// Métodos de remoção
int Vetor::RemoveInicio() {
    if (Vazio()) {
        throw std::runtime_error("Vetor vazio");
    };
    
    Node* temp = primeiro;
    int valor = temp->valor;
    
    primeiro = primeiro->prox;
    
    if (primeiro == nullptr) {
        ultimo = nullptr;
    };
    
    delete temp;
    tamanho--;
    
    return valor;
}

int Vetor::RemoveFinal() {
    if (Vazio()) {
        throw std::runtime_error("Vetor vazio");
    };
    
    if (tamanho == 1) {
        return RemoveInicio();
    };
    
    Node* anterior = Posiciona(tamanho - 1, true);
    Node* temp = ultimo;
    int valor = temp->valor;
    
    anterior->prox = nullptr;
    ultimo = anterior;
    
    delete temp;
    tamanho--;
    
    return valor;
}

int Vetor::RemovePosicao(int pos) {
    if (pos < 0 || pos >= tamanho) {
        throw std::out_of_range("Posição inválida");
    };
    
    if (pos == 0) {
        return RemoveInicio();
    };
    
    if (pos == tamanho - 1) {
        return RemoveFinal();
    };
    
    Node* anterior = Posiciona(pos, true);
    Node* temp = anterior->prox;
    int valor = temp->valor;
    
    anterior->prox = temp->prox;
    delete temp;
    tamanho--;
    
    return valor;
}

// Métodos de busca e utilitários
int Vetor::Pesquisa(int item) {
    Node* atual = primeiro;
    int posicao = 0;
    
    while (atual != nullptr) {
        if (atual->valor == item) {
            return posicao;
        };
        atual = atual->prox;
        posicao++;
    };
    
    return -1; // Não encontrado
};

void Vetor::Imprime() {
    std::cout << "Vetor: [";
    
    Node* atual = primeiro;
    while (atual != nullptr) {
        std::cout << atual->valor;
        if (atual->prox != nullptr) {
            std::cout << ", ";
        };
        atual = atual->prox;
    };
    
    std::cout << "]" << std::endl;
    std::cout << "Tamanho: " << tamanho << std::endl;
};

void Vetor::Limpa() {
    while (primeiro != nullptr) {
        Node* temp = primeiro;
        primeiro = primeiro->prox;
        delete temp;
    };
    
    primeiro = ultimo = nullptr;
    tamanho = 0;
};

// Método privado
Node* Vetor::Posiciona(int pos, bool antes) {
    if (pos < 0 || pos >= tamanho) {
        throw std::out_of_range("Posição inválida");
    };
    
    // Se for para posicionar antes e a posição for 0, retorna nullptr
    if (antes && pos == 0) {
        return nullptr;
    };
    
    Node* atual = primeiro;
    int contador = 0;
    
    // Se for para posicionar antes, para uma posição antes
    int limite = antes ? pos - 1 : pos;
    
    while (contador < limite && atual != nullptr) {
        atual = atual->prox;
        contador++;
    };
    
    return atual;
};