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
Lista* GetRota(){ return rota; };

void SetRota(Lista* rota){
    if (this->rota != nullptr) {
        delete this->rota;
    }
    this->rota = rota;
};

void AvancarRota(){ // Remove o nó atual da rota

} 

int GetProximoSalto(){
    if (rota->Vazia() || rota == nullptr || rota->GetInicio()->proximo == nullptr) {
        // Se a rota não existe, está vazia, ou só tem um elemento (o destino final),
        // não há próximo salto.
        return -1; 
    }
    // O próximo salto é o segundo elemento da lista.
    return rota->GetInicio()->proximo->valorInteiro;
};



// OUTROS MÉTODOS
void Pacote::PrintInfo() {
    std::cout << tempo_chegada 
    << " pac " << id_pacote
    << " org " << armazem_inicial
    << " dst " << armazem_final << std::endl; 
};
