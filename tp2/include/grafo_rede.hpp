#ifndef GRAFO_REDE_H
#define GRAFO_REDE_H

#include "../include/armazem.hpp"

class GrafoRede {
    public:
        GrafoRede();
        ~GrafoRede();

        Rede(int numero_armazens);
        ~Rede();

        void AdicionarAresta(int armazem_1, int armazem_2);
        Lista* getVizinhos(int v) const;

#endif