#include "../include/linked_list.hpp"
#include <iostream>

ListaEncadeada::ListaEncadeada() {
    primeiro = new Node;
    primeiro->valor = -1;
    ultimo = primeiro;
};

ListaEncadeada::~ListaEncadeada() {
    Limpa();
    delete primeiro;
};

int ListaEncadeada::GetItem(int pos) {
    if (pos < 0 || pos >= tamanho) {
        throw "ERRO: Posição inválida!";
        return -1;
    };

    Node* aux = primeiro;
    for (int i = 0; i < pos; i++) {
        aux = aux->prox;
    };

    return aux->valor;
};

void ListaEncadeada::SetItem(int item, int pos) {
    if (pos < 0 || pos >= tamanho) {
        throw "ERRO: Posição inválida!";
        return;
    };

    Node* aux = primeiro;
    for (int i = 0; i < pos; i++) {
        aux = aux->prox;
    };
    aux->valor = item;
};

void ListaEncadeada::InsereInicio(int item) {
    if (tamanho == 0){
        primeiro->valor = item;
    } else {
        Node* aux = new Node;
        aux->valor = item;
        aux->prox = primeiro;
        primeiro = aux;
    }
        
    tamanho++;
};

void ListaEncadeada::InsereFinal(int item) {
    if (tamanho == 0) {
        primeiro->valor = item;
    } else {
        Node* aux = new Node;
        aux->valor = item;
        aux->prox = nullptr;

        ultimo->prox = aux;
        ultimo = aux;
    };

    tamanho++;
};

void ListaEncadeada::InserePosicao(int item, int pos) {
    if (pos < 0 || pos >= tamanho) {
        throw "ERRO: Posição inválida!";
        return;
    };

    Node* antes = primeiro;
    for(int i=0; i<pos-1; i++){
        antes = antes->prox;
    };

    Node* depois = antes->prox;

    Node* novo = new Node;
    novo->valor = item;

    antes->prox = novo;
    novo->prox = depois;

    tamanho++;
};

int ListaEncadeada::RemoveInicio() {

    tamanho--;
    return 0;
};

int ListaEncadeada::RemoveFinal() {
    tamanho--;
    return 0;
};

int ListaEncadeada::RemovePosicao(int pos) {
    tamanho--;
    return 0;
};

int ListaEncadeada::Pesquisa(int c) {
    return 0;
};

void ListaEncadeada::Imprime() {
    if(tamanho == 0)
        return;

    Node* aux = primeiro;
    for(int i=0; i<tamanho; i++){
        std::cout << aux->valor << " ";
        aux = aux->prox;
    };
    std::cout << std::endl;
};

void ListaEncadeada::Limpa() {

};

Node* ListaEncadeada::Posiciona(int pos, bool antes) {
    return nullptr;
};