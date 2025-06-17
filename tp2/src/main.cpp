#include <fstream>
#include <iostream>
#include <string>

#include "../include/simulacao.hpp"

int main(int argc, char* argv[]) {

    std::ifstream arquivo(argv[1]);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    };

    // LEITURA DOS PARAMETROS
    int capacidadetransporte, latenciatransporte, intervalotransportes, custoremocao, numeroarmazens, numeropacotes;
    arquivo >> capacidadetransporte >> latenciatransporte >> intervalotransportes >> custoremocao >> numeroarmazens;

    // CRIAÇÃO DA MATRIZ DE ADJACÊNCIA
    int** matriz = new int*[numeroarmazens];
    for (int i = 0; i < numeroarmazens; i++) {
        matriz[i] = new int[numeroarmazens];
    };

    // LEITURA DA MATRIZ DE ADJACÊNCIA
    for (int i = 0; i < numeroarmazens; i++) {
        for (int j = 0; j < numeroarmazens; j++) {
            arquivo >> matriz[i][j];
        };
    };

    // LEITURA DO NÚMERO DE PACOTES	(ÚLTIMO PARÂMETRO)
    arquivo >> numeropacotes;

    // // PRINTANDO OS PARÂMETROS
    // std::cout << "Capacidade de transporte: " << capacidadetransporte << std::endl;
    // std::cout << "Latencia de transporte:   " << latenciatransporte << std::endl;
    // std::cout << "Intervalo de transporte:  " << intervalotransportes << std::endl;
    // std::cout << "Custo de remocao:         " << custoremocao << std::endl;
    // std::cout << "Numero de armazens:       " << numeroarmazens << std::endl;
    // std::cout << "Matriz de adjacencia:     ";
    // for (int i = 0; i < numeroarmazens; i++) {
    //     if (i) std::cout << "                          ";
    //     for (int j = 0; j < numeroarmazens; j++) {std::cout << matriz[i][j] << " ";};
    //     std::cout << std::endl;
    // };
    // std::cout << numeropacotes << " Pacotes:" << std::endl;


   // CRIAÇÃO DA SIMULAÇÃO
    Simulacao* simulacao = new Simulacao(capacidadetransporte, latenciatransporte, 
                                         intervalotransportes, custoremocao, 
                                         numeroarmazens, matriz);

    // LEITURA E ADIÇÃO DOS PACOTES À SIMULAÇÃO
    int tempochegada, idpacote, armazeminicial, armazemfinal;
    std::string trash;

    for (int i = 0; i < numeropacotes; ++i) {
        if (!(arquivo >> tempochegada >> trash >> idpacote >> trash >> armazeminicial >> trash >> armazemfinal)) {
            std::cerr << "Erro ao ler dados do pacote " << (i + 1) << std::endl;
            delete simulacao;
            for (int j = 0; j < numeroarmazens; ++j) {
                delete[] matriz[j];
            }
            delete[] matriz;
            arquivo.close();
            return 1;
        }

        // Validação básica dos dados do pacote
        if (armazeminicial < 0 || armazeminicial >= numeroarmazens || 
            armazemfinal < 0 || armazemfinal >= numeroarmazens) {
            std::cerr << "Erro: Armazém inválido no pacote " << idpacote << std::endl;
            delete simulacao;
            for (int j = 0; j < numeroarmazens; ++j) {
                delete[] matriz[j];
            }
            delete[] matriz;
            arquivo.close();
            return 1;
        }

        // Cria pacote usando o ID lido do arquivo
        Pacote* pacote = new Pacote(tempochegada, idpacote, armazeminicial, armazemfinal);
        simulacao->AdicionarPacote(pacote);
    }


    arquivo.close();

    // FINALIZA CONFIGURAÇÃO E EXECUTA SIMULAÇÃO
    try {
        simulacao->FinalizarConfiguracao();
        std::cout << "OK3" << std::endl;
        simulacao->ExecutarSimulacao();
        std::cout << "OK4" << std::endl;
        simulacao->ExibirResultados();
        std::cout << "OK5" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro durante a simulação: " << e.what() << std::endl;
        delete simulacao;
        for (int i = 0; i < numeroarmazens; ++i) {
            delete[] matriz[i];
        }
        delete[] matriz;
        return 1;
    }

       std::cout << "OK6" << std::endl;

    // LIMPEZA DE MEMÓRIA
    delete simulacao;
    for (int i = 0; i < numeroarmazens; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;

           std::cout << "OK7" << std::endl;

    return 0;
};