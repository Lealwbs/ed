#include "heap.hpp"
#include <iostream>
#include <algorithm> // para std::swap

Heap::Heap(int maxsize){
    this->tamanho = 0;
    this->data = new int[maxsize];
};

Heap::~Heap(){
    this->tamanho = 0;
    delete[] data;
};

void Heap::Inserir(int x){
    data[tamanho] = x;

    HeapifyPorCima(tamanho);
    tamanho++;

    // std::cout << "HEAP: ";
    // for(int j=0; j<tamanho; j++){
    //     std::cout << data[j] << " ";
    // };
    // std::cout << std::endl;
};

int Heap::Remover(){
    if( tamanho == 0 ) return -1;
 
    int first_element = data[0];
    data[0] = data[tamanho-1];
    tamanho--;

    HeapifyPorBaixo(0);
    return first_element;
};

//Retorna true caso o heap esteja vazio, false caso contrário.
bool Heap::Vazio(){
    return (this->tamanho == 0);
};

int Heap::GetAncestral(int posicao){
    return (posicao + (posicao%2) - 2) / 2;
};

int Heap::GetSucessorEsq(int posicao){
    return (posicao * 2) + 1;
};

int Heap::GetSucessorDir(int posicao){
    return (posicao * 2) + 2;
};

// Funções necessárias para implementar o Heapify recursivo
// Você pode apagar elas caso decida implementar o Heapify iterativo
    
void Heap::HeapifyPorCima(int posicao){
    if(posicao == 0) return;
    int pai = GetAncestral(posicao);

    if(data[pai] > data[posicao]){
        int tmp = data[pai];
        data[pai] = data[posicao];
        data[posicao] = tmp;

        HeapifyPorCima(pai);
    };
};

void Heap::HeapifyPorBaixo(int posicao){
    int menor = posicao;
    int esq = GetSucessorEsq(posicao);
    int dir = GetSucessorDir(posicao);

    if(esq < tamanho && data[esq] < data[menor]) menor = esq;
    if(dir < tamanho && data[dir] < data[menor]) menor = dir;

    if(menor != posicao){
        int tmp = data[posicao];
        data[posicao] = data[menor];
        data[menor] = tmp;

        HeapifyPorBaixo(menor);
    };
};

