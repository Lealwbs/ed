#ifndef SIMULACAO_HPP
#define SIMULACAO_HPP

#include "armazem.hpp"
#include "evento.hpp"
#include "grafo_rede.hpp"
#include "heap_escalonador.hpp"
#include "outros_tads.hpp"
#include "pacote.hpp"
#include "transporte.hpp"

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
    
    // Métodos privados de processamento
    void ProcessarEventoChegada(Evento* evento);
    void ProcessarEventoTransporte(Evento* evento);
    void ExecutarTransferenciaArmazem(int origem, int destino, double momento);
    
    // Métodos privados de logging
    void RegistrarEvento(double tempo, int id_pacote, const std::string& descricao);
    std::string FormatarIdentificadorString(int id, int tamanho);

public:
    // Construtor e destrutor
    Simulacao(int cap_transporte, int lat_transporte, int int_transportes, 
              int cst_remocao, int num_armazens, int** matriz_adjacencia);
    ~Simulacao();
    
    // Método principal de execução
    void ExecutarSimulacao();
    
    // Métodos para adicionar pacotes
    void AdicionarPacote(Pacote* novo_pacote);
    void FinalizarConfiguracao();
    
    // Método para exibir resultados
    void ExibirResultados();
};

#endif