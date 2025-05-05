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

Node* List::getTail(){
    if (this->size == 0){
        return nullptr;
    } else {
        Node* current = this->head;
        while(current->getNext() != nullptr){
            current = current->getNext();
        };
        return current;
    };
};

void List::addNode(int value){
    Node* newNode = new Node(value, nullptr);
    
    if(this->size == 0){
        this->head = newNode; 
    } else {
        Node* current = this->getTail();
        current->setNext(newNode);
    }
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
    // delete &(this->arestas);
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
    this->arestas.addNode(aresta_value);
};

void NodeVertice::printLista(){
    this->arestas.printList();
}

// *****************************

ListaAdjacencia::ListaAdjacencia(){
    this->headLista = nullptr;
    this->sizeLista = 0;
    this->qtdeArestas = 0;
};

ListaAdjacencia::~ListaAdjacencia(){
    NodeVertice* current = this->headLista;
    while (current != nullptr) {
        NodeVertice* temp = current;
        current = current->getNext();
        delete temp;
    }
    this->headLista = nullptr;
    this->sizeLista = 0;
    this->qtdeArestas = 0;
};

NodeVertice* ListaAdjacencia::getTailLista(){
    if (this->sizeLista == 0){
        return nullptr;
    } else {
        NodeVertice* current = this->headLista;
        while(current->getNext() != nullptr){
            current = current->getNext();
        };
        return current;
    };
};

void ListaAdjacencia::addNodeVertice(){
    NodeVertice* newNodeVertice = new NodeVertice(sizeLista+1, nullptr);
    
    if (this->sizeLista == 0){
        this->headLista = newNodeVertice;
    } else {
        NodeVertice* current = this->getTailLista();
        current->setNext(newNodeVertice);
    }
    this->sizeLista++;
};

void ListaAdjacencia::addManyNodeVertices(int qtdeVertices){
    for(int i=0; i<qtdeVertices; i++){
        this->addNodeVertice();
    };
};

int ListaAdjacencia::getSizeLista(){
    return this->sizeLista;
};

int ListaAdjacencia::getQtdeArestas(){
    return this->qtdeArestas;
};

void ListaAdjacencia::addAresta(int posicao_vertice, int aresta_value){
    NodeVertice* current = this->headLista;
    for(int i = 0; i < posicao_vertice; i++){
        current = current->getNext();
    };
    current->addArestaInside(aresta_value);
    this->qtdeArestas++;
};

void ListaAdjacencia::printListaFullInformation(){
    NodeVertice* current = this->headLista;
    while(current != nullptr){
        std::cout << "Vertice " << current->getPosicaoVertice() << " ";
        std::cout << "(Size: " << current->getSizeLista() << ") | ";
        current->printLista();
        std::cout << std::endl;

        current = current->getNext();
    };
};

void ListaAdjacencia::printListaInformation(){
    NodeVertice* current = this->headLista;
    while(current != nullptr){
        current->printLista();
        std::cout << std::endl;
        current = current->getNext();
    };
};