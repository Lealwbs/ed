#ifndef OUTROS_TADS_HPP
#define OUTROS_TADS_HPP

#include <iostream>
#include <cstring>

// ------------------
// LISTA DE INTEIROS
// ------------------
struct NodeListaInt {
    int valor;
    NodeListaInt* proximo;
};

class ListaInt {
public:
    ListaInt();
    ~ListaInt();

    void Adicionar(int valor);
    bool Vazia() const;
    void Imprimir() const;

private:
    NodeListaInt* inicio;
    NodeListaInt* fim;
};

// ------------------
// LISTA DE STRINGS
// ------------------
struct NodeListaString {
    char* texto;
    NodeListaString* proximo;
};

class ListaString {
public:
    ListaString();
    ~ListaString();

    void Adicionar(const char* texto);
    bool Vazia() const;
    void Imprimir() const;

private:
    NodeListaString* inicio;
    NodeListaString* fim;
};

// -------------
// FILA DE INT
// -------------
struct NodeFilaInt {
    int valor;
    NodeFilaInt* proximo;
};

class FilaInt {
public:
    FilaInt();
    ~FilaInt();

    void Enfileirar(int valor);
    int Desenfileirar();
    bool Vazia() const;

private:
    NodeFilaInt* frente;
    NodeFilaInt* tras;
};

#endif
