#include <iostream>
#include <fstream>
#include <string>

#include "../include/test.hpp"
#include "../include/eventos.hpp"
#include "../include/arvore_balanceada.hpp"

int main(int argc, char** argv) {

    // ABERTURA DO ARQUIVO DE ENTRADA
    std::ifstream arquivo(argv[1]);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    };
    
    // std::string linha;
    // while(arquivo >> linha){
    //     std::cout << linha << std::endl;
    // };









// <dh> CL <nome cliente>: Histórico dos pacotes associados a <nome cliente>.
// <dh> PC <identificador pacote>: Histórico do pacote <identificador pacote>.
// <dh> EV <identificador pacote> <tipo evento> <dados evento>: Evento associado à tramitação de um pacote nos Armazéns Hanoi.


// • Clientes: Permite acesso rápido a todos os eventos dos clientes.
// • Pacotes: Permite acesso rápido a todos os eventos associados a um pacote.
// • Eventos: Permite acesso rápido a um identificador de evento.



// RG: data_hora EV tipo_evento id_pacote remetente destinatario armazem_origem armazem_destino
// AR: data_hora EV tipo_evento id_pacote armazem_destino secao_destino
// RM: data_hora EV tipo_evento id_pacote armazem_destino secao_destino
// UR: data_hora EV tipo_evento id_pacote armazem_destino secao_destino
// TR: data_hora EV tipo_evento id_pacote armazem_origem armazem_destino
// EN: data_hora EV tipo_evento id_pacote armazem_destino


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




    arquivo.close();
    return 0;
}