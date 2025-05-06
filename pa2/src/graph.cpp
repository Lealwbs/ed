#include "graph.hpp"

Grafo::Grafo(){};
Grafo::~Grafo(){};

void Grafo::InsereVertice(){
  this->vertices.addNodeVertice();
};

void Grafo::InsereAresta(int v, int w){
  this->vertices.addAresta(v, w);
};

int Grafo::QuantidadeVertices(){
  return this->vertices.getSizeLista();
};

int Grafo::QuantidadeArestas(){
  return (this->vertices.getQtdeArestas())/2;
};

int Grafo::GrauMinimo(){
  return 0;
};

int Grafo::GrauMaximo(){
  return 0;
};

void Grafo::ImprimeVizinhos(int v){
  this->vertices.printListaInformation();
};