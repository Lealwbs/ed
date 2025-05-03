#include <iostream>
#include "list.hpp"

Node::Node(NodeType nodeType, Node* next){
    this->next = next;
    this->nodeType = nodeType;
}

Node::~Node(){
    this->next = nullptr;
    this->nodeType = NODE;
    this->lista_arestas->deleteList();
    this->lista_arestas = nullptr;
}

int Node::getValue(){
    return this->value;
}

void Node::setValue(int value){
    this->value = value;
}

Node* Node::getNext(){
    return this->next;
}

void Node::setNext(Node* next){
    this->next = next;
}

int Node::getPosicaoVertice(){
    return this->posicao_vertice;
}

ListaAdjacencia::~ListaAdjacencia(){
    this->deleteList();
}

Node* ListaAdjacencia::getHead(){
    return this->head;
}

int ListaAdjacencia::getSize(){
    return this->size;
}

void ListaAdjacencia::addVertice(int value){
    Node* newNode = new Node(NODE, nullptr);
    newNode->setNext(this->head);
    this->head = newNode;
    this->size++;
}

void ListaAdjacencia::printList(){
    Node* current = this->head;
    while (current != nullptr) {
        std::cout << current->getValue() << " ";
        current = current->getNext();
    }
    std::cout << std::endl;
}

void ListaAdjacencia::deleteList(){
    Node* current = this->head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->getNext();
        delete temp;
    }
    this->head = nullptr;
    this->size = 0;
}
