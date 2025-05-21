#include "sorting_algorithms.hpp" 
#include "stats.hpp"

#define QUICK_SORT_SIZE 50

void SortingAlgorithms::swap(int *x, int *y, Stats* stats){
    int temp = *x;
    *x = *y;
    *y = temp;
    stats->incMove(3);
};

int SortingAlgorithms::medianOf3Integers (int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;  // a b c
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    return b;                            // c b a
};

void SortingAlgorithms::insertionSort(int vetor[], int ini, int fim, Stats * stats) {
    int k, m;
    int valor;
    stats->incCalls(1);
    for (k = ini + 1; k <= fim; k++) {
        stats->incCmp(1);
        valor = vetor[k];
        stats->incMove(1);
        m = k - 1;
        while ((m >= 0) && (valor < vetor[m])) {
            stats->incCmp(1);
            vetor[m + 1] = vetor[m];
            stats->incMove(1);
            m--;
        };
        vetor[m + 1] = valor;
        stats->incMove(1);
    };
};


// void quickSort_partition3(int* array, int left, int right, int* start, int* end, Stats* stats) {
//     int pivot;
//     stats->incCalls(1);
//     *start = left;
//     *end = right;
//     pivot = medianOf3Integers(array[left], array[(*start + *end) / 2], array[right]);

//     do {
//         while (pivot > array[*start]) {
//             (*start)++;
//             stats->incCmp(1);
//         };
//         stats->incCmp(1);

//         while (pivot < array[*end]) {
//             (*end)--;
//             stats->incCmp(1);
//         };
//         stats->incCmp(1);

//         if (*start <= *end) {
//             swap(&array[*start], &array[*end], stats);
//             (*start)++;
//             (*end)--;
//         };
//     } while (*start <= *end);
// };