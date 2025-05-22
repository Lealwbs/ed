// include/ordenador_universal.hpp
#ifndef ORDENADOR_UNIVERSAL_HPP
#define ORDENADOR_UNIVERSAL_HPP

#include <vector>
#include "sorting_algorithms.hpp"
#include "stats.hpp"

class ordenador_Universal {

    private:
        int numQuebras;
        int seed;
        int* vetor;
        int tam;

        Stats Default_Stats[10];
        Stats InsrtSort_Stats[10];
        Stats QuickSort_Stats[10];

        ordenador_Universal();
        ~ordenador_Universal();
        int MPS_step(int max, int min);
        int LQ_step(int max, int min);


        void registraEstatisticas(double custo);



        void MPS_imprimeEstatisticas(double custo);
        void LQ_imprimeEstatisticas(double custo);



        void calculaNovaFaixa(int limiarParticao, int minMPS, int maxMPS, int passoMPS, int numMPS);
        int menorCusto();

    public:

        int getNumeroQuebras(int vetor[], int tam);
        void ordenadorUniversal(int vetor[], int tam, int minTamParticao, int limiarQuebras);
        int determinaLimiarParticao(int vetor[], int tam, double limiarCusto);
        int determinaLimiarQuebras(int vetor[], int tam, double limiarCusto);

};

#endif 
