#include "heap.hpp"
#include <iostream>
#include <vector>

int main(){
    //class Heap MinHeap;

    int tamMinHeap = 0, entrada;
    std::cin >> tamMinHeap;
    std::cout << tamMinHeap << std::endl;

    int Vetor[tamMinHeap];

    for(int i=0; i<tamMinHeap; i++){

        std::cin >> entrada;
        Vetor[i] = entrada;
        //inserir entrada na estrutura de dados na ordem de leitura
        //minheapsize ++ 



        //remover todos os elementos do minheap e imprimilos na ordem de remoção separados por " ", com endl;


    };

    for(int i=0; i<tamMinHeap; i++){
        std::cout <<  Vetor[i] << ' '; //  << std::endl;
    }; 
    std::cout << std::endl;
    return 0;
}