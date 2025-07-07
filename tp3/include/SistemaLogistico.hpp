#ifndef SISTEMALOGISTICO_HPP
#define SISTEMALOGISTICO_HPP

#include "../include/EventosVetor.hpp"

class SistemaLogistico {
    public:
        SistemaLogistico();
        ~SistemaLogistico();

        void processarEvento(const Evento evento);
        void consultarPacote(int idPacote);
        void consultarCliente(const std::string& nomeCliente);

        // Depuração
        void imprimirEventos();

    private:
        EventosVetor eventos; // Vetor de eventos



};


#endif