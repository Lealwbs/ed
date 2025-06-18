#include "../include/grafo_rede.hpp"
#include <iostream> // Adicionado para usar std::cout

// Construtor: aloca vetor de ponteiros para listas de adjacência
GrafoRede::GrafoRede(int numero_armazens) : numero_armazens(numero_armazens) {
    matriz_adjacencia = new Lista*[numero_armazens];
    for (int i = 0; i < numero_armazens; ++i) {
        matriz_adjacencia[i] = new Lista();
    }
}

// Destrutor: desaloca listas e vetor
GrafoRede::~GrafoRede() {
    for (int i = 0; i < numero_armazens; ++i) {
        delete matriz_adjacencia[i];
    }
    delete[] matriz_adjacencia;
}

// Retorna o número total de armazéns
int GrafoRede::GetNumeroArmazens() {
    return numero_armazens;
}

// Adiciona aresta (ligação) entre dois armazéns
void GrafoRede::AdicionarAresta(int armazem_1, int armazem_2) {
    if (armazem_1 >= 0 && armazem_1 < numero_armazens && armazem_2 >= 0 && armazem_2 < numero_armazens) {
        matriz_adjacencia[armazem_1]->AdicionarInt(armazem_2);
    }
}

// Retorna lista de vizinhos (conexões) de um armazém
Lista* GrafoRede::GetVizinhos(int v) {
    if (v < 0 || v >= numero_armazens) return nullptr;
    return matriz_adjacencia[v];
}

// Imprime a rede de armazens
void GrafoRede::Print() {
    std::cout << "=== Rede de Armazéns ===" << std::endl;
    for (int i = 0; i < numero_armazens; ++i) {
        std::cout << "Armazém " << i << ": ";
        matriz_adjacencia[i]->Imprimir();
    }
    std::cout << "========================" << std::endl;
}

// Busca em largura BFS para encontrar a rota com menos saltos entre dois armazéns
Lista* GrafoRede::GetRota(GrafoRede& rede, int armazem_origem, int armazem_destino) {

    int n = rede.GetNumeroArmazens();
    Lista* rota = new Lista();

    if (armazem_origem == armazem_destino) {
        rota->AdicionarInt(armazem_origem);
        return rota;
    }

    bool* visitado = new bool[n]{};
    int* anterior = new int[n];

    for (int i = 0; i < n; ++i) {
        anterior[i] = -1;
    }

    Fila fila;
    fila.Enfileirar(armazem_origem);
    visitado[armazem_origem] = true;

    bool encontrou = false;

    while (!fila.Vazia() && !encontrou) {
        int atual = fila.Desenfileirar();

        Lista* vizinhos = rede.GetVizinhos(atual);
        if (vizinhos == nullptr) continue; // Adicionado para segurança

        NodeLista* viz = vizinhos->GetHead();
        while (viz != nullptr) {
            if (viz->tipo == tipo_inteiro) {
                int idVizinho = viz->valor;

                if (!visitado[idVizinho]) {
                    visitado[idVizinho] = true;
                    anterior[idVizinho] = atual;
                    fila.Enfileirar(idVizinho);

                    if (idVizinho == armazem_destino) {
                        encontrou = true;
                        break;
                    }
                }
            }
            viz = viz->proximo;
        }
    }

    // Reconstruir a rota se o destino foi alcançado
    if (visitado[armazem_destino]) {
        // 'rota' já foi criada no início da função.
        // Vamos preenchê-la na ordem correta.
        for (int atual = armazem_destino; atual != -1; atual = anterior[atual]) {
            // Adiciona cada passo no INÍCIO da lista para inverter a ordem naturalmente.
            rota->AdicionarNoInicio(atual);
        }
    }

    // Libera a memória e retorna a rota (correta ou vazia se não houver caminho).
    delete[] visitado;
    delete[] anterior;
    return rota;
}