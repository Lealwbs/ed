#include "heap.hpp"

Heap::Heap(int maxsize){
    this->tamanho = 0;
    this->data = new int[maxsize];
};

Heap::~Heap(){
    this->tamanho = 0;
    delete[] data;
};

void Heap::Inserir(int x){
    this->data[this->tamanho] = x;
    (this->tamanho)++;
};

int Heap::Remover(){
    if( this->tamanho == 0 ){
        return -1;
    };

    int tmp_first_element = data[0];
    for(int i=0; i<(this->tamanho-1); i++){
    data[i] = data[i+1];
    };

    data[tamanho-1] = 0;
    this->tamanho--;

    return tmp_first_element;
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
    
//void HeapifyPorBaixo(int posicao);
//void HeapifyPorCima(int posicao); 

