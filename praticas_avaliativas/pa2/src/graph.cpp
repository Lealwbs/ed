#include "list.hpp"
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
  int grauMin = 99999;

  NodeVertice* current = nullptr;
  current = this->vertices.getHeadLista();

  for(int i=0; i<(this->QuantidadeVertices()); i++){
    if(current->getSizeLista() < grauMin){
      grauMin = current->getSizeLista();
    };          
    current = current->getNext();
  };
  return grauMin;
};

int Grafo::GrauMaximo(){
  int grauMax = 0;

  NodeVertice* current = nullptr;
  current = this->vertices.getHeadLista();

  for(int i=0; i<(this->QuantidadeVertices()); i++){
    if(current->getSizeLista() > grauMax){
      grauMax = current->getSizeLista();
    };          
    current = current->getNext();
  };
  return grauMax;
};

void Grafo::ImprimeVizinhos(int v){
  this->vertices.printListaInformation();
};