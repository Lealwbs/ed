#include <iostream>
#include <string>
#include "graph.hpp"

int main(){

    List Vetor;

    Vetor.addNode(1);
    Vetor.addNode(2);
    Vetor.addNode(2);
    Vetor.addNode(2);

    Vetor.printList();
    std::cout << Vetor.getSize() << std::endl;
    return 0;

}

// int main(int argc, char* argv[]){

//     Grafo grafo = Grafo();

//     int qtde_vertices;
//     std::cin >> qtde_vertices;
//     // std::cout << "qtde_vertices: "; 
//     // std::cout << qtde_vertices << std::endl;

//     for(int i = 0; i < qtde_vertices; i++){
//         int qtde_vizinhos;
//         std::cin >> qtde_vizinhos;
//         grafo.InsereVertice();
//         // std::cout << "qtde_vizinhos: ";
//         // std::cout << qtde_vizinhos << std::endl;

//         for (int j = 0; j < qtde_vizinhos; j++){
//             int vizinho;
//             std::cin >> vizinho;
//             grafo.InsereAresta(i, vizinho);
//             // std::cout << "vizinho: ";
//             // std::cout << vizinho << std::endl;
//         }
//     }

//     std::string operacao;
//     operacao = argv[1];
//     // std::cin >> operacao;
//     // std::cout << "operacao: " << operacao << std::endl;
//     // int input_buffer;

//     if (operacao == "-d"){

//         std::cout << "Quantidade de vértices: " << grafo.QuantidadeVertices() << std::endl;
//         std::cout << "Quantidade de arestas: " << grafo.QuantidadeArestas() << std::endl;
//         std::cout << "Grau mínimo: " << grafo.GrauMinimo() << std::endl;
//         std::cout << "Grau máximo: " << grafo.GrauMaximo() << std::endl;

//     } else if (operacao == "-n"){

//         for(int i = 0; i < qtde_vertices; i++){
//             std::cout << "Vizinhos do vértice " << i << ": ";
//             grafo.ImprimeVizinhos(i);
//             std::cout << std::endl;
//         }

//     } else if (operacao == "-k"){

//         if (grafo.QuantidadeArestas() == (qtde_vertices * (qtde_vertices - 1)) / 2){
//             std::cout << "Grafo completo" << std::endl;
//         } else {
//             std::cout << "Grafo incompleto" << std::endl;
//         }

//     } else {

//         std::cout << "Operação inválida" << std::endl;
//     }

//     return 0;
// }