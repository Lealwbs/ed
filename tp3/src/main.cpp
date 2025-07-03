#include <iostream>
#include <fstream>
#include <string>

#include "../include/ArvoreALV.hpp"
#include "../include/VetorEventos.hpp"
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
    Evento* novoEvento;

    // SISTEMA LOGÍSTICO
    SistemaLogistico sistema;

    // PRIMEIRA LEITURA REFERENTE À DATA_HORA E AO TIPO DO COMANDO (EV, PC, CL).     
    while(arquivo >> dataHora >> strComando) {  
        
        int comando = Utils::stringToTipoComando(strComando); // STRING TO INT

        if(comando == TipoComando::EV) {

            // LEITURA E CONVERSÃO DO TIPO DE EVENTO
            arquivo >> strTipoEvento;
            TipoEvento tipoEvento = Utils::stringToTipoEvento(strTipoEvento);
  
            // LER A DEPENDER DO TIPO DE EVENTO E ARMAZENAR OS DADOS DO EVENTO NO VETOR DE EVENTOS
            switch(tipoEvento){
                case TipoEvento::RG:
                    arquivo >> idPacote >> remetente >> destinatario >> armazemOrigem >> armazemDestino;
                    novoEvento = new Evento(tipoEvento, dataHora, idPacote, armazemOrigem, armazemDestino, -1, remetente, destinatario);
                    sistema.processarEvento(novoEvento);
                    // std::cout << "Criado evento: " << novoEvento->getInfo() << std::endl;
                    break;

                case TipoEvento::TR:
                    arquivo >> idPacote >> armazemOrigem >> armazemDestino;
                    novoEvento = new Evento(tipoEvento, dataHora, idPacote, armazemOrigem, armazemDestino, -1, "", "");
                    sistema.processarEvento(novoEvento);
                    // std::cout << "Criado evento: " << novoEvento->getInfo() << std::endl;
                    break;

                case TipoEvento::EN:
                    arquivo >> idPacote >> armazemDestino; 
                    novoEvento = new Evento(tipoEvento, dataHora, idPacote, -1, armazemDestino, -1, "", "");
                    sistema.processarEvento(novoEvento);
                    // std::cout << "Criado evento: " << novoEvento->getInfo() << std::endl;
                    break;

                default: // AR ou RM ou UR, caso não seja nenhuma desses, ele crasha o programa.
                    if (tipoEvento != TipoEvento::AR && tipoEvento != TipoEvento::RM && tipoEvento != TipoEvento::UR) return -1;
                    arquivo >> idPacote >> armazemDestino >> secaoDestino;
                    novoEvento = new Evento(tipoEvento, dataHora, idPacote, -1, armazemDestino, secaoDestino, "", "");
                    sistema.processarEvento(novoEvento);
                    // std::cout << "Criado evento: " << novoEvento->getInfo() << std::endl;
                    break;
            };

            delete novoEvento; 
            continue;
        }



        if(comando == TipoComando::PC) {
            arquivo >> idPacote;

            std::cout << "opa PC | " << idPacote << std::endl;
            // <dh> PC <identificador pacote>: Histórico do pacote <identificador pacote>.
            continue;
        }



        if(comando == TipoComando::CL) {
            arquivo >> nomeCliente;

            std::cout << "opa CL | " << nomeCliente << std::endl;
            // <dh> CL <nome cliente>: Histórico dos pacotes associados a <nome cliente>.
            continue;
        }
        


    }




// <consulta 1>
// <n1 - numero de linhas da resposta da consulta 1>
// <linha 1 da resposta a consulta 1>
// ...
// <linha n1 da resposta a consulta 1>
// <consulta 2>
// ...


// 0000150 CL LUISA <consulta 1>
// 6 <n1 - numero de linhas da resposta da consulta 1>
// 0000006 EV RG 006 LUISA ANDRE 003 002
// 0000012 EV RG 005 BERNARDO LUISA 002 003
// 0000080 EV RG 002 PEDRO LUISA 000 003
// 0000104 EV UR 002 000 002
// 0000122 EV EN 005 003
// 0000123 EV EN 006 002


// 0000200 PC 003 <consulta 2>
// 5 <n1 - numero de linhas da resposta da consulta 1>
// 0000001 EV RG 003 JOAO MARIA 000 003
// 0000002 EV AR 003 000 002
// 0000104 EV RM 003 000 002
// 0000104 EV TR 003 000 002
// 0000124 EV AR 003 002 003



// 0000210 CL JOAO <consulta 3>
// 4 <n1 - numero de linhas da resposta da consulta 1>
// 0000001 EV RG 003 JOAO MARIA 000 003
// 0000070 EV RG 007 JOAO JOSE 000 003
// 0000203 EV TR 003 002 003
// 0000203 EV TR 007 002 003


// 0300 PC 002 <consulta 4>
// 7 <n1 - numero de linhas da resposta da consulta 1>
// 0000080 EV RG 002 PEDRO LUISA 000 003
// 0000093 EV AR 002 000 002
// 0000102 EV RM 002 000 002
// 0000104 EV UR 002 000 002
// 0000202 EV RM 002 000 002
// 0000202 EV TR 002 000 002
// 0000222 EV AR 002 002 003


    //TODO: dar dele nos pacotes dentro do vetor de pacotes;

    arquivo.close();
    return 0;
}