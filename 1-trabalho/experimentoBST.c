#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REPETICOES 30
#define INICIO 10000
#define FIM 200000
#define PASSO 10000

/**
 * @struct No
 * @brief Representa um nó da Árvore Binária de Busca (BST).
 */
typedef struct No {
    int num;
    struct No *esq, *dir;
} No;


/**
 * @brief Aloca memória e inicializa um novo nó da árvore.
 * @param valor O valor inteiro a ser inserido.
 * @return No* Ponteiro para o novo nó criado.
 */
No* novo_no(int valor){
    No* n = (No*)malloc(sizeof(No));
    n->num = valor;
    n->esq = NULL;
    n->dir = NULL;
    return n;
}


/**
 * @brief Insere um valor na árvore de forma recursiva.
 * @details Caso a raiz seja nula, cria o primeiro nó. Caso contrário, decide 
 * o lado da inserção com base no valor (menores à esquerda, maiores ou iguais à direita).
 * @param raiz Ponteiro para a raiz atual da subárvore.
 * @param valor Valor a ser inserido.
 * @return No* Ponteiro para a raiz (atualizado após a inserção).
 */
No* inserir(No* raiz, int valor) {
    if (raiz == NULL)
        return novo_no(valor);

    if (valor < raiz->num)
        raiz->esq = inserir(raiz->esq, valor);
    else
        raiz->dir = inserir(raiz->dir, valor);

    return raiz;
}


/**
 * @brief Percorre a árvore em-ordem (In-Order) e armazena os valores no vetor.
 * @details Esta função é o que garante a ordenação, visitando primeiro a esquerda, 
 * depois o nó atual e por fim a direita.
 * @param raiz Ponteiro para a raiz da árvore.
 * @param vetor Vetor que receberá os elementos ordenados.
 * @param idx Ponteiro para o índice atual de preenchimento do vetor.
 */
void em_ordem(No* raiz, int vetor[], int* idx) {
    if (raiz == NULL) return;

    em_ordem(raiz->esq, vetor, idx);
    vetor[(*idx)++] = raiz->num;
    em_ordem(raiz->dir, vetor, idx);
}


/**
 * @brief Libera a memória de todos os nós da árvore (pós-ordem).
 * @param raiz Ponteiro para a raiz da árvore a ser desalocada.
 */
void liberar_arvore(No* raiz) {
    if (raiz == NULL) return;
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}

/**
 * @brief Algoritmo Tree Sort completo.
 * @details 1. Insere todos os elementos do vetor em uma BST.
 * 2. Recupera-os ordenados via percurso em-ordem.
 * 3. Limpa a árvore da memória.
 * @param vetor O vetor a ser ordenado.
 * @param n O número de elementos no vetor.
 */
void tree_sort(int vetor[], int n){
    No* raiz = NULL;

    for (int i = 0; i < n; i++) {
        raiz = inserir(raiz, vetor[i]);
    }

    int idx = 0;
    em_ordem(raiz, vetor, &idx);

    liberar_arvore(raiz);
}

/**
 * @brief Preenche um vetor com números inteiros aleatórios.
 * @param v Vetor de inteiros.
 * @param n Tamanho do vetor.
 */
void gerar_dados(int v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i] = rand();
    }
}


int main(){

    FILE *f = fopen("resultados_tree_sort_bst.csv", "w");
    if (!f) {
        printf("Erro ao criar arquivo!\n");
        return 1;
    }

    fprintf(f, "Tamanho;Tempo\n");
    printf("--- Testes de Desempenho Tree Sort (BST) ---\n");

    for (int n = INICIO; n <= FIM; n += PASSO) {
        printf("Testando N = %-7d | ", n);

        double soma = 0.0;

        for (int exec = 0; exec < REPETICOES; exec++) {
            int *v = (int*)malloc(n * sizeof(int));
            gerar_dados(v, n);

            clock_t t = clock();
            tree_sort(v, n);
            soma += (double)(clock() - t) / CLOCKS_PER_SEC;

            free(v);
        }

        double media = soma / REPETICOES;
        fprintf(f, "%d;%.6f\n", n, media);

        printf("OK\n");
    }

    fclose(f);
    return 0;
}
