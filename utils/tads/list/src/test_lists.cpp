#include "../include/array_list.hpp"
#include "../include/linked_list.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

// #include "../include/array_list.hpp"
// #include "../include/linked_list.hpp"
// #include <iostream>

// void test_array_list() {
//     ListaArranjo vetor = ListaArranjo();

//     vetor.InsereInicio(5);
//     vetor.InsereInicio(4);
//     vetor.InsereInicio(3);
//     vetor.InsereInicio(2);
//     vetor.InsereInicio(1);

//     vetor.InsereFinal(6);
//     vetor.InsereFinal(7);
//     vetor.InsereFinal(8);
//     vetor.InsereFinal(9);
//     vetor.InsereFinal(0);

//     vetor.Imprime();

//     vetor.InserePosicao(100, 7);

//     vetor.Imprime();

//     vetor.SetItem(50, 0);

//     vetor.Imprime();

//     std::cout << vetor.GetItem(7) << std::endl;

//     std::cout << vetor.Pesquisa(100) << std::endl;

//     std::cout << "#####" << std::endl << std::endl;

//     std::cout << "Tamanho: " << vetor.GetTamanho() << std::endl;
//     vetor.Imprime();

//     std::cout << vetor.RemovePosicao(7) << std::endl;
//     std::cout << "Tamanho: " << vetor.GetTamanho() << std::endl;
//     vetor.Imprime();

//     std::cout << vetor.RemovePosicao(0) << std::endl;
//     std::cout << "Tamanho: " << vetor.GetTamanho() << std::endl;
//     vetor.Imprime();

//     vetor.RemoveFinal();
//     vetor.RemoveFinal();
//     vetor.RemoveInicio();
//     vetor.Imprime();

//     vetor.Limpa();

//     std::cout << "#####" << std::endl << std::endl;

//     for (int i = 0; i < 100; i++) {
//         vetor.InsereFinal(i);
//     };

//     vetor.Imprime();

//     std::cout << vetor.RemovePosicao(99) << std::endl << std::endl;

//     vetor.Imprime();
// };

// void test_linked_list(){
//     ListaEncadeada vetor = ListaEncadeada();

    
//     vetor.InsereFinal(50);
    
//     vetor.InsereInicio(5);
//     vetor.InsereInicio(4);
//     vetor.InsereInicio(3);
//     vetor.InsereInicio(2);
//     vetor.InsereInicio(1);

//     vetor.InsereFinal(6);
//     vetor.InsereFinal(7);
//     vetor.InsereFinal(8);
//     vetor.InsereFinal(9);
//     vetor.InsereFinal(0);

//     vetor.Imprime();

//     vetor.InserePosicao(100, 7);

//     vetor.Imprime();

//     vetor.SetItem(40, 1);

//     vetor.Imprime();

//     std::cout << "Get Item 7: " << vetor.GetItem(7) << std::endl;

//     std::cout <<  "Pesquisa 0: " << vetor.Pesquisa(0) << std::endl;

//     std::cout << "#####" << std::endl << std::endl;

//     std::cout << "Tamanho: " << vetor.GetTamanho() << std::endl;
//     vetor.Imprime();

//     std::cout << "Remover Pos 7: " << vetor.RemovePosicao(7) << std::endl;
//     std::cout << "Tamanho: " << vetor.GetTamanho() << std::endl;
//     vetor.Imprime();

//     std::cout << "Remover Pos 1: " << vetor.RemovePosicao(1) << std::endl;
//     std::cout << "Tamanho: " << vetor.GetTamanho() << std::endl;
//     vetor.Imprime();

//     // std::cout << 1+true << std::endl;

//     // vetor.Imprime();

//     vetor.RemoveFinal();
//     vetor.RemoveFinal();
//     vetor.RemoveInicio();
//     vetor.Imprime();
//     std::cout << "Tamanho: " << vetor.GetTamanho() << std::endl;
    
//     vetor.Limpa();
//     std::cout << "Tamanho: " << vetor.GetTamanho() << std::endl;

//     std::cout << "#####" << std::endl << std::endl;

//     for (int i = 0; i < 100; i++) {
//         vetor.InsereFinal(i);
//     };

//     vetor.Imprime();

