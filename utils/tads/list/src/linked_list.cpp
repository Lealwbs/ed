#include "../include/linked_list.hpp"

ListaEncadeada::ListaEncadeada() {
    primeiro = new Node;
    ultimo = primeiro;
};

ListaEncadeada::~ListaEncadeada() {
    Limpa();
    delete primeiro;
};

int ListaEncadeada::GetItem(int pos) {
    if (pos < 0 || pos >= tamanho){
        throw "ERRO: Posição inválida!";
        return -1;
    };

    Node* aux = primeiro;
    for(int i=0; i<pos; i++){
        aux = aux->prox;
    };

    return aux->valor;
};

void ListaEncadeada::SetItem(int item, int pos) {
    if ( pos<0 || pos >= tamanho) {
        throw "ERRO: Posição inválida!";
        return;
    };

    Node* aux = primeiro;
    for(int i=0; i<pos; i++){
        aux = aux->prox;
    };
    aux->valor = item;
};

void ListaEncadeada::InsereInicio(int item) {

};

void ListaEncadeada::InsereFinal(int item) {

};

void ListaEncadeada::InserePosicao(int item, int pos) {

};

int ListaEncadeada::RemoveInicio() {
    return 0;
};

int ListaEncadeada::RemoveFinal() {
    return 0;
};

int ListaEncadeada::RemovePosicao(int pos) {
    return 0;
};

int ListaEncadeada::Pesquisa(int c) {
    return 0;
};

void ListaEncadeada::Imprime() {

};

void ListaEncadeada::Limpa() {

};

Node* ListaEncadeada::Posiciona(int pos, bool antes) {
    return nullptr;
};