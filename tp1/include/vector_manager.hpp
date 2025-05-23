#ifndef VECTOR_MANAGER_HPP
#define VECTOR_MANAGER_HPP

class vectorManager{
    public:
        static void initSeed(int seed);
        static void initVector(int array[], int size);
        static void printVector(int array[], int size);
        static void shuffleVector(int array[], int size, int numShuffle);
        static void copyVector(int source[], int destination[], int size);
};

#endif