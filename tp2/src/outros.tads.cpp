#include "../include/outros_tads.hpp"
#include <iostream>
#include <cstring>

// ------------------
// LISTA DE INTEIROS
// ------------------

ListaInt::ListaInt() : inicio(nullptr), fim(nullptr) {}

ListaInt::~ListaInt() {
    NodeListaInt* atual = inicio;
    while (atual != nullptr) {
        NodeListaInt* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
}

void ListaInt::Adicionar(int valor) {
    NodeListaInt* novo = new NodeListaInt{valor, nullptr};
    if (Vazia()) {
        inicio = fim = novo;
    } else {
        fim->proximo = novo;
        fim = novo;
    }
}

bool ListaInt::Vazia() const {
    return inicio == nullptr;
}

void ListaInt::Imprimir() const {
    NodeListaInt* atual = inicio;
    while (atual != nullptr) {
        std::cout << atual->valor << " ";
        atual = atual->proximo;
    }
    std::cout << std::endl;
}

// ------------------
// LISTA DE STRINGS
// ------------------

ListaString::ListaString() : inicio(nullptr), fim(nullptr) {}

ListaString::~ListaString() {
    NodeListaString* atual = inicio;
    while (atual != nullptr) {
        NodeListaString* proximo = atual->proximo;
        delete[] atual->texto;
        delete atual;
        atual = proximo;
    }
}

void ListaString::Adicionar(const char* texto) {
    NodeListaString* novo = new NodeListaString;
    if (texto) {
        novo->texto = new char[strlen(texto) + 1];
        strcpy(novo->texto, texto);
    } else {
        novo->texto = nullptr;
    }
    novo->proximo = nullptr;

    if (Vazia()) {
        inicio = fim = novo;
    } else {
        fim->proximo = novo;
        fim = novo;
    }
}

bool ListaString::Vazia() const {
    return inicio == nullptr;
}

void ListaString::Imprimir() const {
    NodeListaString* atual = inicio;
    while (atual != nullptr) {
        if (atual->texto) {
            std::cout << atual->texto << std::endl;
        }
        atual = atual->proximo;
    }
}

// -------------
// FILA DE INT
// -------------

FilaInt::FilaInt() : frente(nullptr), tras(nullptr) {}

FilaInt::~FilaInt() {
    while (!Vazia()) {
        Desenfileirar();
    }
}

void FilaInt::Enfileirar(int valor) {
    NodeFilaInt* novo = new NodeFilaInt{valor, nullptr};
    if (tras) {
        tras->proximo = novo;
    } else {
        frente = novo;
    }
    tras = novo;
}

int FilaInt::Desenfileirar() {
    if (Vazia()) return -1;

    NodeFilaInt* temp = frente;
    int valor = temp->valor;
    frente = frente->proximo;

    if (frente == nullptr) {
        tras = nullptr;
    }

    delete temp;
    return valor;
}

bool FilaInt::Vazia() const {
    return frente == nullptr;
}
