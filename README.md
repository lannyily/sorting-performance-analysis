# Análise de Desempenho: Insertion Sort vs. Tree Sort (BST & AVL)

Este projeto tem como objetivo analisar e comparar a eficiência de diferentes algoritmos de ordenação em diversos cenários (vetores crescentes, decrescentes e aleatórios). O foco principal é observar a diferença de performance entre algoritmos de complexidade quadrática () e logarítmica ().

## Estrutura do Diretório

O projeto está organizado da seguinte forma:

### Implementações Base

* **`InsertionSort.c`**: Implementação simples e direta do algoritmo de ordenação por inserção.
* **`TreeSort.c`**: Implementação básica de ordenação utilizando uma Árvore Binária de Busca (BST) convencional.

### Scripts de Experimentação (Benchmarks)

Estes arquivos automatizam a coleta de dados, testando tamanhos de vetor de **10.000 a 200.000** elementos, com **30 repetições** para cada caso para garantir precisão estatística.

* **`experimentoIS.c`**: Executa testes de estresse para o **Insertion Sort**.
* **`experimentoBST.c`**: Realiza o benchmark para o **Tree Sort** utilizando uma BST simples (focado em dados aleatórios).
* **`experimentoAVL.c`**: A versão mais robusta, utilizando **Árvore AVL** auto-balanceada e um **Memory Pool** para otimizar a alocação de memória.

### Resultados

* **`resultados/`**: Pasta contendo os arquivos `.csv` gerados pelos experimentos:
* `resultados_insertion_sort.csv`
* `resultados_tree_sort_bst.csv`
* `resultados_tree_sort.csv` (Resultados da AVL)

## Como Executar

Para compilar e rodar qualquer um dos experimentos, você precisará de um compilador C (como o GCC).

1. **Compilar:**
```bash
gcc experimentoAVL.c -o experimentoAVL

```

2. **Executar:**
```bash
./experimentoAVL

```

O programa exibirá o progresso no terminal e salvará os tempos médios de execução no respectivo arquivo CSV.


## Algoritmos Analisados

| Algoritmo | Complexidade (Médio Caso) | Estrutura de Dados | Diferencial nesta Implementação |
| --- | --- | --- | --- |
| **Insertion Sort** | O(n2) | Array | Ordenação *in-place*. |
| **Tree Sort (BST)** | O(n log n) | Árvore Binária | Simplicidade de implementação. |
| **Tree Sort (AVL)** | O(n log n) | Árvore AVL | **Memory Pool** e balanceamento garantido. |

### Otimização por Memory Pool (AVL)

No arquivo `experimentoAVL.c`, foi implementado um **Memory Pool**. Em vez de realizar milhares de chamadas ao sistema via `malloc()`, o código aloca um bloco contíguo de memória para todos os nós da árvore de uma só vez, o que reduz drasticamente o tempo de CPU gasto com gerenciamento de memória.

## Formato dos Resultados

Os arquivos CSV gerados seguem o padrão:
`Tamanho;Crescente;Decrescente;Aleatorio`

Isso permite que você importe os dados facilmente para ferramentas como **Excel**, **Google Sheets** ou scripts em **Python (Pandas/Matplotlib)** para gerar gráficos de desempenho.
