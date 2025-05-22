#include <iostream>
#include <fstream>

#include "ordenador_universal.hpp"
#include "sorting_algorithms.hpp" 
#include "vector_manager.hpp" 
#include "stats.hpp" 

// void tests(){

//     Stats stats1(0.0121560, -0.0063780, 0.0172897);
//     Stats stats2(0.0121560, -0.0063780, 0.0172897);
//     stats2.printStats();
//     int seed = 200000;
//     int size = 1000;
//     int* vector = new int[size];

//     vectorManager::initSeed(seed);
//     vectorManager::initVector(vector, size);
//     // std::cout << "Initial vector: ";
//     // vectorManager::printVector(vector, size);
    
    
//     std::cout << "################################" << std::endl;

//     SortingAlgorithms::insertionSort(vector, 0, size - 1, &stats1);
//     // std::cout << "Sorted vector: ";
//     // vectorManager::printVector(vector, size);
//     stats1.printStats();
    
//     std::cout << "################################" << std::endl;
    
//     vectorManager::initSeed(seed);
//     vectorManager::initVector(vector, size);
    
//     SortingAlgorithms::quickSort3Ins(vector, 0, size - 1, &stats2);
//     // std::cout << "Sorted vector: ";
//     // vectorManager::printVector(vector, size);
//     stats2.printStats();
    
// }

// int main() {
//     tests();
//     return 0;
// }

int main(int argc, char* argv[]) {

    tests();

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

    int linha;
    for(int i=0; i<tam; i++) {
        arquivo >> linha;
        vetor[i] = linha;
    };

    arquivo.close();

    return 0;
}