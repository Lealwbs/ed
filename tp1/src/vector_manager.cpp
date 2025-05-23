#include "../include/vector_manager.hpp"
#include <iostream>

void vectorManager::initSeed(int seed){
    // srand(seed);
    srand48(seed);

};

void vectorManager::initVector(int array[], int size){
    for (int i = 0; i < size; i++){
        // array[i] = rand() % size;
        array[i] = (int)(drand48() * size);
    };
};

void vectorManager::printVector(int array[], int size){
    for (int i = 0; i < size; i++){
        std::cout << array[i] << " ";
    };
    std::cout << std::endl;
};

void vectorManager::shuffleVector(int array[], int size, int numShuffle){
    int p1 = 0, p2 = 0;
    for (int t = 0; t < numShuffle; t++){
        /* Gera dois índices distintos no intervalo [0..size-1] */
        while (p1 == p2){   
            // p1 = rand() % size;
            // p2 = rand() % size;
            p1 = (int)(drand48() * size);
            p2 = (int)(drand48() * size);
        }
        /* Realiza a troca para introduzir uma quebra */
        int temp = array[p1];
        array[p1] = array[p2];
        array[p2] = temp;
        p1 = p2 = 0;
    }
}

void vectorManager::copyVector(int source[], int destination[], int size){
    for (int i = 0; i < size; i++){
        destination[i] = source[i];
    }
}