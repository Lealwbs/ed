#ifndef GRAFO_REDE_H
#define GRAFO_REDE_H

#include "../include/armazem.hpp"
#include "../include/outros_tads.hpp"

class GrafoRede {
    public:
        GrafoRede(int numero_armazens);
        ~GrafoRede();

        int GetNumeroArmazens();
        
        void AdicionarAresta(int armazem_1, int armazem_2); // Conexão entre 2 armazéns
        ListaInt* GetVizinhos(int v);

        void Print();

        ListaInt* GetRota(const GrafoRede& rede, int armazem_origem, int armazem_destino); // Pegar a rota com menos saltos entre 2 armazens, usando busca em largura

    private:
        int numero_armazens;
        ListaInt** matriz_adjacencia; // Matriz de adjacência para representar as conexões entre os armazéns

};

#endif