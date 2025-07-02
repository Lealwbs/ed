#ifndef COMANDOS_HPP
#define COMANDOS_HPP

enum TipoComando {
    EV, // EVENTO
    PC, // CONSULTA PACOTE
    CL  // CONSULTA CLIENTE
};

TipoComando stringToTipoComando(const std::string& comando) {
    if (comando == "EV") return EV; // 0
    if (comando == "PC") return PC; // 1
    if (comando == "CL") return CL; // 2
};

#endif