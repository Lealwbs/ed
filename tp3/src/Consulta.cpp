#include "../include/Consulta.hpp"

Cliente::Cliente(std::string nome){ 
    this->nome = nome; 
};

void Cliente::setNome(const std::string& nome){ 
    this->nome = nome; 
};

std::string Cliente::getNome() const { 
    return nome; 
};

const ListaInt &Cliente::getPacotesRemetente(){
    return pacotesRemetente;
};

const ListaInt &Cliente::getPacotesDestinatario(){
    return pacotesDestinatario;
};

void Cliente::adicionarPacoteDestinatario(int idPacote){
    pacotesDestinatario.insereFinal(idPacote);
};

void Cliente::adicionarPacoteRemetente(int idPacote){
    pacotesRemetente.insereFinal(idPacote);
};

Pacote::Pacote(int id){
    this->id = id;
    this->primeiroEvento = nullptr;
    this->ultimoEvento = nullptr;
};

void Pacote::setId(int id) { 
    this->id = id; 
};

void Pacote::setPrimeiroEvento(Evento* evento) { 
    this->primeiroEvento = evento; 
};

void Pacote::setUltimoEvento(Evento* evento) { 
    this->ultimoEvento = evento; 
};

int Pacote::getId() const { 
    return id; 
};

Evento* Pacote::getPrimeiroEvento() const { 
    return this->primeiroEvento; 
};

Evento* Pacote::getUltimoEvento() const { 
    return this->ultimoEvento; 
};