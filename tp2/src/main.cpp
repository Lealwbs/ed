#include "../include/test.hpp"

int main(int argc, char* argv) {

    // "ENTRADA:"
    // • Data hora da postagem
    // • Nome Remetente
    // • Nome Destinatário
    // • Tipo
    // • Armazém de origem
    // • Armazém de destino

    // "SAÍDA:"
    // • Tempo esperado de estadia
    // • Tempo armazenado
    // • Tempo em trânsito

    // rede/grafo (armazens)

    // rota(id armazens, )

    // armazem
    //     setor* Head_vetor
    //     info

    // setor
    //     pilha_pacote Head_vetor
    //     setor* NEXT 

    // pilha_pacote
    //     pacotes Head_vetor
    //     pilha_pacote* NEXT 

    // pacote
    //     INFO
    //     DESTINATION
    //     pacote* NEXT


    Test* pTest = new Test();
    pTest->Print();
    return 0;
}