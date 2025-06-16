#include "../include/outros_tads.hpp"

// ------------------
// IMPLEMENTAÇÃO - LISTA
// ------------------

Lista::Lista(){
    head = nullptr;
    tail = nullptr;
};

Lista::~Lista() {
    NodeLista* atual = head;
    while (atual != nullptr) {
        NodeLista* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    };
};

void Lista::AdicionarInt(int valor) {
    NodeLista* novo = new NodeLista;
    novo->tipo = tipo_inteiro;
    novo->valor = valor;
    novo->texto = "";
    novo->proximo = nullptr;

    if (Vazia()) {
        head = tail = novo;
    } else {
        tail->proximo = novo;
        tail = novo;
    };
};

void Lista::AdicionarTexto(std::string texto) {
    NodeLista* novo = new NodeLista;
    novo->tipo = tipo_string;
    novo->valor = 0;
    novo->texto = texto;
    novo->proximo = nullptr;

    if (Vazia()) {
        head = tail = novo;
    } else {
        tail->proximo = novo;
        tail = novo;
    };
};

void Lista::RemoverInicio() {
    if (head == nullptr) return;
    NodeLista* temp = head;
    head = head->proximo;
    delete temp;
    if (head == nullptr) tail = nullptr;
};

NodeLista* Lista::GetHead() {
    return head;
};

bool Lista::Vazia() {
    return head == nullptr;
};

void Lista::Imprimir() {
    NodeLista* atual = head;
    while (atual != nullptr) {
        if (atual->tipo == tipo_inteiro) {
            std::cout << atual->valor << " ";
        } else if (atual->tipo == tipo_string) {
            std::cout << atual->texto << std::endl;
        };
        atual = atual->proximo;
    };

    if (head != nullptr && head->tipo == tipo_inteiro) {
        std::cout << std::endl;
    };
};

void Lista::ImprimirRota() {
    if (Vazia()) {
        std::cout << "Rota vazia!" << std::endl;
        return;
    };

    NodeLista* atual = head;
    while (atual != nullptr) {
        if (atual->tipo == tipo_inteiro) {
            std::cout << atual->valor;
            if (atual->proximo != nullptr) {
                std::cout << " -> ";
            };
        };
        atual = atual->proximo;
    };
    std::cout << std::endl;
};





// ------------------
// FILA
// ------------------

Fila::Fila() {
    frente = nullptr;
    tras = nullptr;
};

Fila::~Fila() {
    while (!Vazia()) {
        Desenfileirar();
    };
};

void Fila::Enfileirar(int valor) {
    NodeFila* novo = new NodeFila{valor, nullptr};

    if (tras != nullptr) {
        tras->proximo = novo;
    } else {
        frente = novo;
    };

    tras = novo;
};

int Fila::Desenfileirar() {
    if (Vazia()) {
        return -1;
    };

    NodeFila* temp = frente;
    int valor = temp->valor;
    frente = frente->proximo;

    if (frente == nullptr) {
        tras = nullptr;
    };

    delete temp;
    return valor;
};

bool Fila::Vazia() const {
    return frente == nullptr;
};
