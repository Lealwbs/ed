#include "../include/ArvoreAVL.hpp"

// Função utilitária para obter o máximo entre dois inteiros
int max(int n1, int n2) {
    return (n1 >= n2) ? n1 : n2;
}

// Construtor - Inicializa árvore vazia com função de extração de chave
template <typename D, typename K>
ArvoreAVL<D, K>::ArvoreAVL(K (*obterChaveFunc)(D)) : 
    raiz(nullptr), obterChaveFunc(obterChaveFunc), contador(0) {}

// Destrutor - Remove todos os nós recursivamente
template <typename D, typename K>
ArvoreAVL<D, K>::~ArvoreAVL() {
    _limpar(raiz);
}

// Limpa a árvore em pós-ordem
template <typename D, typename K>
void ArvoreAVL<D, K>::_limpar(NodeAVL<D>* node) {
    if (node) {
        _limpar(node->esquerda);
        _limpar(node->direita);
        delete node;
    }
}

// Retorna altura do nó (0 para nullptr)
template <typename D, typename K>
int ArvoreAVL<D, K>::_getAltura(NodeAVL<D>* node) const {
    return node ? node->altura : 0;
}

// Calcula fator de balanceamento (altura esquerda - altura direita)
template <typename D, typename K>
int ArvoreAVL<D, K>::_getFatorBalanceamento(NodeAVL<D>* node) const {
    return node ? _getAltura(node->esquerda) - _getAltura(node->direita) : 0;
}

// Atualiza altura do nó baseado nos filhos
template <typename D, typename K>
void ArvoreAVL<D, K>::_atualizarAltura(NodeAVL<D>* node) {
    node->altura = 1 + max(_getAltura(node->esquerda), _getAltura(node->direita));
}

// Rotação à direita para caso de desbalanceamento esquerda-esquerda
template <typename D, typename K>
NodeAVL<D>* ArvoreAVL<D, K>::_rotacaoDireita(NodeAVL<D>* y) {
    NodeAVL<D>* x = y->esquerda;
    NodeAVL<D>* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    _atualizarAltura(y);
    _atualizarAltura(x);

    return x;
}

// Rotação à esquerda para caso de desbalanceamento direita-direita
template <typename D, typename K>
NodeAVL<D>* ArvoreAVL<D, K>::_rotacaoEsquerda(NodeAVL<D>* x) {
    NodeAVL<D>* y = x->direita;
    NodeAVL<D>* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    _atualizarAltura(x);
    _atualizarAltura(y);

    return y;
}

// Balanceia o nó e retorna nova raiz da subárvore
template <typename D, typename K>
NodeAVL<D>* ArvoreAVL<D, K>::_balancear(NodeAVL<D>* node) {
    _atualizarAltura(node);
    int balance = _getFatorBalanceamento(node);

    // Casos pesados à esquerda
    if (balance > 1) {
        if (_getFatorBalanceamento(node->esquerda) >= 0)  // Caso esquerda-esquerda
            return _rotacaoDireita(node);
        else {                                           // Caso esquerda-direita
            node->esquerda = _rotacaoEsquerda(node->esquerda);
            return _rotacaoDireita(node);
        }
    }
    
    // Casos pesados à direita
    if (balance < -1) {
        if (_getFatorBalanceamento(node->direita) <= 0) // Caso direita-direita
            return _rotacaoEsquerda(node);
        else {                                         // Caso direita-esquerda
            node->direita = _rotacaoDireita(node->direita);
            return _rotacaoEsquerda(node);
        }
    }

    return node;
}

// Inserção pública - incrementa contador
template <typename D, typename K>
void ArvoreAVL<D, K>::inserir(D dado) {
    raiz = _inserir(raiz, dado);
    contador++;
}

// Inserção recursiva com balanceamento automático
template <typename D, typename K>
NodeAVL<D>* ArvoreAVL<D, K>::_inserir(NodeAVL<D>* node, D dado) {
    if (!node) return new NodeAVL<D>(dado);

    K chaveAtual = obterChaveFunc(node->dado);
    K novaChave = obterChaveFunc(dado);

    if (novaChave < chaveAtual)
        node->esquerda = _inserir(node->esquerda, dado);
    else if (novaChave > chaveAtual)
        node->direita = _inserir(node->direita, dado);
    else
        return node; // Chaves duplicadas não são permitidas

    return _balancear(node);
}

