#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct subset {
    int parent;
    int rank;
} subset;

// A utility function to find set of an element i
int Find(subset subsets[], int i) {
    if (subsets[i].parent == i) {
        return i;
    } else {
        return Find(subsets, subsets[i].parent);
    }
}

// A function that does union of two sets of x and y (uses union by rank)
void Union(subset subsets[], int xroot, int yroot) {
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

double drand() {
    return (double)rand() / RAND_MAX;
}

int rndnode(int nodes) {
    return (int)(drand() * nodes);
}

int main() {
    int seed = 1;
    int transportcapacity = 2;
    int transportcost = 20;
    int transportinterval = 100;
    int retrievecost = 1;
    int nodes = 10;
    int numpackets = 100;
    int conncomp = nodes;
    long atime = 1;
    long rtime = 10;
    int src, dst, fsrc, fdst;

    srand(seed);  // Windows-compatible seed

    subset* ss = (subset*)malloc(sizeof(subset) * nodes);
    for (int i = 0; i < nodes; i++) {
        ss[i].parent = i;
        ss[i].rank = 0;
    }

    int* graph = (int*)malloc(sizeof(int) * nodes * nodes);
    for (int i = 0; i < nodes * nodes; i++) graph[i] = 0;

    printf("%d\n%d\n%d\n%d\n", transportcapacity, transportcost,
        transportinterval, retrievecost);

    while (conncomp > 1) {
        do {
            src = rndnode(nodes);
            dst = rndnode(nodes);
        } while (src == dst);
        fsrc = Find(ss, src);
        fdst = Find(ss, dst);
        if (fsrc != fdst) {
            Union(ss, fsrc, fdst);
            conncomp--;
            graph[src * nodes + dst] = 1;
            graph[dst * nodes + src] = 1;
        }
    }

    printf("%d\n", nodes);
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            printf("%d", graph[i * nodes + j]);
            if (j < nodes - 1) {
                printf(" ");
            } else {
                printf("\n");
            }
        }
    }

    printf("%d\n", numpackets);
    for (int i = 0; i < numpackets; i++) {
        do {
            src = rndnode(nodes);
            dst = rndnode(nodes);
        } while (src == dst);
        atime += (long)(drand() * rtime);
        printf("%ld pac %d org %d dst %d\n", atime, i, src, dst);
    }

    free(ss);
    free(graph);

    return numpackets;
}
