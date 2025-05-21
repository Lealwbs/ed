#include "vector_manager.hpp"
#include <iostream>

void vectorManager::initVector(int *vet, int size){
    for (int i = 0; i < size; i++){
        vet[i] = (int)(drand48() * size);
    };
};

void vectorManager::printVector(int *vet, int size){
    for (int i = 0; i < size; i++){
        std::cout << vet[i] << " ";
    };
    std::cout << std::endl;
};
