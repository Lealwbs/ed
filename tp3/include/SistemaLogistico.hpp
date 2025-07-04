#ifndef SISTEMALOGISTICO_HPP
#define SISTEMALOGISTICO_HPP

#include "../include/VetorEventos.hpp"

class SistemaLogistico {
    public:
        SistemaLogistico();
        ~SistemaLogistico();

        void processarEvento(const Evento* evento);
        void consultarPacote(int idPacote);
        void consultarCliente(const std::string& nomeCliente);

    private:
        VetorEventos eventos; // Vetor de eventos



};


#endif