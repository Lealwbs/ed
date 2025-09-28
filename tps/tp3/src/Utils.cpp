#include "../include/Utils.hpp"

TipoEvento Utils::stringToTipoEvento(const std::string& str) {
    if (str == "RG") return RG;
    if (str == "AR") return AR;
    if (str == "RM") return RM;
    if (str == "UR") return UR;
    if (str == "TR") return TR;
    if (str == "EN") return EN;
    throw std::invalid_argument("Tipo de evento inválido: " + str);
};


std::string Utils::tipoEventoToString(TipoEvento tipo) {
    switch (tipo) {
        case RG: return "RG";
        case AR: return "AR";
        case RM: return "RM";
        case UR: return "UR";
        case TR: return "TR";
        case EN: return "EN";
        default: return "UNKNOWN";
    };
};


// CONVERTE UM INTEIRO PARA STRING COM PREENCHIMENTO DE ZEROS. EX: 123 ==(Width 7)==> "0000123"
std::string Utils::intToString(int num, int width) {
    int strLen = std::to_string(num).length();
    if (num < 0 || strLen > width)
        return "ERROR_INT_TO_STRING";

    std::stringstream result;
    result << std::setw(width) << std::setfill('0') << num;
    return result.str();
};


TipoComando Utils::stringToTipoComando(const std::string& comando) {
    if (comando == "EV") return EV; // 0
    if (comando == "PC") return PC; // 1
    if (comando == "CL") return CL; // 2
    throw std::invalid_argument("Comando inválido: " + comando);
};

int Utils::getMax(int a, int b) {
    return (a > b) ? a : b;
};