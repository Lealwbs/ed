#include "../include/ordenador.hpp"
#include <math.h>
#include <iostream>

Ordenador::Ordenador(){};
Ordenador::~Ordenador(){};

void Ordenador::OrdenadorUniversal(int vetor[], int tam, int minTamParticao, int limiarQuebras){
    if ( getNumeroQuebras(vetor, tam) < limiarQuebras ) {
        SortingAlgorithms::InsertionSort(vetor, tam);
    } else {
        if (tam > minTamParticao) {
            SortingAlgorithms::QuickSort(vetor, tam, minTamParticao);
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

void Ordenador::calculaNovaFaixa(int limiarParticao, int minMPS, int maxMPS, int passoMPS, int numMPS) {
    int newMin, newMax;
    if(limiarParticao == 0){
        newMin = 0;
        newMax = 2;
    }else if(limiarParticao == numMPS-1){
        newMin = numMPS-3;
        newMax = numMPS-1;
    }else{
        newMin = limiarParticao-1;
        newMax = limiarParticao+1;
    };

    minMPS = minMPS + (passoMPS * newMin); //getMPS(newMin);
    maxMPS = minMPS + (passoMPS * newMax); //getMPS(newMax);
    passoMPS = (int)(maxMPS - minMPS) / 5;
    if (passoMPS == 0) passoMPS++;

    // *minNumMPS = newMin;
    // *maxNumMPS = newMax;
};

////////////////////////////////////////////////////////////////////
// LIMIAR DE PARTIÇÃO //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

int Ordenador::LimPart_determinaLimiar(int vetor[], int vetorCopia[], int tam, double limiarCusto) {
    int minMPS = 2;
    int maxMPS = tam;
    int passoMPS = (maxMPS - minMPS) / 5;
    float diffCusto = 0.0;
    double custo[5];
    int limiarParticao;
    int numMPS = 0;
    
    //       float diffCusto;
    //   int minMPS = 2;
    //   int maxMPS = tam;
    //   int numMPS = 0;
    //   int passoMPS = _passoMPS(maxMPS, minMPS);
    //   int limParticao;

    int iter = 0;
    do{ 
        std::cout << "iter " << iter << " " << std::endl;
        numMPS = 0;
        iter++;
        
        for (int t = minMPS; t <= maxMPS; t += passoMPS) {

            SortingAlgorithms::stats.resetCounter();
            // resetar 
            OrdenadorUniversal(vetor, tam, t, tam);

            custo[numMPS] = SortingAlgorithms::stats.getCost();  // REGISTRA ESTATÍSTICAS

            std::cout << "mps " << numMPS << " " << std::endl;  // IMPRIME ESTATÍSTICAS
            SortingAlgorithms::stats.printStats();

            numMPS++;
        }
        limiarParticao = LimPart_menorCusto();
        calculaNovaFaixa(limiarParticao, minMPS, maxMPS, passoMPS, numMPS);
        diffCusto = fabs(custo[minMPS] - custo[maxMPS]);

    } while((diffCusto > limiarCusto) && (numMPS >= 5));

    return limiarParticao;
}

// do{
//     cout << "iter " << i << endl;
//     numMPS = 0;

//     for(int tamMin = minMPS; tamMin <= maxMPS; tamMin += passoMPS){
//       copiaVetor(vetor, tam);
//       Sort::SetTamParticao(tamMin);

//       ordenadorUniversal(vetor, tam, tamMin, 0);
      
//       registraEstatisticasMinParticao(tamMin, numMPS);
//       imprimeEstatisticasMinParticao(Registros[numMPS]);
      
//       numMPS++;
//     }

//     limParticao = menorCustoMinParticao(numMPS);
//     int minNumMPS;
//     int maxNumMPS;
//     calculaNovaFaixa(limParticao, &minMPS, &maxMPS, &passoMPS, &numMPS, &minNumMPS, &maxNumMPS);

//     diffCusto = Registros[minNumMPS].cost - Registros[maxNumMPS].cost;
//     if(diffCusto < 0){
//       diffCusto *= -1;
//     }
    
//     cout << "nummps " << numMPS;
//     cout << " limParticao " << Registros[limParticao].mps;
//     cout << " mpsdiff " << setprecision(6) << diffCusto << endl << endl;
    
//     i++;
//   }while (diffCusto > limiarCusto && numMPS >= 5);

//   return Registros[limParticao].mps;
// }




int Ordenador::LimPart_menorCusto() {
    double menorCusto = LimPart_Stats[0].getCost();
    int index = 0;
    for (int i = 1; i < 10; i++) {
        if (LimPart_Stats[i].getCost() < menorCusto) {
            menorCusto = LimPart_Stats[i].getCost();
            index = i;
        }
    }
    return index;
}

// asdsasasaasasasa
//   int cmp, moves, calls;
//   int idMenorCusto;
//   double custo, menorCusto;

//   for(int i = 0; i < numMPS; i++){
//     cmp = Registros[i].cmp;
//     moves = Registros[i].moves;
//     calls = Registros[i].calls;

//     custo = fabs(calcularCusto(cmp, moves, calls));
//     if(custo < 0){
//       custo *= -1;
//     }

//     if(i == 0 || menorCusto > custo){
//       menorCusto = custo;
//       idMenorCusto = i;
//     }
//   }

//   return idMenorCusto;
// }

// int Ordenador::MPS_step(int max, int min) {
//     return (max - min) / 5;
// }

// int Ordenador::LQ_step(int max, int min) {
//     return (max - min) / 10;
// }


////////////////////////////////////////////////////////////////////
// LIMIAR DE QUEBRA ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////