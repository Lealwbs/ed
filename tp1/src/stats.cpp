#include "../include/stats.hpp"
#include <iostream>
#include <iomanip>
#include <math.h>

Stats::Stats(){
    Stats(1, 1, 1);
};

Stats::Stats(double a, double b, double c){
    this->a = a;
    this->b = b;
    this->c = c;

    cost = 0;
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

void Stats::calculateCost(){
    cost = fabs(a*cmp + b*move + c*calls);
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
    calculateCost();
    std::cout << "cost " << std::fixed << std::setprecision(9) << cost << " ";
    std::cout << "cmp " << cmp << " ";
    std::cout << "move " << move << " ";
    std::cout << "calls " << calls << " ";
    std::cout << std::endl;
};

void Stats::printAtributes(){
    std::cout << "a " << a << " ";
    std::cout << "b " << b << " ";
    std::cout << "c " << c << " ";
    std::cout << std::endl;
};

void Stats::setAtributes(double a, double b, double c){
    this->a = a;
    this->b = b;
    this->c = c;
};