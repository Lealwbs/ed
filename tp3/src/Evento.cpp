#include "../include/Evento.hpp"

Evento::Evento(
    TipoEvento tipoEvento,
    int dataHora,
    int idPacote,
    int armazemOrigem,
    int armazemDestino,
    int secaoDestino,
    const std::string& remetente,
    const std::string& destinatario
    ){
        this->tipoEvento = tipoEvento;
        this->dataHora = dataHora;
        this->idPacote = idPacote;
        this->armazemOrigem = armazemOrigem;
        this->armazemDestino = armazemDestino;
        this->secaoDestino = secaoDestino;
        this->remetente = remetente;
        this->destinatario = destinatario;
    };
 

// GETTERS
TipoEvento Evento::getTipoEvento()      const { return tipoEvento; };
int Evento::getDataHora()               const { return dataHora; };
int Evento::getIdPacote()               const { return idPacote; };
int Evento::getArmazemOrigem()          const { return armazemOrigem; };
int Evento::getArmazemDestino()         const { return armazemDestino; };
int Evento::getSecaoDestino()           const { return secaoDestino; };
std::string Evento::getRemetente()      const { return remetente; };
std::string Evento::getDestinatario()   const { return destinatario; };


// SETTERS
void Evento::setTipoEvento(TipoEvento tipoEvento)               { this->tipoEvento = tipoEvento; };
void Evento::setDataHora(int dataHora)                          { this->dataHora = dataHora; };
void Evento::setIdPacote(int idPacote)                          { this->idPacote = idPacote; };
void Evento::setArmazemOrigem(int armazemOrigem)                { this->armazemOrigem = armazemOrigem; };
void Evento::setArmazemDestino(int armazemDestino)              { this->armazemDestino = armazemDestino; };
void Evento::setSecaoDestino(int secaoDestino)                  { this->secaoDestino = secaoDestino; };
void Evento::setRemetente(const std::string& remetente)         { this->remetente = remetente; };
void Evento::setDestinatario(const std::string& destinatario)   { this->destinatario = destinatario; };


// GET_INFO: Se a informação existir, inclui ela na string de retorno.
std::string Evento::getInfo() const {
    std::string result;
    result += Utils::intToString(dataHora, 7) + " ";
    result += "EV ";
    result += Utils::tipoEventoToString(tipoEvento) + " ";
    result += Utils::intToString(idPacote, 3) + " ";

    if (!remetente.empty())     result += remetente + " ";
    if (!destinatario.empty())  result += destinatario + " ";
    if (armazemOrigem != -1)    result += Utils::intToString(armazemOrigem, 3) + " ";
    if (armazemDestino != -1)   result += Utils::intToString(armazemDestino, 3) + " ";
    if (secaoDestino != -1)     result += Utils::intToString(secaoDestino, 3) + " ";

    return result;
}
