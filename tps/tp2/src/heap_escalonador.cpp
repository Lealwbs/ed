#include "../include/heap_escalonador.hpp"
#include <iostream>

HeapEscalonador::HeapEscalonador(int capacidade_max){
    this->capacidade_max = capacidade_max;
    this->tamanho = 0;
    this->eventos = new Evento*[capacidade_max]; // Inicializa o array de ponteiros para eventos com a capacidade máxima especificada
}

HeapEscalonador::~HeapEscalonador() {
    for (int i = 0; i < tamanho; ++i) {
        delete eventos[i];
    }
    delete[] eventos;
}

void HeapEscalonador::InserirEvento(Evento* evento) {
    if (tamanho >= capacidade_max) {
        AumentarCapacidade();
    }

    eventos[tamanho] = evento;
    HeapifyPorCima(tamanho);
    ++tamanho;
}

Evento* HeapEscalonador::ExtrairEvento() {
    if (Vazio()) return nullptr;

    Evento* evento_raiz = eventos[0];
    eventos[0] = eventos[tamanho - 1];
    tamanho--;

    if (!Vazio()) HeapifyPorBaixo(0);

    return evento_raiz;
};

bool HeapEscalonador::Vazio() { return tamanho == 0; };
int HeapEscalonador::GetAncestral(int posicao) { return (posicao - 1) / 2; };
int HeapEscalonador::GetSucessorEsq(int posicao) { return 2 * posicao + 1; };
int HeapEscalonador::GetSucessorDir(int posicao) { return 2 * posicao + 2; };

void HeapEscalonador::HeapifyPorBaixo(int posicao) {
    int esq = GetSucessorEsq(posicao);
    int dir = GetSucessorDir(posicao);
    int menor = posicao;

    if (esq < tamanho && eventos[esq]->GetPrioridade() < eventos[menor]->GetPrioridade()) {
        menor = esq;
    };

    if (dir < tamanho && eventos[dir]->GetPrioridade() < eventos[menor]->GetPrioridade()) {
        menor = dir;
    };

    if (menor != posicao) {
        std::swap(eventos[posicao], eventos[menor]);
        HeapifyPorBaixo(menor);
    };
};

void HeapEscalonador::HeapifyPorCima(int posicao) {
    while (posicao > 0) {
        int ancestral = GetAncestral(posicao);

        if (eventos[posicao]->GetPrioridade() < eventos[ancestral]->GetPrioridade()) {
            std::swap(eventos[posicao], eventos[ancestral]);
            posicao = ancestral;
        } else {
            break;
        };
    };
};

void HeapEscalonador::AumentarCapacidade() {
    capacidade_max *= 2; // Dobra a capacidade máxima
    if (capacidade_max == 0) capacidade_max = 1; // Se a capacidade máxima for 0, inicializa com 1

    Evento** novo_array = new Evento*[capacidade_max];

    for (int i = 0; i < tamanho; ++i) {
        novo_array[i] = eventos[i];
    };

    delete[] eventos;
    eventos = novo_array;
};
