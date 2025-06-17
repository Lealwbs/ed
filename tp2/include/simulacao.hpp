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
#include <exception>

class Simulacao {
private:
    // Parâmetros da simulação
    int capacidade_transporte;
    int latencia_transporte;
    int intervalo_transportes;
    int custo_remocao;
    int numero_armazens;
    
    // Estruturas principais
    GrafoRede* rede_armazens;
    Armazem** lista_armazens;
    HeapEscalonador* escalonador_eventos;
    
    // Controle da simulação
    double tempo_atual;
    int pacotes_pendentes;
    Lista* historico_eventos;
    
    // Armazenamento de pacotes
    Pacote** todos_pacotes;
    int total_pacotes;
    
    // Métodos privados de inicialização
    void CriarArmazens();
    void IniciarTransportesAutomaticos(double tempo_inicial);
    void CalcularRotasPacotes();
    
    // Métodos privados de processamento de eventos
    void ProcessarEventoChegada(Evento* evento);
    void ProcessarEventoTransporte(Evento* evento);
    void ExecutarTransferenciaArmazem(int origem, int destino, double momento);
    
    // Métodos privados de validação e segurança
    bool ValidarArmazem(int id_armazem) const;
    bool ValidarPacote(const Pacote* pacote) const;
    bool ValidarEvento(const Evento* evento) const;
    
    // Métodos privados de logging e formatação
    void RegistrarEvento(double tempo, int id_pacote, const std::string& descricao);
    std::string FormatarIdentificadorString(int id, int tamanho);
    
    // Métodos privados de limpeza de memória
    void LimparMemoria();

public:
    // Construtor e destrutor
    Simulacao(int cap_transporte, int lat_transporte, int int_transportes, 
              int cst_remocao, int num_armazens, int** matriz_adjacencia);
    ~Simulacao();
    
    // Método principal de execução
    void ExecutarSimulacao();
    
    // Métodos para configuração de pacotes
    void AdicionarPacote(Pacote* novo_pacote);
    void FinalizarConfiguracao();
    
    // Método para exibir resultados
    void ExibirResultados();
    
    // Métodos públicos para depuração (opcionais)
    void ExibirStatusSimulacao() const;
    void ExibirEstatisticas() const;
    
    // Getters para depuração (opcionais)
    double GetTempoAtual() const { return tempo_atual; }
    int GetPacotesPendentes() const { return pacotes_pendentes; }
    int GetTotalPacotes() const { return total_pacotes; }
    int GetNumeroArmazens() const { return numero_armazens; }
    
    // Método para verificar integridade (opcional)
    bool VerificarIntegridade() const;
};

#endif