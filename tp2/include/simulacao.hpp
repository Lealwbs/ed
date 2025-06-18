#ifndef SIMULACAO_HPP
#define SIMULACAO_HPP

#include "../include/armazem.hpp"
#include "../include/evento.hpp"
#include "../include/grafo_rede.hpp"
#include "../include/heap_escalonador.hpp"
#include "../include/outros_tads.hpp"
#include "../include/pacote.hpp"
#include "../include/transporte.hpp"

#include <iostream>
#include <string>

class Simulacao {
    public:
        Simulacao(int capacidade_transporte, 
                  int latencia_transporte, 
                  int intervalo_transportes, 
                  int custo_remocao, 
                  int numero_armazens, 
                  int** matriz_adjacencia,
                  int numero_pacotes);

        ~Simulacao();
        
        // MÉTODO PRINCIPAL
        void ExecutarSimulacao();
        void AdicionarPacote(double tempo_chegada, int id_pacote, int armazem_inicial, int armazem_final);
    
    private:
        // PARÂMETROS DA SIMULAÇÃO
        int capacidade_transporte;
        int latencia_transporte;
        int intervalo_transportes;
        int custo_remocao;
        int numero_armazens;
        GrafoRede* rede_armazens; // Matriz de adjacência
        int numero_pacotes;
        
        // ESTRUTURAS PRINCIPAIS
        Armazem** lista_armazens;
        HeapEscalonador* escalonador_eventos;
        
        // CONTROLE DA SIMULAÇÃO
        double tempo_atual;
        double tempo_primeiro_pacote;
        int pacotes_pendentes;
        Lista* historico_eventos;
        
        // ARMAZENAMENTO DOS PACOTES
        Pacote** todos_pacotes;
        
        // INICIALIZACAO
        void IniciarTransportes(double tempo_inicial);
        
        // PROCESSAMENTO DE EVENTOS
        void ProcessarEventoChegada(EventoChegada* evento);
        void ProcessarEventoTransporte(EventoTransporte* evento);
        
        // LOG
        void RegistrarLog(double tempo, int id_pacote, std::string descricao);
        void ImprimirLog();
        std::string FormatarIdentificadorString(int id, int tamanho);
        
        /// LIMPEZA DE MEMÓRIA
        void LimparMemoria();
};

#endif