#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include "../include/stats.hpp"

class SortingAlgorithms{
    private:
        static int medianOf3Integers(int a, int b, int c);
        static void partition3(int array[], int left, int right, int *start, int *end, Stats *stats);
        static void _insertionSort(int array[], int left, int right, Stats *stats);
        static void _quickSort3Ins(int array[], int left, int right, Stats *stats);
    
    public:
        static void swap(int *a, int *b, Stats *stats);
        static void InsertionSort(int array[], int tam, Stats *stats);
        static void QuickSort(int array[], int tam, Stats *stats);
};

#endif
