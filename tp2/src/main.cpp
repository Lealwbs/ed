#include <fstream>
#include <iostream>
#include <string>

#include "../include/pacote.hpp"
#include "../include/armazem.hpp"
#include "../include/transporte.hpp"
#include "../include/escalonador.hpp"

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

    // LEITURA DOS PACOTES
    int tempochegada, idpacote, armazeminicial, armazemfinal;
    std::string trash;

    for (int i = 0; i < numeropacotes; ++i) {
        arquivo >> tempochegada >> trash >> idpacote >> trash >> armazeminicial >> trash >> armazemfinal;

        Pacote pacote = Pacote( tempochegada, idpacote, armazeminicial, armazemfinal);
        //pacote.PrintInfo();
        //armazem.addPacote(pacote);  
    };

    /// OUTPUT: Sequencia de eventos
    // 0000010 pacote 000 armazenado em 000 na secao 001
    // 0000015 pacote 001 armazenado em 003 na secao 001
    // 0000020 pacote 002 armazenado em 002 na secao 001
    // 0000121 pacote 000 removido de 000 na secao 001
    // 0000121 pacote 000 em transito de 000 para 001
    // 0000121 pacote 002 removido de 002 na secao 001
    // 0000121 pacote 002 em transito de 002 para 001
    // 0000121 pacote 001 removido de 003 na secao 001
    // 0000121 pacote 001 em transito de 003 para 001
    // 0000141 pacote 000 armazenado em 001 na secao 002
    // 0000141 pacote 001 armazenado em 001 na secao 000
    // 0000141 pacote 002 armazenado em 001 na secao 003
    // 0000231 pacote 001 removido de 001 na secao 000
    // 0000231 pacote 001 em transito de 001 para 000
    // 0000231 pacote 000 removido de 001 na secao 002
    // 0000231 pacote 000 em transito de 001 para 002
    // 0000231 pacote 002 removido de 001 na secao 003
    // 0000231 pacote 002 em transito de 001 para 003
    // 0000251 pacote 000 entregue em 002
    // 0000251 pacote 001 entregue em 000
    // 0000251 pacote 002 entregue em 003

    // "SAÍDA:"
    // • Tempo esperado de estadia
    // • Tempo armazenado
    // • Tempo em trânsito

    // rede/grafo (armazens)

    // rota(id armazens, )

    // armazem
    //     setor* Head_vetor
    //     info

    // setor
    //     pilha_pacote Head_vetor
    //     setor* NEXT

    // pilha_pacote
    //     pacotes Head_vetor
    //     pilha_pacote* NEXT

    // pacote
    //     INFO
    //     DESTINATION
    //     pacote* NEXT

    // ENCERRANDO MEMÓRIA
    arquivo.close();
    for (int i = 0; i < numeroarmazens; ++i) {
        delete[] matriz[i];
    };
    delete[] matriz;

    return 0;
}