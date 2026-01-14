#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REPETICOES 30
#define INICIO 10000
#define FIM 200000
#define PASSO 10000

/**
 * @struct No
 * @brief Estrutura de um nó de Árvore AVL.
 */
typedef struct No {
    int num;
    struct No *esq, *dir;
    int altura;
} No;

No* pool_nos = NULL;
int pool_idx = 0;

/**
 * @brief Obtém a altura de um nó de forma segura (trata NULL).
 * @param n Ponteiro para o nó.
 * @return int Altura do nó (0 se NULL).
 */
int get_altura(No *n){
    return (n == NULL) ? 0 : n->altura;
}


/** @brief Retorna o maior valor entre dois inteiros. */
int max(int a, int b){ 
    return (a > b) ? a : b; 
}

/**
 * @brief Aloca um nó a partir do pool pré-alocado (evita chamadas excessivas ao malloc).
 * @param valor O número a ser armazenado.
 * @return No* Ponteiro para o nó dentro do pool.
 */
No* novo_no_pool(int valor){
    No* n = &pool_nos[pool_idx++];
    n->num = valor;
    n->esq = n->dir = NULL;
    n->altura = 1;
    return n;

}


/**
 * @brief Realiza uma rotação simples à direita.
 * @param y Raiz da subárvore a ser rotacionada.
 * @return No* Nova raiz da subárvore.
 */
No* rot_dir(No *y){
    No *x = y->esq;
    No *T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    y->altura = max(get_altura(y->esq), get_altura(y->dir)) + 1;
    x->altura = max(get_altura(x->esq), get_altura(x->dir)) + 1;
    return x;

}


/**
 * @brief Realiza uma rotação simples à esquerda.
 * @param x Raiz da subárvore a ser rotacionada.
 * @return No* Nova raiz da subárvore.
 */
No* rot_esq(No *x){

    No *y = x->dir;
    No *T2 = y->esq;
    y->esq = x;
    x->dir = T2;
    x->altura = max(get_altura(x->esq), get_altura(x->dir)) + 1;
    y->altura = max(get_altura(y->esq), get_altura(y->dir)) + 1;
    return y;
}

/**
 * @brief Insere um valor na AVL e mantém o balanceamento.
 * @details Após a inserção recursiva, calcula o fator de equilíbrio e aplica 
 * rotações (Simples ou Duplas) se necessário.
 * @param no Raiz da subárvore.
 * @param num Valor a inserir.
 * @return No* Nova raiz da subárvore balanceada.
 */
No* inserir(No* no, int num){
    if (no == NULL) return novo_no_pool(num);
    
    if (num < no->num) no->esq = inserir(no->esq, num);
    else no->dir = inserir(no->dir, num);

    no->altura = 1 + max(get_altura(no->esq), get_altura(no->dir));
    int bal = get_altura(no->esq) - get_altura(no->dir);

    if (bal > 1 && num < no->esq->num) return rot_dir(no);
    if (bal < -1 && num >= no->dir->num) return rot_esq(no);

    if (bal > 1 && num >= no->esq->num){
        no->esq = rot_esq(no->esq);
        return rot_dir(no);
    }

    if (bal < -1 && num < no->dir->num){
        no->dir = rot_dir(no->dir);
        return rot_esq(no);
    }

    return no;
}

/**
 * @brief Percurso In-Order para extração dos dados ordenados.
 */
void em_ordem(No* raiz, int vetor[], int* idx) {
    if (raiz == NULL) return;
    em_ordem(raiz->esq, vetor, idx);
    vetor[(*idx)++] = raiz->num;
    em_ordem(raiz->dir, vetor, idx);

}


/**
 * @brief Tree Sort otimizado com Árvore AVL e Memory Pool.
 * @param vetor Vetor a ser ordenado.
 * @param n Tamanho do vetor.
 */
void tree_sort(int vetor[], int n) {
    
    pool_nos = (No*)malloc(n * sizeof(No));
    pool_idx = 0;
    
    No* raiz = NULL;
    for (int i = 0; i < n; i++) {
        raiz = inserir(raiz, vetor[i]);
    }

    int idx = 0;
    em_ordem(raiz, vetor, &idx);
    
    free(pool_nos); 
}

/**
 * @brief Gera vetores de teste (0: Crescente, 1: Decrescente, 2: Aleatório).
 */
void gerar_dados(int v[], int n, int tipo){
    for(int i = 0; i < n; i++) {
        if (tipo == 0) v[i] = i;
        else if (tipo == 1) v[i] = n - i;
        else v[i] = rand() % (n * 10);
    }
    
}

int main() {
    srand(time(NULL));
    FILE *f = fopen("resultados_tree_sort.csv", "w");
    if (!f){ 
        printf("Erro ao criar arquivo!\n"); 
        return 1; 
    }

    fprintf(f, "Tamanho;Crescente;Decrescente;Aleatorio\n");
    printf("--- Testes de Desempenho Tree Sort (AVL) ---\n");

    for (int n = INICIO; n <= FIM; n += PASSO) {
        printf("Testando N = %-7d | ", n);
        double medias[3] = {0,0,0};

        for (int tipo = 0; tipo < 3; tipo++) {
            double soma = 0;
            for (int exec = 0; exec < REPETICOES; exec++) {
                int *v = (int*)malloc(n * sizeof(int));
                gerar_dados(v, n, tipo);

                clock_t t = clock();
                tree_sort(v, n);
                soma += (double)(clock() - t) / CLOCKS_PER_SEC;

                free(v);
            }
            medias[tipo] = soma / 5.0;
            printf("#"); fflush(stdout);
        }
        fprintf(f, "%d;%.5f;%.5f;%.5f\n", n, medias[0], medias[1], medias[2]);
        printf(" OK!\n");
    }

    fclose(f);
    
    return 0;
}