//     std::cout << vetor.RemovePosicao(100) << std::endl << std::endl;

//     vetor.Imprime();

// };

// int main() {

//     test_array_list();
//     test_linked_list();

//     return 0;
// };


void testa_lista(Lista* lista, string tipo) {
    cout << "======= Testando " << tipo << " =======" << endl;

    // Inserções
    cout << "[Insercoes] Inserindo no inicio e fim..." << endl;
    for (int i = 1; i <= 5; ++i)
        lista->InsereInicio(i); // 5 4 3 2 1
    for (int i = 6; i <= 10; ++i)
        lista->InsereFinal(i);  // 5 4 3 2 1 6 7 8 9 10
    lista->Imprime();
    cout << "Saida esperada: 5 4 3 2 1 6 7 8 9 10" << endl;

    // Inserção no meio
    cout << "[Insercao em posicao] Inserindo 100 na posicao 5..." << endl;
    lista->InserePosicao(100, 5);
    lista->Imprime();
    cout << "Saida esperada: 5 4 3 2 1 100 6 7 8 9 10" << endl;

    // GetItem
    cout << "[GetItem] Item na posicao 5: " << lista->GetItem(5) << endl;
    cout << "Saida esperada: 100" << endl;

    // SetItem
    cout << "[SetItem] Mudando valor da posicao 1 para 999..." << endl;
    lista->SetItem(999, 1);
    lista->Imprime();
    cout << "Saida esperada: 5 999 3 2 1 100 6 7 8 9 10" << endl;

    // Pesquisa
    cout << "[Pesquisa] Procurando valor 100..." << endl;
    int pos = lista->Pesquisa(100);
    if (pos != -1)
        cout << "Valor encontrado na posicao: " << pos << endl;
    else
        cout << "Valor nao encontrado." << endl;
    cout << "Saida esperada: 5" << endl;

    // Remoções
    cout << "[Remocoes] Removendo da posicao 5..." << endl;
    cout << "Removido: " << lista->RemovePosicao(5) << endl;
    lista->Imprime();
    cout << "Saida esperada: 5 999 3 2 1 6 7 8 9 10" << endl;

    cout << "Removendo do inicio: " << lista->RemoveInicio() << endl;
    cout << "Removendo do final: " << lista->RemoveFinal() << endl;
    lista->Imprime();
    cout << "Saida esperada: 999 3 2 1 6 7 8 9" << endl;

    // Limpeza
    cout << "[Limpeza] Limpando a lista..." << endl;
    lista->Limpa();
    cout << "Tamanho apos limpar: " << lista->GetTamanho() << endl;
    cout << "Saida esperada: 0" << endl;

    // Erros
    cout << "[Erro] Tentando remover inicio em lista vazia..." << endl;
    try {
        lista->RemoveInicio();
    } catch (const char* msg) {
        cout << msg << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    cout << "Saida esperada: ERRO: Lista vazia!" << endl;

    cout << "[Erro] Inserindo em posicao invalida..." << endl;
    try {
        lista->InserePosicao(777, -1);
    } catch (const char* msg) {
        cout << msg << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    cout << "Saida esperada: ERRO: Posicao Invalida OU Tamanho maximo atingido!" << endl;

    // Preenchimento total
    cout << "[Preenchimento total] Inserindo 100 elementos..." << endl;
    try {
        for (int i = 0; i < 100; i++) {
            lista->InsereFinal(i);
        }
        lista->Imprime();
        cout << "Saida esperada: 0 1 2 ... 99" << endl;
    } catch (const char* msg) {
        cout << msg << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    cout << "Tamanho final: " << lista->GetTamanho() << endl;
    cout << "Saida esperada: 100" << endl;

    cout << "Removendo ultimo elemento: " << lista->RemovePosicao(lista->GetTamanho() - 1) << endl;
    lista->Imprime();
    cout << "Saida esperada: 0 1 2 ... 98" << endl;

    cout << "======= Fim do teste para " << tipo << " =======" << endl << endl;
}

int main() {
    ListaArranjo arranjo;
    ListaEncadeada encadeada;

    testa_lista(&arranjo, "ListaArranjo (Array)");
    testa_lista(&encadeada, "ListaEncadeada (Linked List)");

    return 0;
}
