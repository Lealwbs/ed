#ifndef ORDENADOR
#define ORDENADOR_HPP

#include <vector>
#include "../include/sorting_algorithms.hpp"
#include "../include/stats.hpp"

class Ordenador {

    public:

        Ordenador();
        ~Ordenador();

        void OrdenadorUniversal(int vetor[], int tam, int minTamParticao, int limiarQuebras);
        int determinaLimiarParticao(int vetor[], int tam, double limiarCusto);
        int determinaLimiarQuebras(int vetor[], int tam, double limiarCusto);
    
        int getNumeroQuebras(int vetor[], int tam);

    private:
        int numQuebras;
        int tam;

        Stats Default_Stats[10];
        Stats InsrtSort_Stats[10];
        Stats QuickSort_Stats[10];


        int MPS_step(int max, int min);
        int LQ_step(int max, int min);


        void registraEstatisticas(double custo);



        void MPS_imprimeEstatisticas(double custo);
        void LQ_imprimeEstatisticas(double custo);



        void calculaNovaFaixa(int limiarParticao, int minMPS, int maxMPS, int passoMPS, int numMPS);
        int menorCusto();


};

#endif 
