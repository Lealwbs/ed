#include "heap.hpp"
#include <iostream>
#include <vector>
#include <list>

int main(){

    int tamMinHeap = 0, entrada;
    std::cin >> tamMinHeap;
    // std::cout << "Tamanho Heap: " << tamMinHeap << std::endl;

    if(entrada == 0){};

    class Heap MinHeap(tamMinHeap);

    for(int i=0; i<tamMinHeap; i++){
        std::cin >> entrada;
        MinHeap.Inserir(entrada);
    };

    for(int i=0; i<tamMinHeap; i++){
        std::cout <<  MinHeap.Remover() << ' '; //  << std::endl;
    }; 
    std::cout << std::endl;

    return 0;
}