#ifndef LIST_HPP
#define LIST_HPP

class Lista {
    public:
        Lista() { tamanho = 0; };
        int GetTamanho() { return tamanho; };
        bool Vazia() { return tamanho == 0; };

        virtual int GetItem(int pos) = 0;
        virtual void SetItem(int item, int pos) = 0;
        virtual void InsereInicio(int item) = 0;
        virtual void InsereFinal(int item) = 0;
        virtual void InserePosicao(int item, int pos) = 0;
        virtual int RemoveInicio() = 0;
        virtual int RemoveFinal() = 0;
        virtual int RemovePosicao(int pos) = 0;
        virtual int Pesquisa(int c) = 0;
        virtual void Imprime() = 0;
        virtual void Limpa() = 0;

    protected:
        int tamanho;
};

#endif