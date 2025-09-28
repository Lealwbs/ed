#include "list.hpp"

List::List(){
    head = new Node{-1, nullptr}; // Dummy fixed head node
    tail = head; 
    size = 0;
};  

List::~List(){
    Clear();
    delete head;
};

List::List(const List& other){
    head = new Node{-1, nullptr}; 
    tail = head;
    size = 0;
   
    Node* current = other.head->next; // skip dummy
    while (current != nullptr) {
        this->PushBack(current->value);
        current = current->next;
    }
}

List& List::operator=(const List& other){
    if (this != &other) {
        this->Clear();
        tail = head;

        Node* current = other.head->next; // skip dummy
        while (current != nullptr) {
            this->PushBack(current->value);
            current = current->next;
        }
    }
    return *this;
}

int List::Size(){
    return size;
};

bool List::Empty(){
    return size == 0;
};

std::string List::ToString(){
    std::string result = "[";
    Node* current = head->next; // skip dummy

    while (current != nullptr) {
        result += std::to_string(current->value);
        if (current->next != nullptr) {
            result += ", ";
        }
        current = current->next;
    }
    result += "]";
    return result;
};

int List::Get(int pos){
    Node* node = GetNodeAt(pos);
    if (node != nullptr) {
        return node->value;
    }
    return -1; // Invalid position
}; 
void List::Set(int value, int pos){
    Node* node = GetNodeAt(pos);
    if (node != nullptr) {
        node->value = value;
    }
};

void List::PushFront(int value){
    Node* newNode = new Node(value, head->next);
    head->next = newNode;
    if (tail == head) { // List was empty
        tail = newNode;
    }
    size++;
};

void List::PushBack(int value){
    Node* newNode = new Node(value, nullptr);
    tail->next = newNode;
    tail = newNode;
    size++;
};

void List::PushAt(int value, int pos){
    if (pos < 0 || pos > size) {
        return; // Invalid position
    }

    if (pos == 0) {
        PushFront(value);
    } else if (pos == size) {
        PushBack(value);
    } else {
        Node* prev = GetNodeAt(pos, true);
        Node* newNode = new Node(value, prev->next);
        prev->next = newNode;
        size++;
    }
};

int List::PopFront(){
    if (size == 0) {
        return -1; // List is empty
    }

    Node* temp = head->next;
    int retValue = temp->value;
    head->next = temp->next;
    if (temp == tail) { // List had one element
        tail = head;
    }
    size--;
    delete temp;
    return retValue;
};
int List::PopBack(){
    if (size == 0) {
        return -1; // List is empty
    }

    Node* prev = GetNodeAt(size - 1, true); // Node before tail (tail = size-1)
    int retValue = tail->value;
    delete tail;
    if (prev == nullptr) { // List had one element
        head->next = nullptr;
        tail = head;
    } else {
        prev->next = nullptr;
        tail = prev;
    }
    size--;
    return retValue;
};
int List::PopAt(int pos){
    if (pos < 0 || pos >= size) {
        return -1; // Invalid position
    }

    if (pos == 0) {
        return PopFront();
    } else if (pos == size - 1) {
        return PopBack();
    } else {
        Node* prev = GetNodeAt(pos, true);
        Node* toDelete = prev->next;
        int retValue = toDelete->value;
        prev->next = toDelete->next;
        delete toDelete;
        size--;
        return retValue;
    }
};

int List::Search(int value){
    Node* current = head->next; // skip dummy
    int index = 0;
    while (current != nullptr) {
        if (current->value == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1; // Not found
};

void List::Clear(){
    Node* current = head->next; // skip dummy
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head->next = nullptr;
    tail = head;
    size = 0;
};

Node* List::GetNodeAt(int pos, bool before){
    if (pos < 0 || pos >= size) {
        return nullptr;
    }

    Node* current = head; // start from dummy head
    for (int i = 0; i < pos + !before; ++i) {
        current = current->next;
    }
    return current;
};