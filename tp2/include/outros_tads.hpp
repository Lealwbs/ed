#ifndef OUTROS_TADS_HPP
#define OUTROS_TADS_HPP

#include <iostream>
#include <cstring>

// ------------------
// LISTA DE INTEIROS/STRINGS
// ------------------
enum TipoDado {
    tipo_inteiro,
    tipo_string
};

struct NodeLista {
    TipoDado tipo;
    int valor;
    std::string texto;
    NodeLista* proximo;
};

class Lista {
public:
    Lista();
    ~Lista();

    void AdicionarInt(int valor);
    void AdicionarTexto(std::string texto);

    void RemoverInicio();

    NodeLista* GetHead();
    bool Vazia();

    void Imprimir();
    void ImprimirRota();

private:
    NodeLista* head;
    NodeLista* tail;
};


// -------------
// FILA DE INT
// -------------
struct NodeFila {
    int valor;
    NodeFila* proximo;
};

class Fila {
public:
    Fila();
    ~Fila();

    void Enfileirar(int valor);
    int Desenfileirar();
    bool Vazia() const;

private:
    NodeFila* frente;
    NodeFila* tras;
};

#endif
