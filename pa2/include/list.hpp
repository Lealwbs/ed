#ifndef LIST_HPP
#define LIST_HPP

class Node{
    public:
        Node(int value, Node* next = nullptr);
        ~Node();

        void setValue(int value);
        void setNext(Node* next);
        
        int getValue();
        Node* getNext();

    private:
        int value;
        Node* next;
};

class List{
    public:
        List();
        ~List();

        void addNode(int value);
        int getSize();

        void printList();

    private:
        Node* head;
        int size;
};

class NodeVertice{ 

    public:
        NodeVertice(Node* next = nullptr);
        ~NodeVertice();

        Node* getNext();
        void setNext(Node* next);

        int getPosicaoVertice();

    private:
        int posicao_vertice;
        NodeVertice* next;
};


class ListaAdjacencia{
    public:
        ListaAdjacencia();
        ~ListaAdjacencia();

        Node* getHead();

        void addNodeVertice(int value);
        void printList();
        void deleteList();

    private:
        NodeVertice* head;
        int size;
};

#endif
