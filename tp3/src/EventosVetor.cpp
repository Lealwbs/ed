#include "../include/EventosVetor.hpp"

EventosVetor::EventosVetor() {
    primeiro = new Node;
    primeiro->evento = nullptr; // Nó cabeça sem evento
    primeiro->prox = nullptr;
    ultimo = primeiro;
    tamanho = 0;
};

EventosVetor::~EventosVetor() {
    Limpa();
    delete primeiro;
};

int EventosVetor::GetTamanho() const {
    return tamanho;
};

Evento* EventosVetor::GetItem(int pos) {
    if (pos <= 0 || pos > tamanho)
        throw std::runtime_error("ERRO: Posicao invalida!");

    Node* aux = Posiciona(pos);
    return aux->evento;
};

void EventosVetor::SetItem(Evento evento, int pos) {
    if (pos <= 0 || pos > tamanho)
        throw std::runtime_error("ERRO: Posicao invalida!");

    Node* aux = Posiciona(pos);
    if (aux->evento != nullptr) {
        delete aux->evento;
    }
    aux->evento = new Evento(evento);
};

void EventosVetor::InsereInicio(Evento evento) {
    Node* novo = new Node;
    novo->evento = new Evento(evento);
    novo->prox = primeiro->prox;
    primeiro->prox = novo;

    if (novo->prox == nullptr)
        ultimo = novo;

    tamanho++;
};

void EventosVetor::InsereFinal(Evento evento) {
    Node* novo = new Node;
    novo->evento = new Evento(evento);
    novo->prox = nullptr;

    ultimo->prox = novo;
    ultimo = novo;

    tamanho++;
};

void EventosVetor::InserePosicao(Evento evento, int pos) {
    if (pos <= 0 || pos > tamanho + 1)
        throw std::runtime_error("ERRO: Posicao invalida!");

    Node* antes = Posiciona(pos, true);

    Node* novo = new Node;
    novo->evento = new Evento(evento);

    novo->prox = antes->prox;
    antes->prox = novo;

    if (novo->prox == nullptr)
        ultimo = novo;

    tamanho++;
};

Evento* EventosVetor::RemoveInicio() {
    if (tamanho == 0)
        throw std::runtime_error("ERRO: Lista vazia!");

    Node* remover = primeiro->prox;
    primeiro->prox = remover->prox;

    Evento* aux = remover->evento;
    remover->evento = nullptr; // Evita deletar o evento aqui

    if (primeiro->prox == nullptr)
        ultimo = primeiro;

    delete remover;
    tamanho--;
    return aux;
};

Evento* EventosVetor::RemoveFinal() {
    if (tamanho == 0)
        throw std::runtime_error("ERRO: Lista vazia!");

    Evento* aux = ultimo->evento;
    ultimo->evento = nullptr; // Evita deletar o evento aqui

    Node* penultimo = Posiciona(tamanho, true);
    penultimo->prox = nullptr;

    delete ultimo;
    ultimo = penultimo;

    tamanho--;
    return aux;
};

Evento* EventosVetor::RemovePosicao(int pos) {
    if (pos <= 0 || pos > tamanho)
        throw std::runtime_error("ERRO: Posicao invalida ou Lista Vazia!");

    Node* antes = Posiciona(pos, true);
    Node* remover = antes->prox;
    antes->prox = remover->prox;

    Evento* aux = remover->evento;
    remover->evento = nullptr; // Evita deletar o evento aqui

    if (antes->prox == nullptr)
        ultimo = antes;

    delete remover;
    tamanho--;
    return aux;
};

Evento* EventosVetor::Pesquisa(int idPacote) {
    if (tamanho == 0)
        throw std::runtime_error("ERRO: Lista vazia!");

    Node* aux = primeiro->prox;
    for (int i = 1; i <= tamanho; i++) {
        if (aux->evento != nullptr && aux->evento->getIdPacote() == idPacote)
            return aux->evento;
        aux = aux->prox;
    };
    
    return nullptr; // Retorna nullptr se não encontrar
};

void EventosVetor::Imprime() {
    Node* aux = primeiro->prox;
    for (int i = 0; i < tamanho; i++) {
        if (aux->evento != nullptr) {
            std::cout << aux->evento->getInfo() << std::endl;
        }
        aux = aux->prox;
    };
};

void EventosVetor::Limpa() {
    if (tamanho == 0)
        return;

    Node* remover = primeiro->prox;
    while(tamanho){
        primeiro->prox = remover->prox;
        if (remover->evento != nullptr) {
            delete remover->evento;
        }
        delete remover;
        remover = primeiro->prox;
        tamanho--;
    };

    ultimo = primeiro;
};

Node* EventosVetor::Posiciona(int pos, bool antes) {
    if (pos <= 0 || pos > tamanho || tamanho == 0)
        throw std::runtime_error("ERRO: Posicao invalida ou Lista Vazia!");

    Node* aux = primeiro;
    for (int i = 0; i < (pos - 1 + !antes); i++) {
        aux = aux->prox;
    };
    return aux;
};