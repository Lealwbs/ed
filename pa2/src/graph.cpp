#include "graph.hpp"

Grafo::Grafo(){};
Grafo::~Grafo(){};

void Grafo::InsereVertice(){
  void addNodeVertice();
};

void Grafo::InsereAresta(int v, int w){
  return this->vertices.addAresta(v, w);
};

int Grafo::QuantidadeVertices(){
  return this->vertices.getSizeLista();
};

int Grafo::QuantidadeArestas(){
  return this->vertices.getQtdeArestas();
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