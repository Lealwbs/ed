#include <iostream>
#include <fstream>
#include <string>

#include "../include/SistemaLogistico.hpp"

int main(int argc, char** argv) {

    // ABERTURA DO ARQUIVO DE ENTRADA
    std::ifstream arquivo(argv[1]);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    };

    // VARIÁVEIS PARA LEITURA DOS DADOS
    std::string strComando, strTipoEvento, remetente, destinatario, nomeCliente;
    int dataHora, idPacote, armazemOrigem, armazemDestino, secaoDestino;
    Evento novoEvento;

    // SISTEMA LOGÍSTICO
    SistemaLogistico sistema;

    // PRIMEIRA LEITURA REFERENTE À DATA_HORA E AO TIPO DO COMANDO (EV, PC, CL).     
    while(arquivo >> dataHora >> strComando) {  
        
        int comando = Utils::stringToTipoComando(strComando); // STRING TO INT

        if(comando == TipoComando::EV) {
            arquivo >> strTipoEvento;
            TipoEvento tipoEvento = Utils::stringToTipoEvento(strTipoEvento); // STRING TO INT
  
            // LER A DEPENDER DO TIPO DE EVENTO E PROCESSAR OS DADOS 
            switch(tipoEvento){
                case TipoEvento::RG:
                    arquivo >> idPacote >> remetente >> destinatario >> armazemOrigem >> armazemDestino;
                    sistema.processarEvento(Evento(tipoEvento, dataHora, idPacote, armazemOrigem, armazemDestino, -1, remetente, destinatario));
                    break;

                case TipoEvento::TR:
                    arquivo >> idPacote >> armazemOrigem >> armazemDestino;
                    sistema.processarEvento(Evento(tipoEvento, dataHora, idPacote, armazemOrigem, armazemDestino, -1, "", ""));
                    break;

                case TipoEvento::EN:
                    arquivo >> idPacote >> armazemDestino; 
                    sistema.processarEvento(Evento(tipoEvento, dataHora, idPacote, -1, armazemDestino, -1, "", ""));
                    break;

                case TipoEvento::AR: case TipoEvento::RM: case TipoEvento::UR: // AR, RM, UR: POSSUEM A MESMA ENTRADA
                    arquivo >> idPacote >> armazemDestino >> secaoDestino;
                    sistema.processarEvento(Evento(tipoEvento, dataHora, idPacote, -1, armazemDestino, secaoDestino, "", ""));
                    break;
                
                default: 
                    std::cerr << "Tipo de evento inválido: " << strTipoEvento << std::endl;
                    return 2; 
            };
        };

        if(comando == TipoComando::PC) {
            arquivo >> idPacote;
            std::cout << Utils::intToString(dataHora, 7) << " PC " << Utils::intToString(idPacote, 3) << std::endl;
            sistema.consultarPacote(idPacote);
        };

        if(comando == TipoComando::CL) {
            arquivo >> nomeCliente;
            std::cout << Utils::intToString(dataHora, 7)  << " CL " << nomeCliente << std::endl;
            sistema.consultarCliente(nomeCliente);
        };

    };

    // DEPURAÇÃO
    // std::cout << std::endl << "Fim do processamento dos eventos." << std::endl << std::endl;
    // sistema.imprimirEventos();
    // sistema.imprimirPacotes();
    // sistema.imprimirClientes();

    arquivo.close();
    return 0;
}