// Busca pública - retorna dado ou D padrão
template <typename D, typename K>
D ArvoreAVL<D, K>::buscar(K chave) const {
    NodeAVL<D>* node = _buscar(raiz, chave);
    return node ? node->dado : D();
}

// Busca recursiva por chave
template <typename D, typename K>
NodeAVL<D>* ArvoreAVL<D, K>::_buscar(NodeAVL<D>* node, K chave) const {
    if (!node) return nullptr;

    K chaveAtual = obterChaveFunc(node->dado);

    if (chave == chaveAtual)
        return node;
    else if (chave < chaveAtual)
        return _buscar(node->esquerda, chave);
    else
        return _buscar(node->direita, chave);
}

// Remoção pública - decrementa contador
template <typename D, typename K>
void ArvoreAVL<D, K>::remover(K chave) {
    raiz = _remover(raiz, chave);
    contador--;
}

// Remoção recursiva com balanceamento
template <typename D, typename K>
NodeAVL<D>* ArvoreAVL<D, K>::_remover(NodeAVL<D>* node, K chave) {
    if (!node) return nullptr;

    K chaveAtual = obterChaveFunc(node->dado);

    if (chave < chaveAtual)
        node->esquerda = _remover(node->esquerda, chave);
    else if (chave > chaveAtual)
        node->direita = _remover(node->direita, chave);
    else {
        // Nó encontrado - trata casos de remoção
        if (!node->esquerda || !node->direita) {
            // Caso com um filho
            NodeAVL<D>* temp = node->esquerda ? node->esquerda : node->direita;
            if (!temp) {
                // Sem filhos
                temp = node;
                node = nullptr;
            } else {
                // Um filho - copia conteúdo
                *node = *temp;
            }
            delete temp;
        } else {
            // Dois filhos - encontra sucessor in-order
            NodeAVL<D>* temp = _noDeMenorValor(node->direita);
            node->dado = temp->dado;
            node->direita = _remover(node->direita, obterChaveFunc(temp->dado));
        }
    }

    if (!node) return nullptr;

    return _balancear(node);
}

// Encontra nó mais à esquerda (valor mínimo) da subárvore
template <typename D, typename K>
NodeAVL<D>* ArvoreAVL<D, K>::_noDeMenorValor(NodeAVL<D>* node) const {
    while (node && node->esquerda) node = node->esquerda;
    return node;
}

// Retorna o tamanho da árvore
template <typename D, typename K>
int ArvoreAVL<D, K>::getTamanho() const {
    return contador;
}

// Travessia in-order pública com callback simples
template <typename D, typename K>
void ArvoreAVL<D, K>::percorrerEmOrdem(void (*visitar)(D)) const {
    _percorrerEmOrdem(raiz, visitar);
}

// Travessia in-order recursiva
template <typename D, typename K>
void ArvoreAVL<D, K>::_percorrerEmOrdem(NodeAVL<D>* node, void (*visitar)(D)) const {
    if (node) {
        _percorrerEmOrdem(node->esquerda, visitar);
        visitar(node->dado);
        _percorrerEmOrdem(node->direita, visitar);
    }
}

// Travessia in-order pública com parâmetro de contexto
template <typename D, typename K>
void ArvoreAVL<D, K>::percorrerComCallback(void (*visitar)(D, void*), void* contexto) const {
    _percorrerComCallback(raiz, visitar, contexto);
}

// Travessia in-order recursiva com contexto
template <typename D, typename K>
void ArvoreAVL<D, K>::_percorrerComCallback(NodeAVL<D>* node, void (*visitar)(D, void*), void* contexto) const {
    if (node) {
        _percorrerComCallback(node->esquerda, visitar, contexto);
        visitar(node->dado, contexto);
        _percorrerComCallback(node->direita, visitar, contexto);
    }
}

#include "../include/Consulta.hpp"
#include "../include/Evento.hpp"

template class ArvoreAVL<Pacote*, int>;
template class ArvoreAVL<Cliente*, std::string>;
template class ArvoreAVL<Evento*, int>;