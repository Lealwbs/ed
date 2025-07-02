#ifndef EVENTOS_HPP
#define EVENTOS_HPP

#include <string>
#include <sstream> // Para std::stringstream
#include <iomanip> // Para std::setw e std::setfill

enum TipoEvento {
    RG, // Pacote ainda não foi postado (apenas registrado no sistema)
    AR, // Pacote chegou no armazém e foi armazenado na respectiva seção
    RM, // Pacote foi removido da seção para tentativa de transporte
    UR, // Pacote foi rearmazenado por não ser possível transportá-lo
    TR, // Pacote sendo transportado entre armazéns
    EN  // Pacote entregue
};

// ATRIBUTOS DE CADA EVENTO:
// RG: data_hora EV tipo_evento id_pacote remetente destinatario armazem_origem armazem_destino
// AR: data_hora EV tipo_evento id_pacote armazem_destino secao_destino
// RM: data_hora EV tipo_evento id_pacote armazem_destino secao_destino
// UR: data_hora EV tipo_evento id_pacote armazem_destino secao_destino
// TR: data_hora EV tipo_evento id_pacote armazem_origem armazem_destino
// EN: data_hora EV tipo_evento id_pacote armazem_destino


std::string tipoEventoToString(TipoEvento tipo) {
    switch (tipo){
        case RG: return "RG";
        case AR: return "AR";
        case RM: return "RM";
        case UR: return "UR";
        case TR: return "TR";
        case EN: return "EN";
        default: return "UNKNOWN";
    };
};


TipoEvento stringToTipoEvento(const std::string& str) {
    if (str == "RG") return RG;
    if (str == "AR") return AR;
    if (str == "RM") return RM;
    if (str == "UR") return UR;
    if (str == "TR") return TR;
    if (str == "EN") return EN;
    throw std::invalid_argument("Tipo de evento inválido: " + str);
};


std::string intToString(int num, int width = 3) {
    int strLen = std::to_string(num).length();
    if (num < 0 || strLen > width ) 
        return "ERROR_INT_TO_STRING";

    std::stringstream result;
    result << std::setw(width) << std::setfill('0') << num;
    
    return result.str();
};


class Evento {
    public:
        Evento(
            TipoEvento tipo, 
            int dataHora, 
            int idPacote, 
            int armazemOrigem = -1, 
            int armazemDestino = -1, 
            int secaoDestino = -1,
            const std::string& remetente = "", 
            const std::string& destinatario = ""
        ): 
            tipoEvento(tipo), 
            dataHora(dataHora), 
            idPacote(idPacote),
            armazemOrigem(armazemOrigem), 
            armazemDestino(armazemDestino),
            secaoDestino(secaoDestino),
            remetente(remetente), 
            destinatario(destinatario) {};

        ~Evento() = default;


        // GETTERS
        TipoEvento getTipoEvento()      const { return tipoEvento; };
        int getDataHora()               const { return dataHora; };
        int getIdPacote()               const { return idPacote; };
        int getArmazemOrigem()          const { return armazemOrigem; };
        int getArmazemDestino()         const { return armazemDestino; };
        int getSecaoDestino()           const { return secaoDestino; };
        std::string getRemetente()      const { return remetente; };
        std::string getDestinatario()   const { return destinatario; };


        // SETTERS
        void setTipoEvento(TipoEvento tipo)                     { tipoEvento = tipo; };
        void setDataHora(int dataHora)                          { this->dataHora = dataHora; };
        void setIdPacote(int idPacote)                          { this->idPacote = idPacote; };
        void setArmazemOrigem(int armazemOrigem)                { this->armazemOrigem = armazemOrigem; };
        void setArmazemDestino(int armazemDestino)              { this->armazemDestino = armazemDestino; };
        void setSecaoDestino(int secaoDestino)                  { this->secaoDestino = secaoDestino; };
        void setRemetente(const std::string& remetente)         { this->remetente = remetente; };
        void setDestinatario(const std::string& destinatario)   { this->destinatario = destinatario; };


        // GET_INFO: Se a informação existir, inclui ela na string de retorno.
        std::string getInfo() const {
            std::string result = "";

            result += intToString(dataHora, 7) + " ";
            result += tipoEventoToString(tipoEvento) + " ";
            result += intToString(idPacote, 3) + " ";
            
            if (!remetente.empty())     result += remetente + " ";
            if (!destinatario.empty())  result += destinatario + " ";
            if (armazemOrigem != -1)    result += intToString(armazemOrigem, 3) + " ";
            if (armazemDestino != -1)   result += intToString(armazemDestino, 3) + " ";
            if (secaoDestino != -1)     result += intToString(secaoDestino, 3) + " ";

            return result;
        };


    private:
        TipoEvento tipoEvento; // Tipo do evento
        int dataHora; // Data e hora do evento
        int idPacote; // Identificador do pacote
        int armazemOrigem; // Armazém de origem (apenas para RG e TR)
        int armazemDestino; // Armazém de destino (para TODOS)
        int secaoDestino; // Seção de destino (apenas para AR, RM, UR)
        std::string remetente; // Nome do remetente (apenas para RG)
        std::string destinatario; // Nome do destinatário (apenas para RG)
};
 

#endif