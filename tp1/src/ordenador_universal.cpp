#include "ordenador_universal.hpp"
#include <math.h>

ordenador_Universal::ordenador_Universal(){
    numQuebras = 0;
    if (vetor != nullptr && tam > 0) {
        this->numQuebras = ordenador_Universal::getNumeroQuebras(vetor, tam);
    };
};

ordenador_Universal::~ordenador_Universal(){};

int ordenador_Universal::MPS_step(int max, int min) {
    return (max - min) / 5;
}

int ordenador_Universal::LQ_step(int max, int min) {
    return (max - min) / 10;
}

int ordenador_Universal::getNumeroQuebras(int vetor[], int tam) {
    int numQuebras = 0;
    for (int i = 0; i < tam - 1; i++) {
        if (vetor[i] > vetor[i + 1]) {
            numQuebras++;
        }
    }
    return numQuebras;
}

void ordenador_Universal::ordenadorUniversal( int vetor[], int tam, int minTamParticao, int limiarQuebras) {
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

int ordenador_Universal::determinaLimiarParticao(int vetor[], int tam, double limiarCusto) {
    int minMPS = 2;
    int maxMPS = tam;
    int passoMPS = (maxMPS - minMPS) / 5;
    double diffCusto = 0.0;
    double custo[5];
    int numMPS = 0;

    int limiarParticao;

    while ((diffCusto > limiarCusto) && (numMPS >= 5)) {
        numMPS = 0;
        for (int t = minMPS; t <= maxMPS; t += passoMPS) {
            ordenadorUniversal(vetor, tam, t, tam);
            registraEstatisticas(custo[numMPS]);
            imprimeEstatisticas(custo[numMPS]);
            numMPS++;
        }
        limiarParticao = menorCusto();
        calculaNovaFaixa(limiarParticao, minMPS, maxMPS, passoMPS);
        diffCusto = fabs(custo[minMPS] - custo[maxMPS]);
    }
    return limiarParticao;
}

void ordenador_Universal::calculaNovaFaixa(int limiarParticao, int minMPS, int maxMPS, int passoMPS, int numMPS) {
    int newMin, newMax;
    if (limiarParticao == 0) {
        newMin = 0;
        newMax = 2;
    } else if (limiarParticao == numMPS - 1) {
        newMin = numMPS - 3;
        newMax = numMPS - 1;
    } else {
        newMin = limiarParticao - 1;
        newMax = limiarParticao + 1;
    }
    minMPS = getMPS(newMin);
    maxMPS = getMPS(newMax);
    passoMPS = (int)(maxMPS - minMPS) / 5;
    if (passoMPS == 0) passoMPS++;
}