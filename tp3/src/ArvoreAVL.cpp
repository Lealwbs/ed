#include "../include/ArvoreAVL.hpp"

// --- Construtor e Destrutor ---

template <typename TipoDado, typename TipoChave>
ArvoreAVL<TipoDado, TipoChave>::ArvoreAVL() : raiz(nullptr), tamanho(0) {}

template <typename TipoDado, typename TipoChave>
ArvoreAVL<TipoDado, TipoChave>::~ArvoreAVL() {
    limpar();
}

// --- Implementações Públicas ---

template <typename TipoDado, typename TipoChave>
void ArvoreAVL<TipoDado, TipoChave>::inserir(TipoDado dado, TipoChave chave) {
    raiz = inserirRecursivo(raiz, dado, chave);
}

template <typename TipoDado, typename TipoChave>
void ArvoreAVL<TipoDado, TipoChave>::remover(TipoChave chave) {
    raiz = removerRecursivo(raiz, chave);
}

template <typename TipoDado, typename TipoChave>
TipoDado ArvoreAVL<TipoDado, TipoChave>::buscar(TipoChave chave) {
    NodeAVL<TipoDado, TipoChave>* resultado = buscarRecursivo(raiz, chave);
    if (resultado != nullptr) {
        return resultado->dado;
    }
    // Retorna um valor padrão (nullptr para ponteiros) se não encontrar.
    return TipoDado(); 
}

template <typename TipoDado, typename TipoChave>
int ArvoreAVL<TipoDado, TipoChave>::getTamanho() const {
    return tamanho;
}

template <typename TipoDado, typename TipoChave>
bool ArvoreAVL<TipoDado, TipoChave>::estaVazia() const {
    return raiz == nullptr;
}

template <typename TipoDado, typename TipoChave>
int ArvoreAVL<TipoDado, TipoChave>::getAltura() const{
    if (raiz == nullptr) return 0;
    return raiz->altura;
};

template <typename TipoDado, typename TipoChave>
void ArvoreAVL<TipoDado, TipoChave>::limpar() {
    limparRecursivo(raiz);
    raiz = nullptr;
    tamanho = 0;
}


// --- Métodos Auxiliares Privados ---

template <typename TipoDado, typename TipoChave>
int ArvoreAVL<TipoDado, TipoChave>::getAlturaNode(NodeAVL<TipoDado, TipoChave>* no) const {
    if (no == nullptr) return 0;
    return no->altura;
}

template <typename TipoDado, typename TipoChave>
void ArvoreAVL<TipoDado, TipoChave>::atualizarAltura(NodeAVL<TipoDado, TipoChave>* no) {
    if (no != nullptr) {
        no->altura = 1 + Utils::getMax(getAlturaNode(no->esquerda), getAlturaNode(no->direita));
    }
}

template <typename TipoDado, typename TipoChave>
int ArvoreAVL<TipoDado, TipoChave>::getFatorBalanceamento(NodeAVL<TipoDado, TipoChave>* no) {
    if (no == nullptr) return 0;
    return getAlturaNode(no->esquerda) - getAlturaNode(no->direita);
}

template <typename TipoDado, typename TipoChave>
NodeAVL<TipoDado, TipoChave>* ArvoreAVL<TipoDado, TipoChave>::rotacionarDireita(NodeAVL<TipoDado, TipoChave>* y) {
    NodeAVL<TipoDado, TipoChave>* x = y->esquerda;
    NodeAVL<TipoDado, TipoChave>* T2 = x->direita;

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza alturas
    atualizarAltura(y);
    atualizarAltura(x);

    return x; // Nova raiz da sub-árvore
}

template <typename TipoDado, typename TipoChave>
NodeAVL<TipoDado, TipoChave>* ArvoreAVL<TipoDado, TipoChave>::rotacionarEsquerda(NodeAVL<TipoDado, TipoChave>* x) {
    NodeAVL<TipoDado, TipoChave>* y = x->direita;
    NodeAVL<TipoDado, TipoChave>* T2 = y->esquerda;

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza alturas
    atualizarAltura(x);
    atualizarAltura(y);

    return y; // Nova raiz da sub-árvore
}

