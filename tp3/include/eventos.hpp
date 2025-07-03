#ifndef EVENTOS_HPP
#define EVENTOS_HPP

#include "../include/Utils.hpp"

class Evento {
    friend class VetorEventos;
    public:
        Evento(
            TipoEvento tipoEvento,
            int dataHora,
            int idPacote,
            int armazemOrigem = -1,
            int armazemDestino = -1,
            int secaoDestino = -1,
            const std::string& remetente = "",
            const std::string& destinatario = ""
        );

        ~Evento() = default;

        // GETTERS
        TipoEvento getTipoEvento() const;
        int getDataHora() const;
        int getIdPacote() const;
        int getArmazemOrigem() const;
        int getArmazemDestino() const;
        int getSecaoDestino() const;
        std::string getRemetente() const;
        std::string getDestinatario() const;

        // SETTERS
        void setTipoEvento(TipoEvento tipoEvento);
        void setDataHora(int dataHora);
        void setIdPacote(int idPacote);
        void setArmazemOrigem(int armazemOrigem);
        void setArmazemDestino(int armazemDestino);
        void setSecaoDestino(int secaoDestino);
        void setRemetente(const std::string& remetente);
        void setDestinatario(const std::string& destinatario);

        std::string getInfo() const;

    private:
        TipoEvento tipoEvento;     // Tipo do evento
        int dataHora;              // Data e hora do evento
        int idPacote;              // Identificador do pacote
        int armazemOrigem;         // Armazém de origem (apenas para RG e TR)
        int armazemDestino;        // Armazém de destino (para TODOS)
        int secaoDestino;          // Seção de destino (apenas para AR, RM, UR)
        std::string remetente;     // Nome do remetente (apenas para RG)
        std::string destinatario;  // Nome do destinatário (apenas para RG)
};
 

#endif