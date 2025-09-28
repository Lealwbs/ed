#include "../include/ordenador.hpp"
#include "../include/vector_manager.hpp"
#include <math.h>
#include <iostream>
#include <iomanip>

Ordenador::Ordenador(){};
Ordenador::~Ordenador(){};

void Ordenador::OrdenadorUniversal(int vetor[], int tam, int minTamParticao, int limiarQuebras){
    if ( getNumeroQuebras(vetor, tam) < limiarQuebras ) {
        SortingAlgorithms::InsertionSort(vetor, tam);
    } else {
        if (tam > minTamParticao) {
            SortingAlgorithms::QuickSort(vetor, tam);
        } else {
            SortingAlgorithms::InsertionSort(vetor, tam);
        }
    }
}

int Ordenador::getNumeroQuebras(int vetor[], int tam){
    int numQuebras = 0;
    for (int i = 0; i < tam - 1; i++) {
        if (vetor[i] > vetor[i + 1]) {
            numQuebras++;
        }
    }
    return numQuebras;
}

void Ordenador::calculaNovaFaixa(double limParticao, int* minMPS, int* maxMPS, int* passoMPS, int* numMPS, int *minNumMPS, int *maxNumMPS){
    int newMin, newMax, tmpMin;
    if (limParticao == 0){
        newMin = 0;
        newMax = 2;
    } else if(limParticao == *numMPS-1){
        newMin = *numMPS - 3;
        newMax = *numMPS - 1;
    } else{
        newMin = limParticao - 1;
        newMax = limParticao + 1;
    };

    *minNumMPS = newMin;
    *maxNumMPS = newMax;

    tmpMin = *minMPS;
    *minMPS = getMPS(tmpMin, *passoMPS, newMin);
    *maxMPS = getMPS(tmpMin, *passoMPS, newMax);

    *passoMPS = (int)((*maxMPS-*minMPS)/5);
    if(*passoMPS == 0) (*passoMPS)++;
    };

int Ordenador::getMPS(int minMPS, int passoMPS, int num){
    return minMPS + (passoMPS * num);
}

////////////////////////////////////////////////////////////////////
// LIMIAR DE PARTIÇÃO //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

int Ordenador::LimPart_determinaLimiar(int vetor[], int vetorCopia[], int tam, double limiarCusto) {
    int minMPS = 2;
    int maxMPS = tam;
    int numMPS = 0;
    int passoMPS = (int)(maxMPS - minMPS)/5;
    float diffCusto = 0.0;
    int limiarParticao;
    int iter = 0;

    do {
        std::cout << "iter " << iter << std::endl;
        numMPS = 0;

        for (int t = minMPS; t <= maxMPS; t += passoMPS) {
            vectorManager::copyVector(vetorCopia, vetor, tam);
            SortingAlgorithms::setQuickSortSize(t);
            SortingAlgorithms::stats.resetCounter();

            OrdenadorUniversal(vetor, tam, t, 0);

            SortingAlgorithms::stats.calculateCost();
            SortingAlgorithms::stats.setMinTamParticao(t);
            LimPart_Stats[numMPS] = SortingAlgorithms::stats;

            SortingAlgorithms::stats.printStats_LimPart();

            numMPS++;
        }

        limiarParticao = LimPart_menorCusto(numMPS);
        int posMinMPS, posMaxMPS;

        calculaNovaFaixa(limiarParticao, &minMPS, &maxMPS, &passoMPS, &numMPS, &posMinMPS, &posMaxMPS);

        diffCusto = std::fabs(LimPart_Stats[posMinMPS].getCost() - LimPart_Stats[posMaxMPS].getCost());

        std::cout << "nummps " << numMPS << " ";
        std::cout << "limParticao " << LimPart_Stats[limiarParticao].getMinTamParticao() << " ";
        std::cout << "mpsdiff " << std::fixed << std::setprecision(6) << diffCusto << std::endl << std::endl;

        if (iter++ >= 5) {
            std::cout << "Max iterations reached." << std::endl;
            break;
        }

    } while ((diffCusto > limiarCusto) && (numMPS >= 5));

    return LimPart_Stats[limiarParticao].getMinTamParticao();
}

int Ordenador::LimPart_menorCusto(int numMPS) {
    int indexMenorCusto;
    double custo, menorCusto;

    for(int i = 0; i < numMPS; i++){
        custo = fabs(LimPart_Stats[i].getCost());

        if(i == 0 || (custo < menorCusto && custo > 0)){
            menorCusto = custo;
            indexMenorCusto = i;
        }
    }

    return indexMenorCusto;
    }

