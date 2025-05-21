#ifndef STATS_HPP
#define STATS_HPP

#include <string>

class Stats{
    public:
        Stats();
        ~Stats();

        void resetCounter();
        void incCmp(int num);
        void incMove(int num);
        void incCalls(int num);
        void printStats();

    private:
        int cmp;
        int move;
        int calls;
};

#endif 