template <typename TipoDado, typename TipoChave>
NodeAVL<TipoDado, TipoChave>* ArvoreAVL<TipoDado, TipoChave>::inserirRecursivo(NodeAVL<TipoDado, TipoChave>* no, TipoDado dado, TipoChave chave) {
    // 1. Inserção padrão de Árvore Binária de Busca
    if (no == nullptr) {
        tamanho++;
        return new NodeAVL<TipoDado, TipoChave>(dado, chave);
    }

    if (chave < no->chave) {
        no->esquerda = inserirRecursivo(no->esquerda, dado, chave);
    } else if (chave > no->chave) {
        no->direita = inserirRecursivo(no->direita, dado, chave);
    } else {
        // Chaves duplicadas não são permitidas, apenas retorna o nó.
        // Ou você pode atualizar o dado: no->dado = dado;
        return no;
    }

    // 2. Atualiza a altura do nó ancestral
    atualizarAltura(no);

    // 3. Obtém o fator de balanceamento para verificar se o nó ficou desbalanceado
    int fb = getFatorBalanceamento(no);

    // 4. Se desbalanceado, existem 4 casos de rotação

    // Caso Esquerda-Esquerda
    if (fb > 1 && chave < no->esquerda->chave) {
        return rotacionarDireita(no);
    }

    // Caso Direita-Direita
    if (fb < -1 && chave > no->direita->chave) {
        return rotacionarEsquerda(no);
    }

    // Caso Esquerda-Direita
    if (fb > 1 && chave > no->esquerda->chave) {
        no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }

    // Caso Direita-Esquerda
    if (fb < -1 && chave < no->direita->chave) {
        no->direita = rotacionarDireita(no->direita);
        return rotacionarEsquerda(no);
    }

    // Retorna o ponteiro do nó (sem alterações se já estava balanceado)
    return no;
}


template <typename TipoDado, typename TipoChave>
NodeAVL<TipoDado, TipoChave>* ArvoreAVL<TipoDado, TipoChave>::encontrarMinimo(NodeAVL<TipoDado, TipoChave>* no) {
    NodeAVL<TipoDado, TipoChave>* atual = no;
    while (atual->esquerda != nullptr) {
        atual = atual->esquerda;
    }
    return atual;
}

template <typename TipoDado, typename TipoChave>
NodeAVL<TipoDado, TipoChave>* ArvoreAVL<TipoDado, TipoChave>::removerRecursivo(NodeAVL<TipoDado, TipoChave>* no, TipoChave chave) {
    // 1. Remoção padrão de Árvore Binária de Busca
    if (no == nullptr) return no;

    if (chave < no->chave) {
        no->esquerda = removerRecursivo(no->esquerda, chave);
    } else if (chave > no->chave) {
        no->direita = removerRecursivo(no->direita, chave);
    } else {
        // Nó a ser removido encontrado
        tamanho--;
        if (no->esquerda == nullptr || no->direita == nullptr) {
            NodeAVL<TipoDado, TipoChave>* temp = no->esquerda ? no->esquerda : no->direita;
            if (temp == nullptr) { // Sem filhos
                temp = no;
                no = nullptr;
            } else { // Um filho
                *no = *temp; // Copia o conteúdo
            }
            delete temp;
        } else {
            // Nó com dois filhos: pega o sucessor em ordem (menor da sub-árvore direita)
            NodeAVL<TipoDado, TipoChave>* temp = encontrarMinimo(no->direita);
            no->chave = temp->chave;
            no->dado = temp->dado;
            no->direita = removerRecursivo(no->direita, temp->chave);
        }
    }

    if (no == nullptr) return no; // Se a árvore ficou vazia

    // 2. Atualiza altura e balanceia (mesma lógica da inserção)
    atualizarAltura(no);
    int fb = getFatorBalanceamento(no);

    // Caso Esquerda-Esquerda
    if (fb > 1 && getFatorBalanceamento(no->esquerda) >= 0) {
        return rotacionarDireita(no);
    }

    // Caso Esquerda-Direita
    if (fb > 1 && getFatorBalanceamento(no->esquerda) < 0) {
        no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }

    // Caso Direita-Direita
    if (fb < -1 && getFatorBalanceamento(no->direita) <= 0) {
        return rotacionarEsquerda(no);
    }

    // Caso Direita-Esquerda
    if (fb < -1 && getFatorBalanceamento(no->direita) > 0) {
        no->direita = rotacionarDireita(no->direita);
        return rotacionarEsquerda(no);
    }

    return no;
}


template <typename TipoDado, typename TipoChave>
NodeAVL<TipoDado, TipoChave>* ArvoreAVL<TipoDado, TipoChave>::buscarRecursivo(NodeAVL<TipoDado, TipoChave>* no, TipoChave chave) {
    if (no == nullptr || no->chave == chave) {
        return no;
    }

    if (chave < no->chave) {
        return buscarRecursivo(no->esquerda, chave);
    }
    
    return buscarRecursivo(no->direita, chave);
}

template <typename TipoDado, typename TipoChave>
void ArvoreAVL<TipoDado, TipoChave>::limparRecursivo(NodeAVL<TipoDado, TipoChave>* no) {
    if (no != nullptr) {
        limparRecursivo(no->esquerda);
        limparRecursivo(no->direita);
        delete no;
    }
}

template class ArvoreAVL<Pacote*, int>;
template class ArvoreAVL<Evento*, int>;
template class ArvoreAVL<Cliente*, std::string>;
