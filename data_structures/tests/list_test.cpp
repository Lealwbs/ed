#include "assert.hpp"
#include "../list/list.hpp"

int main(){
    
    CPP_UNIT_ASSERT test = CPP_UNIT_ASSERT();

    // ========== TESTES DE INICIALIZAÇÃO ==========
    {
        List a;
        test.assert_equals(a.ToString(), "[]");
        test.assert_equals(a.Size(), 0);
        test.assert_equals(a.Empty(), true);
    }

    // ========== TESTES DE PUSHBACK ==========
    {
        List a;
        
        a.PushBack(10);
        test.assert_equals(a.ToString(), "[10]");
        test.assert_equals(a.Size(), 1);
        test.assert_equals(a.Empty(), false);

        a.PushBack(20);
        test.assert_equals(a.ToString(), "[10, 20]");
        test.assert_equals(a.Size(), 2);

        a.PushBack(30);
        test.assert_equals(a.ToString(), "[10, 20, 30]");
        test.assert_equals(a.Size(), 3);

        a.PushBack(-5);
        test.assert_equals(a.ToString(), "[10, 20, 30, -5]");
        test.assert_equals(a.Size(), 4);

        a.PushBack(0);
        test.assert_equals(a.ToString(), "[10, 20, 30, -5, 0]");
        test.assert_equals(a.Size(), 5);
    }

    // ========== TESTES DE PUSHFRONT ==========
    {
        List a;
        
        a.PushFront(10);
        test.assert_equals(a.ToString(), "[10]");
        test.assert_equals(a.Size(), 1);

        a.PushFront(20);
        test.assert_equals(a.ToString(), "[20, 10]");
        test.assert_equals(a.Size(), 2);

        a.PushFront(30);
        test.assert_equals(a.ToString(), "[30, 20, 10]");
        test.assert_equals(a.Size(), 3);

        a.PushFront(-1);
        test.assert_equals(a.ToString(), "[-1, 30, 20, 10]");
        test.assert_equals(a.Size(), 4);
    }

    // ========== TESTES DE PUSHAT ==========
    {
        List a;
        
        // Inserir no início (posição 0) de lista vazia
        a.PushAt(5, 0);
        test.assert_equals(a.ToString(), "[5]");
        test.assert_equals(a.Size(), 1);

        // Inserir no final (posição 1)
        a.PushAt(10, 1);
        test.assert_equals(a.ToString(), "[5, 10]");
        test.assert_equals(a.Size(), 2);

        // Inserir no meio (posição 1)
        a.PushAt(7, 1);
        test.assert_equals(a.ToString(), "[5, 7, 10]");
        test.assert_equals(a.Size(), 3);

        // Inserir no início (posição 0)
        a.PushAt(1, 0);
        test.assert_equals(a.ToString(), "[1, 5, 7, 10]");
        test.assert_equals(a.Size(), 4);

        // Inserir no final (posição 4)
        a.PushAt(15, 4);
        test.assert_equals(a.ToString(), "[1, 5, 7, 10, 15]");
        test.assert_equals(a.Size(), 5);

        // Inserir em posição intermediária
        a.PushAt(8, 3);
        test.assert_equals(a.ToString(), "[1, 5, 7, 8, 10, 15]");
        test.assert_equals(a.Size(), 6);
    }

    // ========== TESTES DE GET ==========
    {
        List a;
        a.PushBack(100);
        a.PushBack(200);
        a.PushBack(300);
        a.PushBack(400);
        
        test.assert_equals(a.Get(0), 100);
        test.assert_equals(a.Get(1), 200);
        test.assert_equals(a.Get(2), 300);
        test.assert_equals(a.Get(3), 400);
    }

    // ========== TESTES DE SET ==========
    {
        List a;
        a.PushBack(1);
        a.PushBack(2);
        a.PushBack(3);
        
        a.Set(10, 0);
        test.assert_equals(a.ToString(), "[10, 2, 3]");
        
        a.Set(20, 1);
        test.assert_equals(a.ToString(), "[10, 20, 3]");
        
        a.Set(30, 2);
        test.assert_equals(a.ToString(), "[10, 20, 30]");
    }

    // ========== TESTES DE POPFRONT ==========
    {
        List a;
        a.PushBack(1);
        a.PushBack(2);
        a.PushBack(3);
        a.PushBack(4);
        
        test.assert_equals(a.PopFront(), 1);
        test.assert_equals(a.ToString(), "[2, 3, 4]");
        test.assert_equals(a.Size(), 3);
        
        test.assert_equals(a.PopFront(), 2);
        test.assert_equals(a.ToString(), "[3, 4]");
        test.assert_equals(a.Size(), 2);
        
        test.assert_equals(a.PopFront(), 3);
        test.assert_equals(a.ToString(), "[4]");
        test.assert_equals(a.Size(), 1);
        
        test.assert_equals(a.PopFront(), 4);
        test.assert_equals(a.ToString(), "[]");
        test.assert_equals(a.Size(), 0);
        test.assert_equals(a.Empty(), true);
    }

    // ========== TESTES DE POPBACK ==========
    {
        List a;
        a.PushBack(10);
        a.PushBack(20);
        a.PushBack(30);
        a.PushBack(40);
        
        test.assert_equals(a.PopBack(), 40);
        test.assert_equals(a.ToString(), "[10, 20, 30]");
        test.assert_equals(a.Size(), 3);
        
        test.assert_equals(a.PopBack(), 30);
        test.assert_equals(a.ToString(), "[10, 20]");
        test.assert_equals(a.Size(), 2);
        
        test.assert_equals(a.PopBack(), 20);
        test.assert_equals(a.ToString(), "[10]");
        test.assert_equals(a.Size(), 1);
        
        test.assert_equals(a.PopBack(), 10);
        test.assert_equals(a.ToString(), "[]");
        test.assert_equals(a.Size(), 0);
        test.assert_equals(a.Empty(), true);
    }

    // ========== TESTES DE POPAT ==========
    {
        List a;
        a.PushBack(100);
        a.PushBack(200);
        a.PushBack(300);
        a.PushBack(400);
        a.PushBack(500);
        
        // Remove do meio
        test.assert_equals(a.PopAt(2), 300);
        test.assert_equals(a.ToString(), "[100, 200, 400, 500]");
        test.assert_equals(a.Size(), 4);
        
        // Remove do início
        test.assert_equals(a.PopAt(0), 100);
        test.assert_equals(a.ToString(), "[200, 400, 500]");
        test.assert_equals(a.Size(), 3);
        
        // Remove do final
        test.assert_equals(a.PopAt(2), 500);
        test.assert_equals(a.ToString(), "[200, 400]");
        test.assert_equals(a.Size(), 2);
        
        // Remove do meio novamente
        test.assert_equals(a.PopAt(1), 400);
        test.assert_equals(a.ToString(), "[200]");
        test.assert_equals(a.Size(), 1);
        
        // Remove último elemento
        test.assert_equals(a.PopAt(0), 200);
        test.assert_equals(a.ToString(), "[]");
        test.assert_equals(a.Size(), 0);
        test.assert_equals(a.Empty(), true);
    }

    // ========== TESTES DE SEARCH ==========
    {
        List a;
        a.PushBack(5);
        a.PushBack(10);
        a.PushBack(15);
        a.PushBack(20);
        a.PushBack(10); // valor duplicado
        
        test.assert_equals(a.Search(5), 0);
        test.assert_equals(a.Search(10), 1);  // deve retornar primeira ocorrência
        test.assert_equals(a.Search(15), 2);
        test.assert_equals(a.Search(20), 3);
        test.assert_equals(a.Search(99), -1); // não encontrado
        test.assert_equals(a.Search(-1), -1); // não encontrado
    }

    // ========== TESTES DE CLEAR ==========
    {
        List a;
        a.PushBack(1);
        a.PushBack(2);
        a.PushBack(3);
        
        test.assert_equals(a.Size(), 3);
        test.assert_equals(a.Empty(), false);
        
        a.Clear();
        test.assert_equals(a.ToString(), "[]");
        test.assert_equals(a.Size(), 0);
        test.assert_equals(a.Empty(), true);
        
        // Testar clear em lista já vazia
        a.Clear();
        test.assert_equals(a.ToString(), "[]");
        test.assert_equals(a.Size(), 0);
        test.assert_equals(a.Empty(), true);
    }

    // ========== TESTES DE COPY CONSTRUCTOR ==========
    {
        List a;
        a.PushBack(1);
        a.PushBack(2);
        a.PushBack(3);
        
        List b(a); // copy constructor
        test.assert_equals(b.ToString(), "[1, 2, 3]");
        test.assert_equals(b.Size(), 3);
        
        // Modificar original não deve afetar a cópia
        a.PushBack(4);
        test.assert_equals(a.ToString(), "[1, 2, 3, 4]");
        test.assert_equals(b.ToString(), "[1, 2, 3]");
        
        // Modificar cópia não deve afetar original
        b.PushBack(5);
        test.assert_equals(a.ToString(), "[1, 2, 3, 4]");
        test.assert_equals(b.ToString(), "[1, 2, 3, 5]");
    }

    // ========== TESTES DE COPY ASSIGNMENT ==========
    {
        List a;
        a.PushBack(10);
        a.PushBack(20);
        a.PushBack(30);
        
        List b;
        b.PushBack(999); // b já tem conteúdo
        
        b = a; // copy assignment
        test.assert_equals(b.ToString(), "[10, 20, 30]");
        test.assert_equals(b.Size(), 3);
        
        // Modificar original não deve afetar a cópia
        a.PushBack(40);
        test.assert_equals(a.ToString(), "[10, 20, 30, 40]");
        test.assert_equals(b.ToString(), "[10, 20, 30]");
        
        // Auto-atribuição
        a = a;
        test.assert_equals(a.ToString(), "[10, 20, 30, 40]");
        test.assert_equals(a.Size(), 4);
    }

    // ========== TESTES COM NÚMEROS NEGATIVOS ==========
    {
        List a;
        a.PushBack(-10);
        a.PushBack(-5);
        a.PushBack(0);
        a.PushBack(5);
        a.PushBack(10);
        
        test.assert_equals(a.ToString(), "[-10, -5, 0, 5, 10]");
        test.assert_equals(a.Get(0), -10);
        test.assert_equals(a.Get(1), -5);
        test.assert_equals(a.Search(-10), 0);
        test.assert_equals(a.Search(-5), 1);
    }

    // ========== TESTES COMBINADOS (OPERAÇÕES MISTAS) ==========
    {
        List a;
        
        // Combinação de pushes
        a.PushBack(2);
        a.PushFront(1);
        a.PushBack(4);
        a.PushAt(3, 2);
        test.assert_equals(a.ToString(), "[1, 2, 3, 4]");
        
        // Combinação de operações
        a.Set(10, 1);
        test.assert_equals(a.ToString(), "[1, 10, 3, 4]");
        
        int val = a.PopAt(2);
        test.assert_equals(val, 3);
        test.assert_equals(a.ToString(), "[1, 10, 4]");
        
        a.PushFront(0);
        test.assert_equals(a.ToString(), "[0, 1, 10, 4]");
        
        val = a.PopBack();
        test.assert_equals(val, 4);
        test.assert_equals(a.ToString(), "[0, 1, 10]");
        
        val = a.PopFront();
        test.assert_equals(val, 0);
        test.assert_equals(a.ToString(), "[1, 10]");
    }

    // ========== TESTES DE STRESS (MUITOS ELEMENTOS) ==========
    {
        List a;
        
        // Inserir muitos elementos
        for(int i = 0; i < 100; i++) {
            a.PushBack(i);
        }
        test.assert_equals(a.Size(), 100);
        test.assert_equals(a.Get(0), 0);
        test.assert_equals(a.Get(50), 50);
        test.assert_equals(a.Get(99), 99);
        
        // Remover todos
        while(!a.Empty()) {
            a.PopFront();
        }
        test.assert_equals(a.Size(), 0);
        test.assert_equals(a.Empty(), true);
        test.assert_equals(a.ToString(), "[]");
    }

    // ========== TESTES DE EDGE CASES ==========
    {
        // Lista com um elemento só
        List a;
        a.PushBack(42);
        test.assert_equals(a.ToString(), "[42]");
        test.assert_equals(a.Size(), 1);
        test.assert_equals(a.Get(0), 42);
        test.assert_equals(a.Search(42), 0);
        
        a.Set(84, 0);
        test.assert_equals(a.ToString(), "[84]");
        
        test.assert_equals(a.PopFront(), 84);
        test.assert_equals(a.Empty(), true);
        
        // Testar PushAt em posições extremas de lista pequena
        List b;
        b.PushAt(1, 0);
        b.PushAt(3, 1);
        b.PushAt(2, 1);
        test.assert_equals(b.ToString(), "[1, 2, 3]");
    }

    return 0;
}