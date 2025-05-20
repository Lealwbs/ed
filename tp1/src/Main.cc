#include "Test.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {

    std::ifstream arquivo(argv[1]);

    if (!arquivo.is_open()){
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    };

    int seed; // Semente aleatória
    double limiarCusto; // Limiar de Convergência
    double a; // Coeficiente das Comparações:
    double b; // Coeficiente das Movimentações
    double c; // Coeficieinte das Chamadas
    int tam; // Número de Chaves

    arquivo >> seed >> limiarCusto >> a >> b >> c >> tam;

    std::cout << "seed: " << seed << std::endl;
    std::cout << "limiarCusto: " << limiarCusto << std::endl;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "tam: " << tam << std::endl;

    int* vetor = new int[tam];

    std::string linha;
    for(int i=0; i<tam; i++) {
        arquivo >> linha;
        vetor[i] = stoi(linha);
    };

    ///////////////// IMPRIMIR VETOR /////////////////
    // std::cout << "##################" << std::endl;
    // for(int i=0; i<tam; i++) {
    //     std::cout << vetor[i] << std::endl;
    // };
    
    // Test* pTest = new Test();
    // pTest->Print();
    arquivo.close();
    return 0;
}