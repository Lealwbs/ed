#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "../include/evento.hpp"

// Esse escalonador nada mais é que um Heap de prioridade que armazena os eventos.
class HeapEscalonador {
    public:
        HeapEscalonador(int capacidade_max = 100);
        ~HeapEscalonador();

        void InserirEvento(Evento* evento); // Adiciona um evento à fila de prioridade
        Evento* ExtrairEvento(); // Remove e retorna o evento com a maior prioridade
        bool Vazio(); // Verifica se a fila está vazia

    private:

        int GetAncestral(int posicao);
        int GetSucessorEsq(int posicao);
        int GetSucessorDir(int posicao);
        void HeapifyPorBaixo(int posicao);
        void HeapifyPorCima(int posicao);
        void AumentarCapacidade();

        int tamanho;
        int capacidade_max;
        Evento** eventos; // Um heap que armazena ponteiros para os eventos
};

#endif 