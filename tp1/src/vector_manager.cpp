#include "vector_manager.hpp"
#include <iostream>

void vectorManager::initSeed(int seed){
    srand(seed);
};

void vectorManager::initVector(int vetor[], int size){
    for (int i = 0; i < size; i++){
        vetor[i] = rand() % size;
    };
};

void vectorManager::printVector(int vetor[], int size){
    for (int i = 0; i < size; i++){
        std::cout << vetor[i] << " ";
    };
    std::cout << std::endl;
};

void vectorManager::shuffleVector(int* vet, int size, int numShuffle){
    int p1 = 0, p2 = 0;
    for (int t = 0; t < numShuffle; t++){
        /* Gera dois índices distintos no intervalo [0..size-1] */
        while (p1 == p2){   
            p1 = rand() % size;
            p2 = rand() % size;
        }
        /* Realiza a troca para introduzir uma quebra */
        int temp = vet[p1];
        vet[p1] = vet[p2];
        vet[p2] = temp;
        p1 = p2 = 0;
    }
}