#include "../include/armazem.hpp"
#include <iostream>

// ###################
// ARMAZÉM
// ###################

Armazem::Armazem(int id_armazem, int numero_total_destinos_possiveis){
    this->id_armazem = id_armazem;
    numero_secoes = numero_total_destinos_possiveis;

    // Cria vetor de seções, uma para cada possível destino
    secoes = new Secao[numero_secoes];
    for (int i = 0; i < numero_secoes; ++i) {
        secoes[i].SetArmazemDestino(i);
    };
};

Armazem::~Armazem() { delete[] secoes; };

void Armazem::SetIdArmazem(int id_armazem) { this->id_armazem = id_armazem; };
int Armazem::GetIdArmazem() { return id_armazem; };

void Armazem::AddPacote(Pacote* pacote) {
    if (pacote == nullptr) return;

    int destino = pacote->GetProximoSalto();

    // Se não há mais destinos para o pacote, ignora
    if (destino == -1) return;

    Secao* secao = GetSecaoByDestino(destino);

    // Verifica se existe uma seção válida para o destino
    if (secao != nullptr) {
        secao->EmpilharPacote(pacote);
        pacote->SetEstado(Pacote::Armazenado);
    } else {
        std::cerr << "[ERRO] Armazem " << id_armazem 
                  << " não possui seção para o destino " << destino << std::endl;
    };
};

Secao* Armazem::GetSecaoByDestino(int id_destino) {
    // Verifica se o destino está dentro dos limites do vetor
    if (id_destino < 0 || id_destino >= numero_secoes) {
        return nullptr;
    };
    return &secoes[id_destino];
};

void Armazem::PrintAllPacotes() {
    std::cout << "--- Armazem " << id_armazem << " ---" << std::endl;
    bool encontrou_pacote = false;

    for (int i = 0; i < numero_secoes; ++i) {
        if (!secoes[i].Vazia()) {
            secoes[i].Print();
            encontrou_pacote = true;
        };
    };

    if (!encontrou_pacote) {
        std::cout << "  Nenhum pacote armazenado." << std::endl;
    };

    std::cout << "--------------------------" << std::endl;
};
