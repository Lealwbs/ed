#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include "../include/stats.hpp"

class SortingAlgorithms{
    public:
        static void swap(int *a, int *b, Stats *stats);
        static int medianOf3Integers(int a, int b, int c);

        static void partition3(int array[], int left, int right, int *start, int *end, Stats *stats);
        static void insertionSort(int array[], int left, int right, Stats *stats);
        static void quickSort3Ins(int array[], int left, int right, Stats *stats);
};

#endif
