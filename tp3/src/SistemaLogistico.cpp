#include "../include/SistemaLogistico.hpp"

// SistemaLogistico::SistemaLogistico():
//     pacotes(obterChavePacote),
//     clientes(obterChaveCliente),
//     eventos(obterChaveEvento) {};

// SistemaLogistico::~SistemaLogistico(){};

void SistemaLogistico::processarEvento(const Evento evento) {
    // std::cout << evento.getInfo() << std::endl;
};

void SistemaLogistico::consultarPacote(int idPacote){
    // std::cout << "opa PC | " << idPacote << std::endl;
    // <dh> PC <identificador pacote>: Histórico do pacote <identificador pacote>.
};

void SistemaLogistico::consultarCliente(const std::string& nomeCliente){
    // std::cout << "opa CL | " << nomeCliente << std::endl;
    // <dh> CL <nome cliente>: Histórico dos pacotes associados a <nome cliente>.
};

void SistemaLogistico::imprimirEventos(){};
void SistemaLogistico::imprimirPacotes(){};
void SistemaLogistico::imprimirClientes(){};


// // // 0000200 PC 003 <consulta 2>
// // // 5 <n1 - numero de linhas da resposta da consulta 1>
// // // 0000001 EV RG 003 JOAO MARIA 000 003
// // // 0000002 EV AR 003 000 002
// // // 0000104 EV RM 003 000 002
// // // 0000104 EV TR 003 000 002
// // // 0000124 EV AR 003 002 003

// // // 0300 PC 002 <consulta 4>
// // // 7 <n1 - numero de linhas da resposta da consulta 1>
// // // 0000080 EV RG 002 PEDRO LUISA 000 003
// // // 0000093 EV AR 002 000 002
// // // 0000102 EV RM 002 000 002
// // // 0000104 EV UR 002 000 002
// // // 0000202 EV RM 002 000 002
// // // 0000202 EV TR 002 000 002
// // // 0000222 EV AR 002 002 003

// // // 0000210 CL JOAO <consulta 3>
// // // 4 <n1 - numero de linhas da resposta da consulta 1>
// // // 0000001 EV RG 003 JOAO MARIA 000 003
// // // 0000070 EV RG 007 JOAO JOSE 000 003
// // // 0000203 EV TR 003 002 003
// // // 0000203 EV TR 007 002 003

// // // 0000150 CL LUISA <consulta 1>
// // // 6 <n1 - numero de linhas da resposta da consulta 1>
// // // 0000006 EV RG 006 LUISA ANDRE 003 002
// // // 0000012 EV RG 005 BERNARDO LUISA 002 003
// // // 0000080 EV RG 002 PEDRO LUISA 000 003
// // // 0000104 EV UR 002 000 002
// // // 0000122 EV EN 005 003
// // // 0000123 EV EN 006 002


// // // <consulta 1>
// // // <n1 - numero de linhas da resposta da consulta 1>
// // // <linha 1 da resposta a consulta 1>
// // // ...
// // // <linha n1 da resposta a consulta 1>
// // // <consulta 2>
// // // ...
