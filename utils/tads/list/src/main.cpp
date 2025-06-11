#include "../include/array_list.hpp"
#include "../include/linked_list.hpp"
#include <iostream>

void test_array_list() {
    ListaArranjo vetor = ListaArranjo();

    vetor.InsereInicio(5);
    vetor.InsereInicio(4);
    vetor.InsereInicio(3);
    vetor.InsereInicio(2);
    vetor.InsereInicio(1);

    vetor.InsereFinal(6);
    vetor.InsereFinal(7);
    vetor.InsereFinal(8);
    vetor.InsereFinal(9);
    vetor.InsereFinal(0);

    vetor.Imprime();

    vetor.InserePosicao(100, 7);

    vetor.Imprime();

    vetor.SetItem(50, 0);

    vetor.Imprime();

    std::cout << vetor.GetItem(7) << std::endl;

    std::cout << vetor.Pesquisa(100) << std::endl;

    std::cout << "#####" << std::endl << std::endl;

    std::cout << "Tamanho: " << vetor.GetTamanho() << std::endl;
    vetor.Imprime();

    std::cout << vetor.RemovePosicao(7) << std::endl;
    std::cout << "Tamanho: " << vetor.GetTamanho() << std::endl;
    vetor.Imprime();

    std::cout << vetor.RemovePosicao(0) << std::endl;
    std::cout << "Tamanho: " << vetor.GetTamanho() << std::endl;
    vetor.Imprime();

    vetor.RemoveFinal();
    vetor.RemoveFinal();
    vetor.RemoveInicio();
    vetor.Imprime();

    vetor.Limpa();

    std::cout << "#####" << std::endl << std::endl;

    for (int i = 0; i < 100; i++) {
        vetor.InsereFinal(i);
    };

    vetor.Imprime();

    std::cout << vetor.RemovePosicao(99) << std::endl << std::endl;

    vetor.Imprime();
};

void test_linked_list(){
    ListaEncadeada vetor = ListaEncadeada();
};

int main() {

    // test_array_list();
    test_linked_list();

    return 0;
};
