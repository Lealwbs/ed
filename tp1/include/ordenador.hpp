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
        int getNumeroQuebras(int vetor[], int tam);
        
        void calculaNovaFaixa(int limiarParticao, int minMPS, int maxMPS, int passoMPS, int numMPS);

        // Limiar de Partição
        Stats LimPart_Stats[10];
        int LimPart_determinaLimiar(int vetor[], int tam, double limiarCusto);
        void LimPart_registraEstatisticas(double custo);
        void LimPart_imprimeEstatisticas(double custo);
        int LimPart_menorCusto();
        
        // Limiar de Quebras
        Stats InsSort_Stats[10];
        Stats QuickSort_Stats[10];
        int LimQueb_determinaLimiar(int vetor[], int tam, double limiarCusto);
        void LimQueb_registraEstatisticas(double custo);
        void LimQueb_imprimeEstatisticas(double custo);
        int LimQueb_menorCusto();

        
    private:

};

#endif 
