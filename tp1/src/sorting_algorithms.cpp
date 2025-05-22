#include "../include/sorting_algorithms.hpp" 
#include "../include/stats.hpp"

Stats SortingAlgorithms::stats(1, 1, 1);

void SortingAlgorithms::swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    stats.incMove(3);
};

int SortingAlgorithms::medianOf3Integers(int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;  // a b c
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    return b;                            // c b a
};

void SortingAlgorithms::_insertionSort(int array[], int left, int right) {
    stats.incCalls(1);
    for (int i = left + 1; i <= right; i++) {
        stats.incCmp(1);
        int value = array[i];
        stats.incMove(1);
        int j = i - 1;

        while (j >= left && value < array[j]) {
            stats.incCmp(1);
            array[j + 1] = array[j];
            stats.incMove(1);
            j--;
        }
        array[j + 1] = value;
        stats.incMove(1);
    }
};

void SortingAlgorithms::_quickSort3Ins(int array[], int left, int right, int minTamParticaoQS) {
    stats.incCalls(1);
    int start, end;

    partition3(array, left, right, &start, &end);

    if (left < end) {
        if (end - left <= minTamParticaoQS) {
            _insertionSort(array, left, end);
        } else {
            _quickSort3Ins(array, left, end, minTamParticaoQS);
        }
    }

    if (start < right) {
        if (right - start <= minTamParticaoQS) {
            _insertionSort(array, start, right);
        } else {
            _quickSort3Ins(array, start, right, minTamParticaoQS);
        }
    }
};

void SortingAlgorithms::partition3(int array[], int left, int right, int* start, int* end) {
    stats.incCalls(1);

    *start = left;
    *end = right;

    int pivot = medianOf3Integers(array[left], array[(left + right) / 2], array[right]);

    do {
        while (array[*start] < pivot) {
            (*start)++;
            stats.incCmp(1);
        }
        stats.incCmp(1);

        while (array[*end] > pivot) {
            (*end)--;
            stats.incCmp(1);
        }
        stats.incCmp(1);

        if (*start <= *end) {
            swap(&array[*start], &array[*end]);
            (*start)++;
            (*end)--;
        }
    } while (*start <= *end);
};

void SortingAlgorithms::InsertionSort(int array[], int tam){
    _insertionSort(array, 0, tam - 1);
};

void SortingAlgorithms::QuickSort(int array[], int tam, int minTamParticaoQS){
    _quickSort3Ins(array, 0, tam - 1, minTamParticaoQS);
};