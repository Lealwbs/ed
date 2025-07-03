#ifndef VETOREVENTOS_HPP
#define VETOREVENTOS_HPP

#include "../include/Eventos.hpp"
#include <iostream>

class Node {
    public:
        Evento* evento;
        Node* prox;
};

class VetorEventos {
    public:
        VetorEventos();
        ~VetorEventos();
        Evento* GetItem(int pos);
        void SetItem(Evento evento, int pos);
        void InsereInicio(Evento evento);
        void InsereFinal(Evento evento);
        void InserePosicao(Evento evento, int pos);
        Evento* RemoveInicio();
        Evento* RemoveFinal();
        Evento* RemovePosicao(int pos);
        Evento* Pesquisa(int c);
        void Imprime();
        void Limpa();

    private:
        Node* primeiro;
        Node* ultimo;
        Node* Posiciona(int pos, bool antes = false);
        int tamanho;
};

#endif