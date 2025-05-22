#include "vector_manager.hpp"
#include <iostream>

void vectorManager::initSeed(int seed){
    srand48(seed);
};

void vectorManager::initVector(int array[], int size){
    for (int i = 0; i < size; i++){
        array[i] = (int)(drand48() * size);
    };
};

void vectorManager::printVector(int array[], int size){
    for (int i = 0; i < size; i++){
        std::cout << array[i] << " ";
    };
    std::cout << std::endl;
};
