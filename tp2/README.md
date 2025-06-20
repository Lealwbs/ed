# TP2 - Sistema de Escalonamento Logístico

## Visão Geral

Este projeto implementa um sistema de simulação de eventos discretos para gerenciar a logística de pacotes entre uma rede de armazéns, inspirado no problema "Armazéns Hanoi". O sistema é projetado para escalonar e rotear pacotes, considerando capacidades, latências e uma lógica de armazenamento LIFO (Last-In, First-Out).

O núcleo da simulação gerencia eventos cronologicamente usando um escalonador de prioridades (Min-Heap). A rede de armazéns é modelada como um grafo não direcionado, e as rotas são calculadas como o caminho mais curto. Cada armazém contém seções de armazenamento que funcionam como pilhas, onde o último pacote a entrar é o primeiro a sair.

## Estrutura do Projeto

O código-fonte está organizado na seguinte estrutura de diretórios:

-   **`include/`**: Contém os arquivos de cabeçalho (`.hpp`) com as definições de todas as classes e TADs utilizados no projeto.
    -   `simulacao.hpp`: Orquestra toda a lógica da simulação de eventos discretos.
    -   `heap_escalonador.hpp`: Implementa o escalonador de eventos como uma fila de prioridade (Min-Heap).
    -   `grafo_rede.hpp`: Modela a rede de armazéns como um grafo.
    -   `armazem.hpp`: Representa um armazém individual.
    -   `pilha_secao.hpp`: Implementa as seções de armazenamento com lógica de pilha (LIFO).
    -   `pacote.hpp`: Define a estrutura e os estados de um pacote.
    -   `evento.hpp`: Define as classes base e derivadas para os eventos da simulação (Chegada, Transporte).
-   **`src/`**: Contém os arquivos de implementação (`.cpp`) para cada classe definida nos cabeçalhos.
    -   `main.cpp`: Ponto de entrada do programa, responsável por ler o arquivo de configuração e iniciar a simulação.
-   **`bin/`**: Diretório onde o executável final é gerado pelo Makefile.
-   **`obj/`**: Armazena os arquivos-objeto (`.o`) gerados durante a compilação.
-   **`files/`**: Contém os arquivos de entrada para os cenários de simulação e os enunciados do trabalho.
-   **`makefile`**: Script para compilação e execução do projeto.

## Como Funciona

A simulação opera como um sistema de eventos discretos, seguindo os seguintes passos:

1.  **Inicialização**: O programa lê um arquivo de entrada que define os parâmetros da simulação (capacidade de transporte, latência, etc.), a topologia da rede de armazéns (matriz de adjacência) e a lista de pacotes a serem enviados.
2.  **Criação do Cenário**: Uma instância da classe `Simulacao` é criada, inicializando a rede de armazéns, o escalonador de eventos e as estruturas de dados.
3.  **Roteamento de Pacotes**: Para cada pacote, o sistema calcula a rota mais curta (em número de saltos) entre a origem e o destino usando uma busca em largura (BFS) no grafo da rede.
4.  **Agendamento de Eventos Iniciais**:
    -   Para cada pacote, um evento de **Chegada** é agendado em seu armazém de origem no tempo especificado.
    -   Eventos de **Transporte** recorrentes são agendados para cada conexão entre os armazéns, começando no tempo de chegada do primeiro pacote.
5.  **Laço de Simulação**: O sistema processa os eventos em ordem cronológica a partir do escalonador (Min-Heap) até que todos os pacotes sejam entregues.
    -   **Evento de Chegada**: Ao chegar em um armazém, se não for o destino final, o pacote é colocado (empilhado) na seção correspondente ao próximo armazém em sua rota. Se for o destino, a entrega é registrada.
    -   **Evento de Transporte**: Retira pacotes de uma seção (seguindo a lógica LIFO) até a capacidade máxima de transporte. Para cada pacote retirado, um novo evento de **Chegada** é agendado no próximo armazém, considerando a latência da viagem. Um novo evento de transporte para a mesma rota é reagendado para o futuro.
6.  **Saída**: Ao final da simulação, um log detalhado com todos os eventos (armazenamento, remoção, trânsito e entrega) é impresso na saída padrão.

## Compilação e Uso

### Compilação

Para compilar o projeto, utilize o `Makefile` fornecido. Execute o seguinte comando na raiz do diretório `tp2`:

```bash
make all
```

Este comando compilará todos os arquivos-fonte e criará o executável tp2.out (ou tp2.exe no Windows) dentro do diretório bin/.

Execução
O programa é executado via linha de comando, recebendo como argumento o caminho para o arquivo de entrada da simulação.

```bash
./bin/tp2.out <caminho_para_o_arquivo_de_entrada>
```

Por exemplo, para executar a simulação com o cenário de exemplo 1:

```bash
./bin/tp2.out files/e1/sched.wkl
```