////////////////////////////////////////////////////////////////////
// LIMIAR DE QUEBRA ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

int Ordenador::LimQueb_determinaLimiar(int vetor[], int seed, int tam, double limiarCusto) {
    int minMPS = 1;
    int maxMPS = (int)(tam/2);
    int numMPS = 20;
    int passoMPS = (int)(maxMPS - minMPS)/5;
    float diffCusto = limiarCusto + 1;
    int limiarQuebras;
    int iter = 0;

    #define QUICK_SORT 1
    #define INSERTION_SORT 2

    do {
        std::cout << "iter " << iter << std::endl;
        numMPS = 0;

        for (limiarQuebras = minMPS; limiarQuebras <= maxMPS; limiarQuebras += passoMPS) {
            vectorManager::initSeed(seed);
            vectorManager::shuffleVector(vetor, tam, limiarQuebras);
            SortingAlgorithms::stats.resetCounter();
            SortingAlgorithms::QuickSort(vetor, tam); 
            SortingAlgorithms::stats.setNumQuebras(limiarQuebras);
            SortingAlgorithms::stats.calculateCost();
            QuickSort_Stats[numMPS] = SortingAlgorithms::stats;
            SortingAlgorithms::stats.printStats_LimQuebras(QUICK_SORT);

            vectorManager::initSeed(seed);
            vectorManager::shuffleVector(vetor, tam, limiarQuebras);
            SortingAlgorithms::stats.resetCounter();
            SortingAlgorithms::InsertionSort(vetor, tam);   
            SortingAlgorithms::stats.setNumQuebras(limiarQuebras);
            SortingAlgorithms::stats.calculateCost();
            InsSort_Stats[numMPS] = SortingAlgorithms::stats;
            SortingAlgorithms::stats.printStats_LimQuebras(INSERTION_SORT);

            numMPS++;
        }
        
        int posMinMPS, posMaxMPS;
        float tmp;
        limiarQuebras = LimQueb_menorCusto(numMPS, &tmp);
        calculaNovaFaixa(limiarQuebras, &minMPS, &maxMPS, &passoMPS, &numMPS, &posMinMPS, &posMaxMPS);
        
        // std::cout << "nova faixa: <" << minMPS << ", " << maxMPS << "> " << std::endl;
        // std::cout << "nova posicao: <" << posMinMPS << ", " << posMaxMPS << "> " << std::endl;
        // std::cout << "In Max Cost: " << InsSort_Stats[posMaxMPS].getCost() << " " << std::endl;
        // std::cout << "In Max Cost: " << InsSort_Stats[posMinMPS].getCost() << " " << std::endl;
        // std::cout << "In Max - Min Cost: " << InsSort_Stats[posMaxMPS].getCost() - InsSort_Stats[posMinMPS].getCost() << " " << std::endl;

        diffCusto = std::fabs(InsSort_Stats[posMaxMPS].getCost() - InsSort_Stats[posMinMPS].getCost());

        std::cout << "numlq " << numMPS << " ";
        std::cout << "limQuebras " << QuickSort_Stats[limiarQuebras].getNumQuebras() << " ";
        std::cout << "lqdiff " << std::fixed << std::setprecision(6) << diffCusto << std::endl << std::endl;

        iter++;
        // if (iter++ >= 5) {
        //     std::cout << "Max iterations reached. " << std::endl;
        //     break;
        // }

    } while ((diffCusto > limiarCusto) && (numMPS >= 5));

    return limiarQuebras;
}

int Ordenador::LimQueb_menorCusto(int numMPS, float* menorCustoOutput) {
    int indexMenorCusto;
    double custo, menorCusto;
    double custoQuickSort, custoInsertionSort;

    for(int i = 0; i < numMPS; i++){
        custoQuickSort = (QuickSort_Stats[i].getCost());
        custoInsertionSort = (InsSort_Stats[i].getCost());

        // std::cout << "index: " << "diffCusto " << fabs(custoQuickSort - custoInsertionSort) << " ";
        // std::cout << std::endl;

        custo = fabs(custoQuickSort - custoInsertionSort);

        if(i==0 || (custo < menorCusto && custo != 0)){
            menorCusto = custo;
            indexMenorCusto = i;
        }
    }
    *menorCustoOutput = menorCusto;
    return indexMenorCusto;
}
