#ifndef EVENTOS_HPP
#define EVENTOS_HPP

#include <string>

enum TipoEvento {
    RG, // Pacote ainda não foi postado (apenas registrado no sistema)
    AR, // Pacote chegou no armazém e foi armazenado na respectiva seção
    RM, // Pacote foi removido da seção para tentativa de transporte
    UR, // Pacote foi rearmazenado por não ser possível transportá-lo
    TR, // Pacote sendo transportado entre armazéns
    EN  // Pacote entregue
};

class EventoBase{
    public:
        // SETTERS  
        void setTipoEvento(TipoEvento tipo_evento);
        void setDataHora(int data_hora);
        void setIdPacote(int id_pacote);
        // GETTERS
        TipoEvento getTipoEvento() const;
        int getDataHora() const;
        int getIdPacote() const;

    protected:
        TipoEvento tipo_evento;
        int data_hora;
        int id_pacote;
};

class EventoRG{
    public:
        // SETTERS
        void setRemetente(std::string remetente);
        void setDestinatario(std::string destinatario);
        void setArmazemOrigem(int armazem_origem);
        void setArmazemDestino(int armazem_destino);
        // GETTERS
        std::string getRemetente() const;
        std::string getDestinatario() const;
        int getArmazemOrigem() const;
        int getArmazemDestino() const;

    private:
        std::string remetente;
        std::string destinatario;
        int armazem_origem;
        int armazem_destino;
};

class EventoAR{
    public:
        // SETTERS
        void setArmazemDestino(int armazem_destino);
        void setSecaoDestino(int secao_destino);
        // GETTERS
        int getArmazemDestino() const;
        int getSecaoDestino() const;

    private:
        int armazem_destino;
        int secao_destino;
};

class EventoRM{
    public:
        // SETTERS
        void setArmazemDestino(int armazem_destino);
        void setSecaoDestino(int secao_destino);
        // GETTERS
        int getArmazemDestino() const;
        int getSecaoDestino() const;

    private:
        int armazem_destino;
        int secao_destino;
};

class EventoUR{
    public:
        // SETTERS
        void setArmazemDestino(int armazem_destino);
        void setSecaoDestino(int secao_destino);
        // GETTERS
        int getArmazemDestino() const;
        int getSecaoDestino() const;

    private:
        int armazem_destino;
        int secao_destino;
};

class EventoTR{
    public:
        // SETTERS
        void setArmazemOrigem(int armazem_origem);
        void setArmazemDestino(int armazem_destino);
        // GETTERS
        int getArmazemOrigem() const;
        int getArmazemDestino() const;

    private:
        int armazem_origem;
        int armazem_destino;
};

class EventoEN{
    public:
        // SETTERS
        void setArmazemDestino(int armazem_destino);
        // GETTERS
        int getArmazemDestino() const;

    private:
        int armazem_destino;
};

// OBS: Fazer os trem tudo aqui, sem precisar do .hpp (OU NÃO)


#endif