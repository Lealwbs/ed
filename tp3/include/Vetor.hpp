#ifndef VETOR_HPP
#define VETOR_HPP

typedef struct NodeVetor_t {
    int valor;
    struct NodeVetor_t* prox;
} NodeVetor;

class Vetor {
    public:
        Vetor();
        ~Vetor();
        
        // Métodos de acesso
        int GetItem(int pos);
        void SetItem(int item, int pos);
        int GetTamanho();
        bool Vazio();
        
        // Métodos de inserção
        void InsereInicio(int item);
        void InsereFinal(int item);
        void InserePosicao(int item, int pos);
        
        // Métodos de remoção
        int RemoveInicio();
        int RemoveFinal();
        int RemovePosicao(int pos);
        
        // Métodos de busca e utilitários
        int Pesquisa(int item);
        void Imprime();
        void Limpa();
        
    private:
        int tamanho;
        NodeVetor* primeiro;
        NodeVetor* ultimo;    
        NodeVetor* Posiciona(int pos, bool antes = false);
};

#endif