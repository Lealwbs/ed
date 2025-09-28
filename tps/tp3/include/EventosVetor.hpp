#ifndef EVENTOSVETOR_HPP
#define EVENTOSVETOR_HPP

#include "../include/Evento.hpp"
#include <iostream>

class Node {
    public:
        Evento* evento;
        Node* prox;
};

class EventosVetor {
    public:
        EventosVetor();
        ~EventosVetor();
        int GetTamanho() const;
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
        void ImprimeUltimo();
        void Limpa();
        void OrdenaPorDataHora();

    private:
        Node* primeiro;
        Node* ultimo;
        Node* Posiciona(int pos, bool antes = false);
        int tamanho;
};

#endif