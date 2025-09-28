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

        Node* getHead();
        Node* getTail();
        int getSize();
        void addNode(int value);
        void printList();

    private:
        Node* head;
        int size;
};

class NodeVertice{ 

    public:
        NodeVertice(int posicao_vertice, NodeVertice* next = nullptr);
        ~NodeVertice();

        int getPosicaoVertice();
        void setNext(NodeVertice* next);
        NodeVertice* getNext();
        int getSizeLista();
        void addArestaInside(int aresta_value);

        void printLista();

    private:
        int posicao_vertice;
        NodeVertice* next;
        List arestas;
};

class ListaAdjacencia{
    public:
        ListaAdjacencia();
        ~ListaAdjacencia();

        NodeVertice* getHeadLista();
        NodeVertice* getTailLista();

        void addNodeVertice();
        void addManyNodeVertices(int qtdeVertices);

        int getSizeLista();
        int getQtdeArestas();

        void addAresta(int posicao_vertice, int aresta_value);

        void printListaFullInformation();
        void printListaInformation();

    private:
        NodeVertice* headLista;
        int sizeLista;
        int qtdeArestas;
};

#endif
