#include "stats.hpp"
#include <iostream>

Stats::Stats(){
    cmp = 0;
    move = 0;
    calls = 0;
};

Stats::~Stats(){};

void Stats::resetCounter(){
    cmp = 0;
    move = 0;
    calls = 0;
};

void Stats::incCmp(int num){
    cmp += num;
};
void Stats::incMove(int num){
    move += num;
};
void Stats::incCalls(int num){
    calls += num;
};

void Stats::printStats(){
    std::cout << "cmp " << cmp;
    std::cout << "move " << move;
    std::cout << "calls " << calls;
    std::cout << std::endl;
};
