#include "../include/pacote.hpp"

Pacote::Pacote(double tempo_chegada, int id_pacote, int armazem_inicial, int armazem_final){
    this->tempo_chegada = tempo_chegada;
    this->id_pacote = id_pacote;
    this->armazem_inicial = armazem_inicial;
    this->armazem_final = armazem_final;
    this->estado = Pacote::Nao_Postado;
    this->tempo_armazenado = 0.0;
    this->tempo_transito = 0.0; };

Pacote::~Pacote(){};

// MÉTODOS GET
double Pacote::GetTempoChegada(){ return tempo_chegada; };
int Pacote::GetIdPacote(){ return id_pacote; };
int Pacote::GetArmazemInicial(){ return armazem_inicial; };
int Pacote::GetArmazemFinal(){ return armazem_final; };
Pacote::Estado_Pacote Pacote::GetEstado(){ return estado; };
//Lista* Pacote::GetRota(){  }; 
double Pacote::GetTempoArmazenado(){ return tempo_armazenado; };
double Pacote::GetTempoTransito(){ return tempo_transito; };

// MÉTODOS SET
void Pacote::SetEstado(Estado_Pacote novo_estado){ estado = novo_estado; };
void Pacote::SetTempoArmazenado(double tempo){ tempo_armazenado = tempo; };
void Pacote::SetTempoTransito(double tempo){ tempo_transito = tempo; };

// OUTROS MÉTODOS
void Pacote::PrintInfo() {
    std::cout << tempo_chegada 
    << " pac " << id_pacote
    << " org " << armazem_inicial
    << " dst " << armazem_final << std::endl; 
};
