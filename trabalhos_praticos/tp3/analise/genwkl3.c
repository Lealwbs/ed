// Um algoritmo union-find para identificar ilhas (versão compatível com Windows)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Incluído para srand

// Estrutura para um subconjunto no union-find
typedef struct subset {
    int parent;
    int rank;
} subset;

// Função utilitária para encontrar o conjunto de um elemento i (com compressão de caminho)
int Find(subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = Find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Função que une dois conjuntos de x e y (usa união por rank)
void Union(subset subsets[], int x, int y) {
    int xroot = Find(subsets, x);
    int yroot = Find(subsets, y);

    if (xroot == yroot) return;

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Função para gerar um nó aleatório
int rndnode(int nodes) {
    // Usa rand() em vez de drand48()
    return (int)(((double)rand() / (RAND_MAX + 1)) * nodes);
}

// Função para imprimir as instruções de uso
void print_usage(char *prog_name) {
    fprintf(stderr, "Uso: %s [-s seed] [-n nos] [-p pacotes] [-c clientes] [-t tempo] [-v]\n", prog_name);
}

int main(int argc, char *argv[]) {
    // Valores padrão
    long seed = 1;
    int nodes = 10;
    int numpackets = 100;
    int numclients = 10;
    long rtime = 10;
    int verbose = 0;

    // --- Início da análise de argumentos manual (substituição do getopt) ---
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0) {
            if (i + 1 < argc) seed = atol(argv[++i]);
        } else if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 < argc) nodes = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-p") == 0) {
            if (i + 1 < argc) numpackets = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-c") == 0) {
            if (i + 1 < argc) numclients = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc) rtime = atol(argv[++i]);
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else {
            print_usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    // --- Fim da análise de argumentos manual ---

    if (verbose) fprintf(stderr, "[DEBUG] genwkl3_extra iniciado com seed=%ld, nos=%d, pacotes=%d, clientes=%d\n", seed, nodes, numpackets, numclients);

    if (nodes <= 1) {
        fprintf(stderr, "Erro: O numero de nos deve ser maior que 1.\n");
        exit(EXIT_FAILURE);
    }

    long atime = 1;
    int src, dst, sender, receiver;
    long qtime, qtime_end;

    // Usa fopen_s no Windows para mais segurança, mas fopen ainda funciona
    FILE *out = fopen("tp3.in", "wt");
    if (!out) {
        perror("Erro ao abrir tp3.in");
        exit(EXIT_FAILURE);
    }

    // Usa srand() no lugar de srand48()
    srand((unsigned int)seed);

    if (verbose) fprintf(stderr, "[DEBUG] Gerando %d pacotes...\n", numpackets);
    for (int i = 0; i < numpackets; i++) {
        do { src = rndnode(nodes); dst = rndnode(nodes); } while (src == dst);
        // Usa rand() em vez de drand48()
        atime += (long)(((double)rand() / RAND_MAX) * rtime) + 1;

        do { sender = rndnode(numclients); receiver = rndnode(numclients); } while (sender == re
        fprintf(out, "%.7ld EV RG %.3d n%.5d n%.5d %.3d %.3d\n",
                atime, i, sender, receiver, src, dst);
    }

    int numcl = (numclients > 0) ? 10 : 0;
    int numpc = (numpackets > 0) ? 10 : 0;
    int num_ma = 5; // Número de consultas de Movimentação em Armazém
    int num_rc = 5; // Número de consultas de Rotas Congestionadas

    if (verbose) fprintf(stderr, "[DEBUG] Gerando consultas...\n");

    for (int i = 0; i < numcl; i++) {
        qtime = (long)(((double)rand() / RAND_MAX) * atime);
        sender = rndnode(numclients);
        fprintf(out, "%.7ld CL n%.5d\n", qtime, sender);
    }
    
    for (int i = 0; i < numpc; i++) {
        qtime = (long)(((double)rand() / RAND_MAX) * atime);
        sender = rndnode(numpackets);
        fprintf(out, "%.7ld PC %.3d\n", qtime, sender);
    }

    // Gerar consultas MA (Movimentação em Armazém)
    for (int i = 0; i < num_ma; i++) {
        qtime = (long)(((double)rand() / RAND_MAX) * atime);
        qtime_end = qtime + (long)(((double)rand() / RAND_MAX) * (atime - qtime));
        int armazem = rndnode(nodes);
        fprintf(out, "%.7ld MA %.7ld %.7ld %.3d\n", qtime, qtime, qtime_end, armazem);
    }

    // Gerar consultas RC (Rotas Congestionadas)
    for (int i = 0; i < num_rc; i++) {
        qtime = (long)(((double)rand() / RAND_MAX) * atime);
        fprintf(out, "%.7ld RC\n", qtime);
    }

    if (verbose) fprintf(stderr, "[DEBUG] Geracao de dados concluida. Fechando arquivo.\n");
    fclose(out);

    return 0;
}