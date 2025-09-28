#include "../include/linked_list.hpp"
#include <iostream>

ListaEncadeada::ListaEncadeada() {
    primeiro = new Node;
    primeiro->valor = -1;
    primeiro->prox = nullptr;
    ultimo = primeiro;
    tamanho = 0;
};

ListaEncadeada::~ListaEncadeada() {
    Limpa();
    delete primeiro;
};

int ListaEncadeada::GetItem(int pos) {
    if (pos <= 0 || pos > tamanho)
        throw std::runtime_error("ERRO: Posicao invalida!");

    Node* aux = Posiciona(pos);
    return aux->valor;
};

void ListaEncadeada::SetItem(int item, int pos) {
    if (pos <= 0 || pos > tamanho)
        throw std::runtime_error("ERRO: Posicao invalida!");

    Node* aux = Posiciona(pos);
    aux->valor = item;
};

void ListaEncadeada::InsereInicio(int item) {
    Node* novo = new Node;
    novo->valor = item;
    novo->prox = primeiro->prox;
    primeiro->prox = novo;

    if (novo->prox == nullptr)
        ultimo = novo;

    tamanho++;
};

void ListaEncadeada::InsereFinal(int item) {
    Node* novo = new Node;
    novo->valor = item;
    novo->prox = nullptr;

    ultimo->prox = novo;
    ultimo = novo;

    tamanho++;
};

void ListaEncadeada::InserePosicao(int item, int pos) {
    if (pos <= 0 || pos > tamanho)
        throw std::runtime_error("ERRO: Posicao invalida!");

    Node* antes = Posiciona(pos, true);

    Node* novo = new Node;
    novo->valor = item;

    novo->prox = antes->prox;
    antes->prox = novo;

    if (novo->prox == nullptr)
        ultimo = novo;

    tamanho++;
};

int ListaEncadeada::RemoveInicio() {
    if (tamanho == 0)
        throw std::runtime_error("ERRO: Lista vazia!");

    Node* remover = primeiro->prox;
    primeiro->prox = remover->prox;

    tamanho--;
    int aux = remover->valor;

    if (primeiro->prox == nullptr)
        ultimo = primeiro;

    delete remover;
    return aux;
};

int ListaEncadeada::RemoveFinal() {
    if (tamanho == 0)
        throw std::runtime_error("ERRO: Lista vazia!");

    int aux = ultimo->valor;

    Node* penultimo = Posiciona(tamanho, true);
    penultimo->prox = nullptr;

    delete ultimo;
    ultimo = penultimo;

    tamanho--;
    return aux;
};

int ListaEncadeada::RemovePosicao(int pos) {
    if (pos <= 0 || pos > tamanho)
        throw std::runtime_error("ERRO: Posicao invalida ou Lista Vazia!");

    int aux;

    Node* antes = Posiciona(pos, true);
    Node* remover = antes->prox;
    antes->prox = remover->prox;

    aux = remover->valor;
    delete remover;

    if (antes->prox == nullptr)
        ultimo = antes;

    tamanho--;
    return aux;
};

int ListaEncadeada::Pesquisa(int c) {
    if (tamanho == 0)
        throw std::runtime_error("ERRO: Lista vazia!");

    Node* aux = primeiro->prox;
    for (int i = 1; i <= tamanho; i++) {
        if (aux->valor == c)
            return i;
        aux = aux->prox;
    };
    return -1;
};

void ListaEncadeada::Imprime() {
    Node* aux = primeiro->prox;
    for (int i = 0; i < tamanho; i++) {
        std::cout << aux->valor << " ";
        aux = aux->prox;
    };
    std::cout << std::endl;
};

void ListaEncadeada::Limpa() {
    if (tamanho == 0)
        return;

    Node* remover = primeiro->prox;
    while(tamanho){
        primeiro->prox = remover->prox;
        delete remover;
        remover = primeiro->prox;
        tamanho--;
    };

    ultimo = primeiro;
};

Node* ListaEncadeada::Posiciona(int pos, bool antes) {
    if (pos <= 0 || pos > tamanho || tamanho == 0)
        throw std::runtime_error("ERRO: Posicao invalida ou Lista Vazia!");

    Node* aux = primeiro;
    for (int i = 0; i < (pos - 1 + !antes); i++) {
        aux = aux->prox;
    };
    return aux;
};