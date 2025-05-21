
#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include "../include/stats.hpp"

class SortingAlgorithms{
    public:
    
        static void swap(int *xp, int *yp, Stats *s);  
        static int medianOf3Integers(int a, int b, int c);

        static void insertionSort(int vetor[], int ini, int fim, Stats * stats);
        static void quickSort_partition3(int vetor[], int l, int r);



    // static void _insertionSort(int V[], int l, int r);
    // static void partition3(int V[], int l, int r, int *i, int *j);
    // static int median(int a, int b, int c);
    // static void SetTamParticao(int tam);
};
#endif
