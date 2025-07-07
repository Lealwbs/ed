#ifndef CONSULTA_HPP
#define CONSULTA_HPP

#include "../include/Vetor.hpp"

#include <string>

class Cliente{
    public:
        Cliente(std::string nome) : nome(nome) {};
        ~Cliente() = default;

        // SETTERS
        void setNome(const std::string& nome) { this->nome = nome; };

        // GETTERS
        std::string getNome() const { return nome; };
        Vetor& getPacotesRemetente() const { return pacotesRemetente; };
        Vetor& getPacotesDestinatario() const { return pacotesDestinatario; };

        // ADD PACOTES
        void addPacoteRemetente(int idPacote) { pacotesDestinatario.insereFinal(idPacote); };
        void addPacoteDestinatario(int idPacote) { pacotesRemetente.insereFinal(idPacote); };

    private:
        std::string nome;
        Vetor pacotesRemetente; 
        Vetor pacotesDestinatario; 
};

#endif

class Pacote {
    public:
        Pacote(int id) : id(id), primeiroEvento(nullptr), ultimoEvento(nullptr) {}
        ~Pacote() = default;

        // SETTERS
        void setId(int novoId){ this->id = novoId;}
        void setPrimeiroEvento(Evento* evento) { this->primeiroEvento = evento; }
        void setUltimoEvento(Evento* evento) { this->ultimoEvento = evento; }

        // GETTERS
        int getId() const { return id; }
        Evento* getPrimeiroEvento() const { return primeiroEvento; }
        Evento* getUltimoEvento() const { return ultimoEvento; }

    private:
        int id;
        Evento* primeiroEvento;
        Evento* ultimoEvento;
    };

#endif
