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
    minTamParticao = 0;
};

Stats::~Stats(){};

void Stats::resetCounter(){
    cost = 0; 
    cmp = 0;
    move = 0;
    calls = 0;
    minTamParticao = 0;
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
    std::cout << "calls " << calls;
    std::cout << std::endl;
};

void Stats::printStats_LimPart(){
    calculateCost();
    std::cout << "mps " << minTamParticao << " ";
    std::cout << "cost " << std::fixed << std::setprecision(9) << cost << " ";
    std::cout << "cmp " << cmp << " ";
    std::cout << "move " << move << " ";
    std::cout << "calls " << calls;
    std::cout << std::endl;
};

void Stats::printStats_LimQuebras(int i){
    if(i == 1) std::cout << "qs ";
    if(i == 2) std::cout << "in ";

    std::cout << "lq " << numQuebras << " ";

    calculateCost();
    std::cout << "cost " << std::fixed << std::setprecision(9) << cost << " ";
    std::cout << "cmp " << cmp << " ";
    std::cout << "move " << move << " ";
    std::cout << "calls " << calls;
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

double Stats::getCost(){
    calculateCost();
    return cost;
};

int Stats::getCmp(){
    return cmp;
};

int Stats::getMove(){
    return move;
};

int Stats::getCalls(){
    return calls;
};

int Stats::getMinTamParticao(){
    return minTamParticao;
};

void Stats::setMinTamParticao(int num){
    minTamParticao = num;
};

int Stats::getNumQuebras(){
    return numQuebras;
};

void Stats::setNumQuebras(int num){
    numQuebras = num;
};