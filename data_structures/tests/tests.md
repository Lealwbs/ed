# 🧪 Testes das Estruturas de Dados

Este repositório organiza os **TADs** em pastas separadas (`list/`, `queue/`, `stack/`, `avl_tree/`, etc.), e cada um possui seus próprios arquivos `.cpp` e `.hpp`. Os **testes unitários** ficam na pasta `tests/`, seguindo o padrão:

```
Code/alg1/
├── cpp_unit_test/
│   ├── include/
│   │   └── assert.hpp
│   └── src/
│       └── assert.cpp
└── data_structures/
    ├── list/
    │   ├── list.cpp 
    │   └── list.hpp
    ├── queue/
    │   ├── queue.cpp
    │   └── queue.hpp
    ├── stack/
    │   ├── stack.cpp
    │   └── stack.hpp
    ├── avl_tree/
    │   ├── avl_tree.cpp
    │   └── avl_tree.hpp
    ├── dsu/
    │   ├── dsu.cpp
    │   └── dsu.hpp
    ├── graph/
    │   ├── graph.cpp
    │   └── graph.hpp
    ├── hash_table/
    │   ├── hash_table.cpp
    │   └── hash_table.hpp
    ├── min_heap/
    │   ├── min_heap.cpp
    │   └── min_heap.hpp
    └── tests/
        ├── Makefile
        ├── list_test.cpp
        ├── queue_test.cpp
        ├── bin/              # Binários compilados (.exe)
        └── obj/              # Arquivos objeto (.o)
```

O `Makefile` foi configurado especificamente para **Windows** com:
- **Compilação manual** e explícita de cada teste
- **Integração** com a biblioteca de testes `cpp_unit_test`
- **Organização** dos binários em `tests/bin/` e objetos em `tests/obj/`
- **Comandos simples** e extensíveis

<br>

## 📋 Estruturas de Dados e Testes

| Estrutura | Arquivo de Teste | Status |
|-----------|------------------|--------|
| 📝 **Lista** | `list_test.cpp` | ✅ Disponível |
| 🔄 **Fila (Queue)** | `queue_test.cpp` | ✅ Disponível |
| 📚 **Pilha (Stack)** | `stack_test.cpp` | 🔄 Para adicionar |
| 🌳 **Árvore AVL** | `avl_tree_test.cpp` | 🔄 Para adicionar |
| 🔗 **DSU (Disjoint Set Union)** | `dsu_test.cpp` | 🔄 Para adicionar |
| 🕸️ **Grafo** | `graph_test.cpp` | 🔄 Para adicionar |
| #️⃣ **Tabela Hash** | `hash_table_test.cpp` | 🔄 Para adicionar |
| ⬆️ **Min Heap** | `min_heap_test.cpp` | 🔄 Para adicionar |

<br>

# ▶️ Comandos Makefile

### 🏃‍♂️ Executar Testes

#### Testes disponíveis
```bash
mingw32-make test_list    # Testa Lista
mingw32-make test_queue   # Testa Fila
```

### 🔧 Utilitários

#### Compilar todos os testes
```bash
mingw32-make compile
```

#### Limpar arquivos compilados
```bash
mingw32-make clean
```

#### Ver comandos disponíveis
```bash
mingw32-make help
```

<br>

## 🚀 Como Usar

1. **Navegue até a pasta de testes**:
   ```bash
   cd data_structures/tests
   ```

2. **Execute um teste específico**:
   ```bash
   mingw32-make test_list
   ```

3. **Compile todos os testes sem executar**:
   ```bash
   mingw32-make compile
   ```

4. **Limpe os arquivos compilados**:
   ```bash
   mingw32-make clean
   ```

<br>

## ➕ Adicionando Novos Testes

Para adicionar uma nova estrutura de dados (exemplo: **stack**):

### 1. **Crie o arquivo de teste**:
```cpp
// stack_test.cpp
#include "assert.hpp"
#include "stack.hpp"

int main(){
    CPP_UNIT_ASSERT t = CPP_UNIT_ASSERT();
    
    // Seus testes aqui
    t.assert_equals("esperado", "atual");
    
    return 0;
}
```

### 2. **Edite o Makefile**:

**No target `compile:`**
```makefile
compile: $(BIN_DIR)/list_test.exe $(BIN_DIR)/queue_test.exe $(BIN_DIR)/stack_test.exe
```

**Adicione as regras:**
```makefile
# Compilar teste da pilha
$(BIN_DIR)/stack_test.exe: stack_test.cpp $(OBJ_DIR)/stack.o $(OBJ_DIR)/assert.o
    @if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
    $(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(CPP_UNIT_DIR)/include stack_test.cpp $(OBJ_DIR)/stack.o $(OBJ_DIR)/assert.o -o $(BIN_DIR)/stack_test.exe

# Compilar objeto da pilha
$(OBJ_DIR)/stack.o: $(SRC_DIR)/stack/stack.cpp
    @if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
    $(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(CPP_UNIT_DIR)/include -c $(SRC_DIR)/stack/stack.cpp -o $(OBJ_DIR)/stack.o

# Executar teste da pilha
test_stack: $(BIN_DIR)/stack_test.exe
    @echo Executando teste da pilha...
    @$(BIN_DIR)/stack_test.exe
```

### 3. **Teste o novo comando**:
```bash
mingw32-make test_stack
```

<br>

## 🛠️ Configurações Técnicas

- **Compilador**: `g++` (MinGW no Windows)
- **Padrão**: C++17
- **Flags**: `-Wall -Wextra -g` (warnings e debug)
- **Framework de Testes**: `cpp_unit_test` customizado
- **Inclusões**:
  - `data_structures/` para as estruturas
  - `cpp_unit_test/include/` para os asserts

<br>

## 📖 Estrutura do Makefile

O Makefile é **simples e manual** para facilitar:
- **Controle total** sobre cada compilação
- **Fácil extensão** copiando e adaptando seções
- **Compatibilidade total** com Windows/MinGW
- **Integração** com a biblioteca de testes personalizada

### Exemplo de uso da biblioteca de testes:
```cpp
#include "assert.hpp"
#include "list.hpp"

int main(){
    CPP_UNIT_ASSERT t = CPP_UNIT_ASSERT();
    
    // Testes
    t.assert_equals(expected, actual);
    t.assert_true(condition);
    
    return 0;
}
```