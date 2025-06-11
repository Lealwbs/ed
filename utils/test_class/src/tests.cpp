#include <iostream>
#include <string>

int soma(int a, int b) {
    return a + b;
}

void checar(const std::string& nome, bool condicao) {
    if (condicao) {
        std::cout << "[OK] " << nome << "\n";
    } else {
        std::cout << "[FAIL] " << nome << "\n";
    }
}

int main() {
    checar("Soma de 2 + 3 == 5", soma(2, 3) == 5);
    checar("Soma de -1 + -1 == -2", soma(-1, -1) == -2);
    checar("Soma de 0 + 0 == 0", soma(0, 0) == 0);
    checar("Soma de 10 + -5 == 5", soma(10, -5) == 5);

    std::cout << "Testes finalizados.\n";
    return 0;
}