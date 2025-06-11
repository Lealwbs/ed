#include "../include/list.hpp"

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

class ListaEncadeada : public Lista {
    public:
        ListaEncadeada();
        ~ListaEncadeada();
        int GetItem(int pos);
        void SetItem(int item, int pos);
        void InsereInicio(int item);
        void InsereFinal(int item);
        void InserePosicao(int item, int pos);
        int RemoveInicio();
        int RemoveFinal();
        int RemovePosicao(int pos);
        int Pesquisa(int c);
        void Imprime();
        void Limpa();

    private:
        int* primeiro;
        int* ultimo;
        int* Posiciona(int pos, bool antes);
};

#endif
