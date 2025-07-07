#ifndef ARVORE_AVL_HPP
#define ARVORE_AVL_HPP

#include <string>

#include "../include/Utils.hpp" // Para função getMax()
#include "../include/Consulta.hpp"
#include "../include/Evento.hpp"


template <typename TipoDado, typename TipoChave>
struct NodeAVL {
    TipoDado dado;
    TipoChave chave;
    NodeAVL* esquerda;
    NodeAVL* direita;
    int altura;

    NodeAVL(TipoDado d, TipoChave c) : dado(d), chave(c), esquerda(nullptr), direita(nullptr), altura(1) {}
};

// Declaração da Classe da Árvore AVL
template <typename TipoDado, typename TipoChave>
class ArvoreAVL {
    friend class SistemaLogistico;
    public:
        // Construtor e Destrutor
        ArvoreAVL();
        ~ArvoreAVL();

        // Funções Públicas Principais
        void inserir(TipoDado dado, TipoChave chave);
        void remover(TipoChave chave);
        TipoDado buscar(TipoChave chave); // Retorna o dado associado à chave

        // Funções Utilitárias Públicas
        int getTamanho() const;
        int getAltura() const;
        bool estaVazia() const;
        void limpar();

    private:
        NodeAVL<TipoDado, TipoChave>* raiz;
        int tamanho;

        // Métodos Auxiliares Privados (o coração da árvore)
        int getAlturaNode(NodeAVL<TipoDado, TipoChave>* no) const;
        int getFatorBalanceamento(NodeAVL<TipoDado, TipoChave>* no);
        void atualizarAltura(NodeAVL<TipoDado, TipoChave>* no);

        // Funções de Rotação
        NodeAVL<TipoDado, TipoChave>* rotacionarDireita(NodeAVL<TipoDado, TipoChave>* y);
        NodeAVL<TipoDado, TipoChave>* rotacionarEsquerda(NodeAVL<TipoDado, TipoChave>* x);

        // Funções Recursivas de Operação
        NodeAVL<TipoDado, TipoChave>* inserirRecursivo(NodeAVL<TipoDado, TipoChave>* no, TipoDado dado, TipoChave chave);
        NodeAVL<TipoDado, TipoChave>* removerRecursivo(NodeAVL<TipoDado, TipoChave>* no, TipoChave chave);
        NodeAVL<TipoDado, TipoChave>* buscarRecursivo(NodeAVL<TipoDado, TipoChave>* no, TipoChave chave);
        void limparRecursivo(NodeAVL<TipoDado, TipoChave>* no);
        
        NodeAVL<TipoDado, TipoChave>* encontrarMinimo(NodeAVL<TipoDado, TipoChave>* no);
};



#endif