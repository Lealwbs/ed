#include <iostream>
#include <fstream>

#include "ordenador_universal.hpp"
#include "sorting_algorithms.hpp" 
#include "vector_manager.hpp" 
#include "stats.hpp" 

void tests(){

    SortingAlgorithms SortData;

    double a = 0.0121560;
    double b = -0.0063780;
    double c = 0.0172897;

    SortData.stats.setAtributes(a, b, c);

    int seed = 1;
    int size = 30;
    int* vector = new int[size];

    vectorManager::initSeed(seed);
    vectorManager::initVector(vector, size);
    // std::cout << "Initial vector: ";
    vectorManager::printVector(vector, size);
    
    
    std::cout << "InsertionSort ################################" << std::endl;

    SortingAlgorithms::InsertionSort(vector, size);
    // std::cout << "Sorted vector: ";
    vectorManager::printVector(vector, size);
    SortData.stats.printStats();
    SortData.stats.resetCounter();
    
    std::cout << "QuickSort ################################" << std::endl;
    
    vectorManager::initSeed(seed);
    vectorManager::initVector(vector, size);
    
    SortingAlgorithms::QuickSort(vector, size);
    // std::cout << "Sorted vector: ";
    vectorManager::printVector(vector, size);
    SortData.stats.printStats();
    
}

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

    // std::cout << "seed: " << seed << std::endl;
    // std::cout << "limiarCusto: " << limiarCusto << std::endl;
    // std::cout << "a: " << a << std::endl;
    // std::cout << "b: " << b << std::endl;
    // std::cout << "c: " << c << std::endl;
    // std::cout << "tam: " << tam << std::endl;

    int* array = new int[tam];

    int linha;
    for(int i=0; i<tam; i++) {
        arquivo >> linha;
        array[i] = linha;
    };

    arquivo.close();

    return 0;
}