#include "../include/unionFind.hpp"
#include <iostream>

void printArestas(Aresta* vetor, int tamanho){
    for(int i=0; i<tamanho; i++){
        std::cout << vetor[i].u << " ";
        std::cout << vetor[i].v << " ";
        std::cout << vetor[i].custo << std::endl;
    };
};

int calcularArvoreGeradoraMinima(Aresta* vetor, int qtdeVertices, int qtdeArestas){
    return qtdeVertices + qtdeArestas;
};

int main() {
        
    int qtdeVertices;
    int qtdeArestas;

    std::cin >> qtdeVertices >> qtdeArestas;

    Aresta arestas[qtdeArestas];

    for(int i=0; i<qtdeArestas; i++){
        std::cin >> arestas[i].u;
        std::cin >> arestas[i].v;
        std::cin >> arestas[i].custo;
    };

    // printArestas(arestas, qtdeArestas);

    int valorAGM = calcularArvoreGeradoraMinima(arestas, qtdeVertices, qtdeArestas);

    std::cout << valorAGM << std::endl; 

    return 0;
};