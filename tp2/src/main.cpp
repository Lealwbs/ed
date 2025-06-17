#include <fstream>
#include <iostream>
#include <string>

#include "../include/simulacao.hpp"

int main(int argc, char* argv[]) {

    // ABERTURA DO ARQUIVO DE ENTRADA
    std::ifstream arquivo(argv[1]);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    };

    // LEITURA DOS PARAMETROS
    int capacidadetransporte, latenciatransporte, intervalotransportes, custoremocao, numeroarmazens, numeropacotes;
    arquivo >> capacidadetransporte >> latenciatransporte >> intervalotransportes >> custoremocao >> numeroarmazens;

    // CRIAÇÃO E LEITURA DA MATRIZ DE ADJACÊNCIA
    int** matriz_adjacencia = new int*[numeroarmazens];
    for (int i = 0; i < numeroarmazens; i++) {
        matriz_adjacencia[i] = new int[numeroarmazens];
        for (int j = 0; j < numeroarmazens; j++) {
            arquivo >> matriz_adjacencia[i][j];
        };
    };

    // LEITURA DO NÚMERO DE PACOTES	(ÚLTIMO PARÂMETRO)
    arquivo >> numeropacotes;

    // PRINTANDO OS PARÂMETROS (DEBUG)
    std::cout << "Capacidade de transporte: " << capacidadetransporte << std::endl;
    std::cout << "Latencia de transporte:   " << latenciatransporte << std::endl;
    std::cout << "Intervalo de transporte:  " << intervalotransportes << std::endl;
    std::cout << "Custo de remocao:         " << custoremocao << std::endl;
    std::cout << "Numero de armazens:       " << numeroarmazens << std::endl;
    std::cout << "Matriz de adjacencia:     ";
    for (int i = 0; i < numeroarmazens; i++) {
        if (i) std::cout << "                          ";
        for (int j = 0; j < numeroarmazens; j++) {std::cout << matriz_adjacencia[i][j] << " ";};
        std::cout << std::endl;
    };
    std::cout << numeropacotes << " Pacotes" << std::endl;

    // CRIAÇÃO DA SIMULAÇÃO
    Simulacao simulacao = Simulacao( capacidadetransporte, latenciatransporte, 
        intervalotransportes, custoremocao, numeroarmazens, matriz_adjacencia, numeropacotes);
        
     // LEITURA E ADIÇÃO DOS PACOTES À SIMULAÇÃO
    int tempochegada, idpacote, armazeminicial, armazemfinal; std::string trash;
     for (int i = 0; i < numeropacotes; ++i) {
        arquivo >> tempochegada >> trash >> idpacote >> trash >> armazeminicial >> trash >> armazemfinal;
        simulacao.AdicionarPacote(tempochegada, idpacote, armazeminicial, armazemfinal);
        std::cout << "OK pacote" << std::endl;
    };
    arquivo.close();

    std::cout << "OK Antes Simulacao" << std::endl;
    
    // APÓS INSERÇÃO DOS PACOTES, EXECUTA A SIMULAÇÃO
    simulacao.ExecutarSimulacao();

    std::cout << "OK Depois Simulacao" << std::endl;

    // LIMPA A MEMÓRIA ALLOCADA
    for (int i = 0; i < numeroarmazens; ++i) { delete[] matriz_adjacencia[i]; }
    delete[] matriz_adjacencia;

    std::cout << "OK FINAL" << std::endl;

    return 0;
};