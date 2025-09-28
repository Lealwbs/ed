#ifndef ORDENADOR_HPP
#define ORDENADOR_HPP

#include <vector>
#include "../include/sorting_algorithms.hpp"
#include "../include/stats.hpp"

class Ordenador {

    public:
        Ordenador();
        ~Ordenador();

        void OrdenadorUniversal(int vetor[], int tam, int minTamParticao, int limiarQuebras);
        int getNumeroQuebras(int vetor[], int tam);
        
        void calculaNovaFaixa(double limParticao, int* minMPS, 
            int* maxMPS, int* passoMPS, int* numMPS, int *minNumMPS, int *maxNumMPS);
        int getMPS(int minMPS, int passoMPS, int num);

        // Limiar de Partição
        Stats LimPart_Stats[10];
        int LimPart_determinaLimiar(int vetor[], int vetorCopia[], int tam, double limiarCusto);
        int LimPart_menorCusto(int numMPS);
        
        // Limiar de Quebras
        Stats InsSort_Stats[10];
        Stats QuickSort_Stats[10];
        int LimQueb_determinaLimiar(int vetor[], int seed, int tam, double limiarCusto);
        int LimQueb_menorCusto(int numMPS, float* menorCustoOutput);

        
    private:

};

#endif 
