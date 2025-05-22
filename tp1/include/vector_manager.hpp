#ifndef VECTOR_MANAGER_HPP
#define VECTOR_MANAGER_HPP

class vectorManager{
    public:
        static void initSeed(int seed);
        static void initVector(int vetor[], int size);
        static void printVector(int vetor[], int size);
        static void shuffleVector(int* vet, int size, int numShuffle);
};

#endif