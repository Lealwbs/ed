#ifndef CONSULTA_HPP
#define CONSULTA_HPP

#include "../include/Vetor.hpp"

#include <string>

class Cliente{
    public:
        Cliente(std::string nome);
        ~Cliente() = default;

        // SETTERS
        void setNome(const std::string& nome);

        // GETTERS
        std::string getNome() const;
        Vetor& getPacotesDestinatario() const; 
        Vetor& getPacotesRemetente() const; 

        // ADD PACOTES
        void addPacoteRemetente(int idPacote);
        void addPacoteDestinatario(int idPacote);

    private:
        std::string nome;
        Vetor pacotesRemetente; 
        Vetor pacotesDestinatario; 
};


class Pacote{
    public:
        Pacote(int id);
        ~Pacote() = default;

        // SETTERS
        void setId(int id);
        void setPrimeiroEvento(Evento* evento);
        void setUltimoEvento(Evento* evento);
        
        // GETTERS
        int getIdPacote() const;
        Evento* getPrimeiroEvento() const;
        Evento* getUltimoEvento() const;
        
    private:
        int id;
        Evento* primeiroEvento;
        Evento* ultimoEvento;
};

#endif
