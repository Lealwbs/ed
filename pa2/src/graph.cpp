#include "graph.hpp"


Grafo::Grafo(){
    this->vertices = ListaAdjacencia();
}

Grafo::~Grafo(){
    this->vertices.deleteList();
}

void Grafo::InsereVertice(){
    this->vertices.addVertice(0);
}

void Grafo::InsereAresta(int v, int w){
    Node* current = this->vertices.getHead();
    while (current != nullptr) {
        if (current->getValue() == v) {
            current->lista_arestas->addVertice(w);
            break;
        }
        current = current->getNext();
    }
}

int Grafo::QuantidadeVertices(){
    return this->vertices.getSize();
}

int Grafo::QuantidadeArestas(){
    Node* current = this->vertices.getHead();
    int qtde_arestas = 0;
    while (current != nullptr) {
        qtde_arestas += current->lista_arestas->getSize();
        current = current->getNext();
    }
    return qtde_arestas/2;
}

int Grafo::GrauMinimo(){
    Node* current = this->vertices.getHead();
    int grau_minimo = 999999;
    while (current != nullptr) {
        if (current->lista_arestas->getSize() < grau_minimo) {
            grau_minimo = current->lista_arestas->getSize();
        }
        current = current->getNext();
    }
    return grau_minimo;
}

int Grafo::GrauMaximo(){
    Node* current = this->vertices.getHead();
    int grau_maximo = 0;
    while (current != nullptr) {
        if (current->lista_arestas->getSize() > grau_maximo) {
            grau_maximo = current->lista_arestas->getSize();
        }
        current = current->getNext();
    }
    return grau_maximo;
}

void Grafo::ImprimeVizinhos(int v){
    Node* current = this->vertices.getHead();
    while (current != nullptr) {
        if (current->getPosicaoVertice() == v) {
            current->lista_arestas->printList();
            break;
        }
        current = current->getNext();
    }
}