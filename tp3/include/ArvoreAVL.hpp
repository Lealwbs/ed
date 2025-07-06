#ifndef ARVORE_AVL_HPP
#define ARVORE_AVL_HPP

template <typename D> // <dado>
struct NodeAVL {
    D dado;                 // Dado armazenado no nó
    NodeAVL* esquerda;      // Ponteiro para o filho da esquerda
    NodeAVL* direita;       // Ponteiro para o filho da direita
    int altura;             // Altura do nó para o balanceamento
    NodeAVL(D novoDado) : dado(novoDado), esquerda(nullptr), direita(nullptr), altura(1) {}
};

template <typename D, typename K> // <dado e key>
class ArvoreAVL {
    public:
        ArvoreAVL(K (*obterChaveFunc)(D));  // Exige uma função para extrair a chave de um objeto do tipo T
        ~ArvoreAVL();
        
        int getTamanho() const;
        void inserir(D dado);
        void remover(K chave);
        D buscar(K chave) const;

        // Percorre a árvore em ordem (in-order) e aplica uma função de visita a cada elemento, e em ordem com uma função de callback que aceita um contexto
        void percorrerEmOrdem(void (*visitar)(D)) const;
        void percorrerComCallback(void (*visitar)(D, void*), void* contexto) const;

    private:
        NodeAVL<D>* raiz;        // Ponteiro para a raiz da árvore
        K (*obterChaveFunc)(D);  // Ponteiro para a função que extrai a chave
        int contador;            // Número de elementos na árvore

        NodeAVL<D>* _inserir(NodeAVL<D>* node, D dado);        // Insere um nó recursivamente
        NodeAVL<D>* _remover(NodeAVL<D>* node, K chave);       // Remove um nó recursivamente
        NodeAVL<D>* _buscar(NodeAVL<D>* node, K chave) const;  // Busca um nó recursivamente

        // Função recursiva para o percurso em ordem, e em ordem com callback e contexto
        void _percorrerEmOrdem(NodeAVL<D>* node, void (*visitar)(D)) const;
        void _percorrerComCallback(NodeAVL<D>* node, void (*visitar)(D, void*), void* contexto) const;
        
        int _getAltura(NodeAVL<D>* node) const;               // Retorna a altura de um nó (seguro para nós nulos)
        void _limpar(NodeAVL<D>* node);                       // Libera a memória da árvore de forma recursiva
        void _atualizarAltura(NodeAVL<D>* node);              // Atualiza a altura de um nó com base na altura de seus filhos
        int _getFatorBalanceamento(NodeAVL<D>* node) const;   // Calcula o fator de balanceamento de um nó
        NodeAVL<D>* _noDeMenorValor(NodeAVL<D>* node) const;  // Encontra o nó com o menor valor na sub-árvore (o mais à esquerda)
        
        // ROTAÇÕES E BALANCEAMENTO 
        NodeAVL<D>* _rotacaoDireita(NodeAVL<D>* y);
        NodeAVL<D>* _rotacaoEsquerda(NodeAVL<D>* x);
        NodeAVL<D>* _balancear(NodeAVL<D>* node);
    };

#endif