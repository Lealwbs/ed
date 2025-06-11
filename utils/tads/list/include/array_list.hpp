#include "../include/list.hpp"

#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

class ListaArranjo : public Lista {
    public:
        ListaArranjo() : Lista() {};
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
        static const int MAXTAM = 100;
        int itens[MAXTAM];
};

#endif