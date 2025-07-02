#ifndef COMANDOS_HPP
#define COMANDOS_HPP

enum TipoComando {
    EV, // EVENTO
    PC, // CONSULTA PACOTE
    CL  // CONSULTA CLIENTE
};

int stringToTipoComando(const std::string& comando) {
    if (comando == "EV") return TipoComando::EV; // 0
    if (comando == "PC") return TipoComando::PC; // 1
    if (comando == "CL") return TipoComando::CL; // 2
    return -1; // COMANDO INVÁLIDO
};

#endif