#include "../include/array_list.hpp"
#include <iostream>

int ListaArranjo::GetItem(int pos) {
    if (pos < 0 || pos >= tamanho)
        return -1;

    return itens[pos];
};

void ListaArranjo::SetItem(int item, int pos) {
    if (pos < 0 || pos >= tamanho)
        return;
    itens[pos] = item;
};

void ListaArranjo::InsereInicio(int item) {
    if (tamanho >= MAXTAM)
        return;

    for (int i = tamanho; i > 0; i--) {
        itens[i] = itens[i - 1];
    };

    itens[0] = item;
    tamanho++;
};

void ListaArranjo::InsereFinal(int item) {
    if (tamanho >= MAXTAM)
        return;

    itens[tamanho] = item;
    tamanho++;
};

void ListaArranjo::InserePosicao(int item, int pos) {
    if (pos < 0 || pos > tamanho || tamanho >= MAXTAM)
        return;

    for (int i = tamanho; i > pos; i--) {
        itens[i] = itens[i - 1];
    };

    itens[pos] = item;
    tamanho++;
};

int ListaArranjo::RemoveInicio() {
    if (tamanho == 0)
        return -1;

    int aux = itens[0];
    for (int i = 0; i < tamanho - 1; i++) {
        itens[i] = itens[i + 1];
    };
    tamanho--;
    return aux;
};

int ListaArranjo::RemoveFinal() {
    if (tamanho == 0)
        return -1;

    int aux = itens[tamanho - 1];
    tamanho--;
    return aux;
};

int ListaArranjo::RemovePosicao(int pos) {
    if (pos < 0 || pos >= tamanho || tamanho == 0)
        return -1;

    int aux = itens[pos];

    for (int i = pos; i < tamanho - 1; i++) {
        itens[i] = itens[i + 1];
    };

    tamanho--;
    return aux;
};

int ListaArranjo::Pesquisa(int c) {
    int posicao = -1;
    for (int i = 0; i < tamanho; i++) {
        if (itens[i] == c) {
            posicao = i;
            break;
        };
    };
    return posicao;
};

void ListaArranjo::Imprime() {
    for (int i = 0; i < tamanho; i++) {
        std::cout << itens[i] << " ";
    };
    std::cout << std::endl;
};

void ListaArranjo::Limpa() {
    tamanho = 0;
};
