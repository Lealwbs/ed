#ifndef SISTEMALOGISTICO_HPP
#define SISTEMALOGISTICO_HPP

#include "../include/EventosVetor.hpp"
#include "../include/ArvoreAVL.hpp"
#include "../include/Consulta.hpp"

class SistemaLogistico {
    public:
        SistemaLogistico() = default;
        ~SistemaLogistico() = default;

        // PROCESSAMENTO E CONSULTAS
        void processarEvento(const Evento evento);              // Processa e armazena um novo evento no sistema
        void consultarPacote(int idPacote);                     // Consulta e imprime histórico de eventos de um pacote
        void consultarCliente(const std::string& nomeCliente);  // Consulta e imprime pacotes associados a um cliente

        // DEPURAÇÃO
        void imprimirEventos();
        void imprimirPacotes();
        void imprimirClientes();

    private:
        ArvoreAVL<Pacote*, int> pacotes;
        ArvoreAVL<Evento*, int> eventos;
        ArvoreAVL<Cliente*, std::string> clientes;
        
        // GET/CREATE PACOTE E CLIENTE
        Pacote* obterOuCriarPacote(int idPacote);
        Cliente* obterOuCriarCliente(const std::string& nome);
};

#endif