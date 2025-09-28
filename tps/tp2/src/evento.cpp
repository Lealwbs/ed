#include "../include/evento.hpp"

// ###################
// EVENTO 
// ###################

Evento::Evento() {};
Evento::~Evento() {};


double Evento::GetTempo() { return tempo; }
long long Evento::GetPrioridade() { return prioridade; }
Evento::TipoEvento Evento::GetTipo() { return tipo; }

void Evento::SetTempo(double tempo) { this->tempo = tempo; }
void Evento::SetPrioridade(long long prioridade) { this->prioridade = prioridade; }
void Evento::SetTipo(TipoEvento tipo) { this->tipo = tipo; }

// ###################
// EVENTO TRANSPORTE
// ###################

EventoTransporte::EventoTransporte(double tempo, int armazem_origem, int armazem_destino){
    this->tipo = TipoEvento::Transporte;
    this->tempo = tempo;
    this->armazem_origem = armazem_origem;
    this->armazem_destino = armazem_destino;
    this->prioridade = 0;
    UpdatePrioridadeTransporte(armazem_origem, armazem_destino);
}

EventoTransporte::~EventoTransporte(){};

int EventoTransporte::GetArmazemOrigem() { return armazem_origem; }
int EventoTransporte::GetArmazemDestino() { return armazem_destino; }

void EventoTransporte::UpdatePrioridadeTransporte(int armazem_origem, int armazem_destino) {
    long long tempo_inteiro = static_cast<long long>(tempo);
    long long dados_evento = armazem_origem * 10000 + armazem_destino;
    long long peso_tipo = 2;  // Transporte tem prioridade menor que chegada (executa depois)

    prioridade = tempo_inteiro * 1000000000LL + dados_evento * 10LL + peso_tipo;
}


void EventoTransporte::SetArmazemOrigem(int armazem_origem){ this->armazem_origem = armazem_origem; };
void EventoTransporte::SetArmazemDestino(int armazem_destino){ this->armazem_destino = armazem_destino; };



// ###################
// EVENTO CHEGADA
// ###################

EventoChegada::EventoChegada(double tempo, Pacote* pacote, int armazem_chegada){
    this->tipo = TipoEvento::Chegada;
    this->tempo = tempo;
    this->pacote = pacote;
    this->armazem_chegada = armazem_chegada;
    this->prioridade = 0;
    UpdatePrioridadeChegada(pacote);
}

EventoChegada::~EventoChegada(){};

Pacote* EventoChegada::GetPacote() { return pacote; }
int EventoChegada::GetArmazemChegada() { return armazem_chegada; }

void EventoChegada::UpdatePrioridadeChegada(Pacote* pacote) {
    long long tempo_inteiro = static_cast<long long>(tempo);
    long long pacote_id = pacote->GetIdPacote();
    long long peso_tipo = 1;  // Chegada tem menor prioridade (executa antes se tempos iguais)

    // Estrutura de prioridade: tempo mais significativo, depois pacote_id, depois tipo
    prioridade = tempo_inteiro * 1000000000LL + pacote_id * 10LL + peso_tipo;
}

void EventoChegada::SetPacote(Pacote* pacote) { this->pacote = pacote; }
void EventoChegada::SetArmazemChegada(int armazem_chegada) { this->armazem_chegada = armazem_chegada; }