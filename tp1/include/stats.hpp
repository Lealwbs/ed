#ifndef STATS_HPP
#define STATS_HPP

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
        void printStats_LimPart();
        void printStats_LimQuebras();
        
        void printAtributes();
        void setAtributes(double a, double b, double c);
        
        double getCost();
        int getCmp();
        int getMove();
        int getCalls();
        int getMinTamParticao();
        void setMinTamParticao(int num);

    private:
        double a;
        double b;
        double c;
        double cost;
        
        int cmp;
        int move;
        int calls;

        int minTamParticao;
};

#endif 