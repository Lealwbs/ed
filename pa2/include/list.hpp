#ifndef LIST_HPP
#define LIST_HPP

enum NodeType{
    NODE = 0,
    NODE_LIST = 1
};
class ListaAdjacencia;

class Node{
    public:
        Node(NodeType nodeType, Node* next = nullptr);
        ~Node();

        int getValue();
        void setValue(int value);

        Node* getNext();
        void setNext(Node* next);

        int getPosicaoVertice();

        ListaAdjacencia* lista_arestas; 

    private:
        Node* next;
        NodeType nodeType; 

        // type = 0
        int value; 

        // type = 1
        int posicao_vertice;
        int qtde_arestas;
};

class ListaAdjacencia{
    public:
        ~ListaAdjacencia();

        Node* getHead();
        int getSize();

        void addVertice(int value);
        void printList();
        void deleteList();

    private:
        Node* head;
        int size;
};

#endif
