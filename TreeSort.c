#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @struct No
 * @brief Estrutura que representa um nó em uma Árvore Binária de Busca (BST).
 */
struct No{
    int chave;
    struct No *esquerda;
    struct No *direita;
};

/**
 * @brief Cria e inicializa um novo nó para a árvore.
 * * @param valor O valor inteiro a ser armazenado no nó.
 * @return struct No* Ponteiro para o nó recém-criado ou NULL em caso de falha de alocação.
 */
struct No* novoNo(int valor){
    struct No* temp = (struct No*) malloc(sizeof(struct No));
    if(temp == NULL) return NULL; 
    temp->chave = valor;
    temp->esquerda = NULL;
    temp->direita = NULL;

    return temp;
}

/**
 * @brief Insere um valor na árvore de forma iterativa.
 * * @param raiz Ponteiro para a raiz da árvore atual.
 * @param valor O valor a ser inserido.
 * @return struct No* A raiz da árvore (útil para a primeira inserção).
 */
struct No* inserir(struct No* raiz, int valor){

    struct No* novo = novoNo(valor);
    if (raiz == NULL) return novo;

    struct No *atual = raiz;
    struct No *pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (valor < atual->chave)
            atual = atual->esquerda;
        else
            atual = atual->direita;
    }

    if (valor < pai->chave)
        pai->esquerda = novo;
    else
        pai->direita = novo;

    return raiz;

}


/**
 * @brief Realiza o percurso In-Order (em-ordem) para extrair os dados ordenados.
 * * @param raiz Ponteiro para a raiz da árvore.
 * @param vetor Vetor onde os elementos serão armazenados.
 * @param indice Ponteiro para o índice atual do vetor (controla a posição da escrita).
 */
void armazenarOrdenado(struct No* raiz, int vetor[], int* indice){
    if (raiz != NULL) {
        armazenarOrdenado(raiz->esquerda, vetor, indice);
        vetor[(*indice)++] = raiz->chave;
        armazenarOrdenado(raiz->direita, vetor, indice);

    }
}

/**
 * @brief Libera recursivamente toda a memória alocada para a árvore.
 * * @param raiz Ponteiro para a raiz da árvore a ser destruída.
 */
void liberarArvore(struct No* raiz){
    if (raiz != NULL){
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);

    }
}

/**
 * @brief Implementação do algoritmo Tree Sort.
 * * Constrói uma BST a partir de um vetor e depois utiliza o percurso 
 * em-ordem para devolver os elementos ordenados ao vetor original.
 * * @param vetor O array de inteiros a ser ordenado.
 * @param tamanho A quantidade de elementos no array.
 */
void treeSort(int vetor[], int tamanho){
    struct No* raiz = NULL;

    for (int i = 0; i < tamanho; i++) {
        raiz = inserir(raiz, vetor[i]);
    }

    int indice = 0;
    armazenarOrdenado(raiz, vetor, &indice);
    liberarArvore(raiz); 

}


/**
 * @brief Gera um vetor baseado em cenários específicos para testes de performance.
 * * @param vetor Vetor a ser preenchido.
 * @param tamanho Tamanho do vetor.
 * @param tipo 1 para Crescente, 2 para Decrescente, qualquer outro para Aleatório.
 */
void gerarVetor(int vetor[], int tamanho, int tipo){
    if (tipo == 1){
        for (int i = 0; i < tamanho; i++) vetor[i] = i;
    } 
    else if (tipo == 2) {
        for (int i = 0; i < tamanho; i++) vetor[i] = tamanho - i;
    } 
    else {
        for (int i = 0; i < tamanho; i++) vetor[i] = rand() % (tamanho * 10);
    }
}

void imprimirVetor(int vetor[], int tamanho){
    for (int i = 0; i < tamanho; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}


int main() {
    int tamanho, tipo;
    srand(time(NULL));

    printf("Digite a quantidade de numeros: ");
    if (scanf("%d", &tamanho) != 1) return 1;

    int *vetor = (int*) malloc(tamanho * sizeof(int));
    if (vetor == NULL) return 1;

    printf("1-Crescente, 2-Decrescente, 3-Aleatorio: ");
    scanf("%d", &tipo);

    gerarVetor(vetor, tamanho, tipo);

    imprimirVetor(vetor, tamanho);

    clock_t inicio = clock();
    treeSort(vetor, tamanho);
    clock_t fim = clock();

    imprimirVetor(vetor, tamanho);

    printf("\nTempo: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    

    free(vetor);
    return 0;
}