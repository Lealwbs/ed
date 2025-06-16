#include "../include/pacote.hpp"
#include "../include/outros_tads.hpp"

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
int Pacote::GetIdPacote(){ return id_pacote; };
int Pacote::GetArmazemInicial(){ return armazem_inicial; };
int Pacote::GetArmazemFinal(){ return armazem_final; };
double Pacote::GetTempoChegada(){ return tempo_chegada; };
double Pacote::GetTempoArmazenado(){ return tempo_armazenado; };
double Pacote::GetTempoTransito(){ return tempo_transito; };
Pacote::Estado_Pacote Pacote::GetEstado(){ return estado; };

// MÉTODOS SET
void Pacote::SetEstado(Estado_Pacote novo_estado){ estado = novo_estado; };
void Pacote::SetTempoArmazenado(double tempo){ tempo_armazenado = tempo; };
void Pacote::SetTempoTransito(double tempo){ tempo_transito = tempo; };

// ROTA
Lista* Pacote::GetRota(){ return rota; };

void Pacote::SetRota(Lista* rota){
    if (this->rota != nullptr) { delete this->rota; }; // Se já existe uma rota, apaga ela 
    this->rota = rota; // Seta a nova rota
};

void Pacote::AvancarRota(){ // Remove o nó atual da rota
    if (rota != nullptr && !rota->Vazia()) {
        rota->RemoverInicio();
    }
} 

// O próximo salto é o 2º elemento da lista "rota", caso não tenha segundo elemento, ou seja vazio/nulo, retorna -1 (não possui)
int Pacote::GetProximoSalto(){
    if (rota->Vazia() || rota == nullptr || rota->GetHead()->proximo == nullptr) return -1; 
    return rota->GetHead()->proximo->valor;
};

// OUTROS MÉTODOS
void Pacote::PrintInfo() {
    std::cout << tempo_chegada 
    << " pac " << id_pacote
    << " org " << armazem_inicial
    << " dst " << armazem_final << std::endl; 
};
