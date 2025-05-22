#ifndef STATS_HPP
#define STATS_HPP

#include <string>

class Stats{
    public:
        Stats();
        Stats(double a, double b, double c);
        ~Stats();

        void resetCounter();
        void calculateCost();
        void incCmp(int num);
        void incMove(int num);
        void incCalls(int num);
        void printStats();
        void printAtributes();
        void setAtributes(double a, double b, double c);

    private:
        double a;
        double b;
        double c;
        double cost;
        
        int cmp;
        int move;
        int calls;
};

#endif 