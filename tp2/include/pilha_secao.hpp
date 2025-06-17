#ifndef PILHA_SECAO_HPP
#define PILHA_SECAO_HPP

#include "../include/pacote.hpp"

#include <iostream>

struct NodePilhaPacotes {
    Pacote* pacote;
    NodePilhaPacotes* next;
};

class PilhaPacotes {
    public:
        PilhaPacotes();
        ~PilhaPacotes();

        void Empilhar(Pacote* pacote); // Empilha o pacote no topo da pilha
        Pacote* Desempilhar(); // Retira o pacote do topo e retorna o ponteiro para ele
        Pacote* DesempilharSemRemover(); // Desempilhar sem remover o pacote do topo

        bool Vazia();
        void Imprimir();
        int GetTamanho();

        Pacote** GetPacotesInArray();

    private:
        int tamanho;
        NodePilhaPacotes* topo;
};


class Secao {
    public:
        Secao();
        ~Secao();

        void EmpilharPacote(Pacote* pacote);
        Pacote* DesempilharPacote();

        int GetArmazemDestino();
        void SetArmazemDestino(int armazem_destino);
        
        bool Vazia();
        int GetTamanho();
        void Print();

    private:
        int armazem_destino;
        PilhaPacotes* pilha_pacotes;
};

#endif