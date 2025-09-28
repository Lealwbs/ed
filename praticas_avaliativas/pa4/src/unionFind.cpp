#include "../include/unionFind.hpp"

UnionFind::UnionFind(int quantidade_subconjuntos){
    subconjuntos = new Subconjunto[quantidade_subconjuntos];
    tamanho = quantidade_subconjuntos;
};
UnionFind::~UnionFind(){
    delete[] subconjuntos;
};

void UnionFind::Make(int x){
    subconjuntos[x].representante = x;
};

int UnionFind::Find(int x){
    return subconjuntos[x].rank;
};

void UnionFind::Union(int x, int y){};
