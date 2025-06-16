#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include "../include/evento.hpp"
#include "../include/pilha_secao.hpp"


class Armazem { // Um armazém contem várias seções
    public:
        Armazem(int id_armazem, int numero_total_destinos_possiveis);
        ~Armazem();
        
        void SetIdArmazem(int id_armazem);
        int GetIdArmazem();

        void AddPacote(Pacote* pacote); // Adiciona um pacote numa seção com base no seu próximo destino

        Secao* GetSecaoByDestino(int id_destino); // Retorna a seção correspondente a um destino específico

        void PrintAllPacotes(); //Printa todos os pacotes de todas as seções do armazém (DEBUG)

    private:
        int id_armazem; // Identificador do armazém
        int numero_secoes; // Número de seções criadas
        Secao* secoes;  // Vetor array de seções do armazém
};

#endif