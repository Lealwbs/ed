#ifndef CONSULTA_HPP
#define CONSULTA_HPP

#include "../include/Vetor.hpp"
#include "../include/EventosVetor.hpp"

#include <string>

class Cliente{
    public:
        Cliente(std::string nome) : nome(nome) {};
        ~Cliente() = default;

        // SETTERS
        void setNome(const std::string& nome) { this->nome = nome; };

        // GETTERS
        std::string getNome() { return nome; };
        Vetor& getpacotesComoRemetente() { return pacotesComoRemetente; };
        Vetor& getpacotesComoDestinatario() { return pacotesComoDestinatario; };

        // ADD PACOTES
        void addPacoteRemetente(int idPacote) { pacotesComoDestinatario.InsereFinal(idPacote); };
        void addPacoteDestinatario(int idPacote) { pacotesComoRemetente.InsereFinal(idPacote); };

    private:
        std::string nome;
        Vetor pacotesComoRemetente; 
        Vetor pacotesComoDestinatario; 
};

class Pacote {
    public:
        Pacote(int id) : id(id) {}
        ~Pacote() = default;

        // SETTERS
        void setId(int novoId){ this->id = novoId;}

        // GETTERS
        int getId() const { return id; }

        // OUTROS ME´TODOS
        void adicionarEvento(const Evento& evento) { historicoEventos.InsereFinal(evento);}
        EventosVetor& getHistoricoEventos() { return historicoEventos;}

    private:
        int id;
        EventosVetor historicoEventos;
    };

#endif
