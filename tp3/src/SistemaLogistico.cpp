#include "../include/SistemaLogistico.hpp"

SistemaLogistico::SistemaLogistico(){};
SistemaLogistico::~SistemaLogistico(){};

void SistemaLogistico::processarEvento(const Evento* evento){
    eventos.InsereFinal(*evento);
    //eventos.Imprime();
};



void SistemaLogistico::consultarPacote(int idPacote){};
void SistemaLogistico::consultarCliente(const std::string& nomeCliente){};