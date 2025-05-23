#include <iostream>
#include <fstream>

#include "../include/ordenador.hpp"
#include "../include/sorting_algorithms.hpp" 
#include "../include/vector_manager.hpp" 
#include "../include/stats.hpp" 

void tests(){

    SortingAlgorithms sort;

    double a = 0.0121560;
    double b = -0.0063780;
    double c = 0.0172897;

    sort.stats.setAtributes(a, b, c);

    int seed = 1;
    int size = 100;
    int* vector = new int[size];



    // vectorManager::initSeed(seed);
    // vectorManager::initVector(vector, size);
    // vectorManager::printVector(vector, size);
    
    Ordenador ordenador = Ordenador();
    
    // sort.stats.printStats();

    // std::cout << "Universal ################################" << std::endl;
    vectorManager::initSeed(seed);
    vectorManager::initVector(vector, size);
    ordenador.OrdenadorUniversal(vector, size, 50, 90);
    sort.stats.printStats();


    // std::cout << "InsertionSort ################################" << std::endl;
    sort.stats.resetCounter();
    vectorManager::initSeed(seed);
    vectorManager::initVector(vector, size);
    sort.InsertionSort(vector, size);
    sort.stats.printStats();


    // std::cout << "QuickSort ################################" << std::endl;
    sort.stats.resetCounter();
    vectorManager::initSeed(seed);
    vectorManager::initVector(vector, size);
    sort.QuickSort(vector, size, 50);
    sort.stats.printStats();

    // std::cout << "END ################################" << std::endl;
}

int main(int argc, char* argv[]) {

    //tests();

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
    int tamanhoArray; // Número de Chaves

    arquivo >> seed >> limiarCusto >> a >> b >> c >> tamanhoArray;

    // std::cout << "seed: " << seed << std::endl;
    // std::cout << "limiarCusto: " << limiarCusto << std::endl;
    // std::cout << "a: " << a << std::endl;
    // std::cout << "b: " << b << std::endl;
    // std::cout << "c: " << c << std::endl;
    // std::cout << "tamanhoArray: " << tam << std::endl;

    int* array = new int[tamanhoArray];
    int* arrayCopy = new int[tamanhoArray];

    // Inicializa os vetores com os valores do arquivo e fecha o arquivo.
    int linha;
    for(int i=0; i<tamanhoArray; i++) {
        arquivo >> linha;
        array[i] = linha;
        arrayCopy[i] = linha;
    };
    arquivo.close();

    Ordenador order = Ordenador();

    std::cout << "size " << tamanhoArray << " ";
    std::cout << "seed " << seed << " ";
    std::cout << "breaks " << order.getNumeroQuebras(array, tamanhoArray);
    std::cout << std::endl << std::endl;
    
    int limiarParticao = order.LimPart_determinaLimiar(arrayCopy, tamanhoArray, limiarCusto);
    
    // SortingAlgorithms::QuickSort(arrayCopy, tamanhoArray, limiarParticao);
    // int limiarQuebras = order.LimQueb_determinaLimiar(arrayCopy, tamanhoArray, limiarCusto);

    std::cout << std::endl;
    std::cout << "Limiar de Partição: " << limiarParticao << std::endl;
    // std::cout << "Limiar de Quebras: " << limiarQuebras << std::endl;

    delete[] array;
    delete[] arrayCopy;

    return 0;
}