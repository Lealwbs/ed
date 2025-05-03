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

void List::addNode(int value){
    Node* newNode = new Node(value, this->head);
    this->head = newNode; 
    this->size++;
};

int List::getSize(){
    return this->size;
};

void List::printList(){
    Node* current = this->head;
    while (current != nullptr){
        std::cout << current->getValue() << " ";
        current = current->getNext();
    }
    std::cout << std::endl;
};