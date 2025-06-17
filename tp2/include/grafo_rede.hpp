#ifndef GRAFO_REDE_HPP
#define GRAFO_REDE_HPP

#include "../include/armazem.hpp"
#include "../include/outros_tads.hpp"

class GrafoRede {
    public:
        GrafoRede(int numero_armazens);
        ~GrafoRede();

        int GetNumeroArmazens();
        
        void AdicionarAresta(int armazem_1, int armazem_2); // Conexão entre 2 armazéns
        Lista* GetVizinhos(int v);

        void Print();

        Lista* GetRota(GrafoRede& rede, int armazem_origem, int armazem_destino); // Pegar a rota com menos saltos entre 2 armazens, usando busca em largura

    private:
        int numero_armazens;
        Lista** matriz_adjacencia; // Matriz de adjacência para representar as conexões entre os armazéns

};

#endif