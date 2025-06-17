#ifndef EVENTO_HPP
#define EVENTO_HPP

#include "../include/pacote.hpp"

class Evento {
    public:
        enum TipoEvento {
            Chegada,
            Transporte
        };

        Evento();
        ~Evento();

        // MÉTODOS SET
        void SetTempo(double tempo);
        void SetPrioridade(long long prioridade);
        void SetTipo(TipoEvento tipo);

        // MÉTODOS GET
        double GetTempo();
        long long GetPrioridade();
        TipoEvento GetTipo();

    protected:
        TipoEvento tipo;
        double tempo;
        long long prioridade; 
};



class EventoTransporte : public Evento {
    public:
        EventoTransporte(double tempo, int armazem_origem, int armazem_destino);

        // MÉTODOS SET
        void SetArmazemOrigem(int armazem_origem);
        void SetArmazemDestino(int armazem_destino);

        // MÉTODOS GET
        int GetArmazemOrigem();
        int GetArmazemDestino();

        // MÉTODOS PARA ATUALIZAR A PRIORIDADE
        void UpdatePrioridadeTransporte(int armazem_origem, int armazem_destino);

    private:
        int armazem_origem;
        int armazem_destino;
};



class EventoChegada : public Evento {
    public:
        EventoChegada(double tempo, Pacote* pacote, int armazem_chegada);

        // MÉTODOS SET
        void SetPacote(Pacote* pacote);
        void SetArmazemChegada(int armazem_chegada);

        // MÉTODOS GET
        Pacote* GetPacote();
        int GetArmazemChegada();

        // MÉTODOS PARA ATUALIZAR A PRIORIDADE
        void UpdatePrioridadeChegada(Pacote* pacote);

    private:
        Pacote* pacote;
        int armazem_chegada;
};

#endif