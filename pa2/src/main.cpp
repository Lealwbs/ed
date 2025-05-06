#include <iostream>
#include <string>
#include "graph.hpp"

int main(int argc, char* argv[]){

    Grafo grafo = Grafo();

    int qtde_vertices, qtde_vizinhos, vizinho;

    //std::cout << "Digite a quantidade de vertices: ";
    std::cin >> qtde_vertices;

    for(int i = 0; i < qtde_vertices; i++){
        grafo.InsereVertice();
        //std::cout << "Digite a quantidade de vizinhos do vertice " << i << ": ";
        std::cin >> qtde_vizinhos;

        for (int j = 0; j < qtde_vizinhos; j++){
            //std::cout << "Vizinho " << j << ": "; 
            std::cin >> vizinho;
            grafo.InsereAresta(i, vizinho);
        }
    }

    std::string operacao;
    operacao = argv[1];

    if (operacao == "-d"){

        std::cout << "Quantidade de vertices: " << grafo.QuantidadeVertices() << std::endl;
        std::cout << "Quantidade de arestas: " << grafo.QuantidadeArestas() << std::endl;
        std::cout << "Grau minimo: " << grafo.GrauMinimo() << std::endl;
        std::cout << "Grau maximo: " << grafo.GrauMaximo() << std::endl;

    } else if (operacao == "-n"){

        grafo.ImprimeVizinhos(0);

    } else if (operacao == "-k"){

        if (grafo.QuantidadeArestas() == (qtde_vertices * (qtde_vertices - 1)) / 2){
            std::cout << "Grafo completo" << std::endl;
        } else { std::cout << "Grafo incompleto" << std::endl; }

    } else {
        
        std::cout << "Operação inválida" << std::endl;
    }

    return 0;
}