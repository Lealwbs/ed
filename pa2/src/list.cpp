#include <iostream>
#include "list.hpp"

Node::Node(int value, Node* next){
    this->value = value;
    this->next = next;
};

Node::~Node(){
    this->next = nullptr;
};

void Node::setValue(int value){
    this->value = value;
};

void Node::setNext(Node* next){
    this->next = next;
};

int Node::getValue(){
    return this->value;
};

Node* Node::getNext(){
    return this->next;
};

// *****************************

List::List(){
    this->head = nullptr;
    this->size = 0;
};

List::~List(){
    Node* current = this->head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->getNext();
        delete temp;
    }
    this->head = nullptr;
    this->size = 0;
};

Node* List::getHead(){
    return this->head;
};

int List::getSize(){
    return this->size;
};

void List::addNode(int value){
    Node* newNode = new Node(value, this->head);
    this->head = newNode; 
    this->size++;
};

void List::printList(){
    Node* current = this->head;
    while (current != nullptr){
        std::cout << current->getValue() << " ";
        current = current->getNext();
    }
    // std::cout << std::endl;
};

// *****************************

NodeVertice::NodeVertice(int posicao_vertice, NodeVertice* next){
    this->next = next;
    this->posicao_vertice = posicao_vertice;
};

NodeVertice::~NodeVertice(){
    this->next = nullptr;
    this->posicao_vertice = -1;
    delete &(this->arestas);
};

int NodeVertice::getPosicaoVertice(){
    return this->posicao_vertice;
};

void NodeVertice::setNext(NodeVertice* next){
    this->next = next;
};

NodeVertice* NodeVertice::getNext(){
    return this->next;
};

int NodeVertice::getSizeLista(){
    return this->arestas.getSize();
};

void NodeVertice::addArestaInside(int aresta_value){
    arestas.addNode(aresta_value);
};

void NodeVertice::printLista(){
    this->arestas.printList();
}

// *****************************

ListaAdjacencia::ListaAdjacencia(){
    this->sizeLista = 0;
    this->headLista = nullptr;
};

ListaAdjacencia::~ListaAdjacencia(){
    NodeVertice* current = this->headLista;
    while (current != nullptr) {
        NodeVertice* temp = current;
        current = current->getNext();
        delete temp;
    }
    this->sizeLista = 0;
    this->headLista = nullptr;
};

void ListaAdjacencia::addNodeVertice(){
    NodeVertice* newNodeVertice = new NodeVertice(sizeLista+1, this->headLista);
    this->headLista = newNodeVertice;
    this->sizeLista++;
};

int ListaAdjacencia::getSizeLista(){
    return this->sizeLista;
};

void ListaAdjacencia::addAresta(int posicao_vertice, int aresta_value){
    NodeVertice* current = this->findVerticeByPosition(posicao_vertice);
    current->addArestaInside(aresta_value);
};

NodeVertice* ListaAdjacencia::findVerticeByPosition(int posicao_vertice){
    NodeVertice* current = this->headLista;
    while(current != nullptr){
        if(current->getPosicaoVertice() == posicao_vertice){
            return current;
        };
        current = current->getNext();
    };
    return nullptr;
};

void ListaAdjacencia::printLista(){
    NodeVertice* current = this->headLista;
    while(current != nullptr){
        std::cout << current->getPosicaoVertice() << "º Vertice - ";
        std::cout << "Size:" << current->getSizeLista() << " | ";
        current->printLista();
        std::cout << std::endl;

        current = current->getNext();
    }
}