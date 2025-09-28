#ifndef LIST_HPP
#define LIST_HPP

#include <string>

typedef struct Node_t{
    int value;
    Node_t* next;
    Node_t(int val = 0, Node_t* nxt = nullptr): value(val), next(nxt){};
} Node;

class List {
    private:
        int size;
        Node* head;
        Node* tail;
        Node* GetNodeAt(int pos, bool before = false); // Get node at position, starting from 0. It gets the node before it if 'before' is true.

    public:
        List();
        ~List();
        List(const List& other); // Copy constructor
        List& operator=(const List& other); // Copy assignment operator
        
        int Size();
        bool Empty();
        std::string ToString();

        int Get(int pos); 
        void Set(int value, int pos);

        void PushFront(int value);
        void PushBack(int value);
        void PushAt(int value, int pos);

        int PopFront();
        int PopBack();
        int PopAt(int pos);

        int Search(int value);
        void Clear();
};

#endif