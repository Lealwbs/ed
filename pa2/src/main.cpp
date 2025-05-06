#include <iostream>
#include <string>
#include "graph.hpp"

// int main(){

//     // List Vetor;

//     // Vetor.addNode(1);
//     // Vetor.addNode(2);
//     // Vetor.addNode(2);
//     // Vetor.addNode(2);

//     // Vetor.printList();
//     // std::cout << Vetor.getSize() << std::endl;
//     // return 0;

//     ListaAdjacencia vetor;

//     std::cout << vetor.getSizeLista() << std::endl;
//     vetor.addManyNodeVertices(6);
//     std::cout << vetor.getSizeLista() << std::endl;
    
//     vetor.addAresta(0, 2);
//     vetor.addAresta(0, 5);

//     vetor.addAresta(1, 2);
//     vetor.addAresta(1, 4);
//     vetor.addAresta(1, 5);

//     vetor.addAresta(2, 0);
//     vetor.addAresta(2, 1);
//     vetor.addAresta(2, 4);

//     vetor.addAresta(3, 5);
    
//     vetor.addAresta(4, 1);
//     vetor.addAresta(4, 2);

//     vetor.addAresta(5, 0);
//     vetor.addAresta(5, 1);
//     vetor.addAresta(5, 3);
    
//     vetor.printListaInformation();


// }

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

    std::cout << std::endl;
    grafo.ImprimeVizinhos(0);

    // std::string operacao;
    // operacao = argv[1];

    // if (operacao == "-d"){

    //     std::cout << "Quantidade de vértices: " << grafo.QuantidadeVertices() << std::endl;
    //     std::cout << "Quantidade de arestas: " << grafo.QuantidadeArestas() << std::endl;
    //     std::cout << "Grau mínimo: " << grafo.GrauMinimo() << std::endl;
    //     std::cout << "Grau máximo: " << grafo.GrauMaximo() << std::endl;

    // } else if (operacao == "-n"){

    //     for(int i = 0; i < qtde_vertices; i++){
    //         std::cout << "Vizinhos do vértice " << i << ": ";
    //         grafo.ImprimeVizinhos(i);
    //         std::cout << std::endl;
    //     }

    // } else if (operacao == "-k"){

    //     if (grafo.QuantidadeArestas() == (qtde_vertices * (qtde_vertices - 1)) / 2){
    //         std::cout << "Grafo completo" << std::endl;
    //     } else {
    //         std::cout << "Grafo incompleto" << std::endl;
    //     }

    // } else {

    //     std::cout << "Operação inválida" << std::endl;
    // }

    return 0;
}