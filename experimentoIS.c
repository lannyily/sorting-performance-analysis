#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REPETICOES 30
#define INICIO 10000
#define FIM 200000
#define PASSO 10000



/**
 * @brief Preenche o vetor com valores em ordem crescente.
 * @param vetor Array de inteiros.
 * @param tamanho Tamanho do array.
 */
void gerarOrdenado(int vetor[], int tamanho){

    for (int i = 0; i < tamanho; i++)
        vetor[i] = i + 1;
}

/**
 * @brief Preenche o vetor com valores em ordem decrescente (pior caso para Insertion Sort).
 * @param vetor Array de inteiros.
 * @param tamanho Tamanho do array.
 */
void gerarDecrescente(int vetor[], int tamanho){

    for (int i = 0; i < tamanho; i++)
        vetor[i] = tamanho - i;
}


/**
 * @brief Preenche o vetor com valores aleatórios usando rand().
 * @param vetor Array de inteiros.
 * @param tamanho Tamanho do array.
 */
void gerarAleatorio(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
        vetor[i] = rand();
}

/**
 * @brief Implementação clássica do algoritmo Insertion Sort.
 * @details Possui complexidade $O(n)$ para vetores ordenados e $O(n^2)$ para casos médios e inversos.
 * @param vetor Array de inteiros a ser ordenado.
 * @param tamanho Tamanho do array.
 */
void insertionSort(int vetor[], int tamanho){
    for (int i = 1; i < tamanho; i++){
        int chave = vetor[i];
        int j = i - 1;

        while (j >= 0 && vetor[j] > chave){
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;

    }
}

/**
 * @brief Captura o tempo de execução de uma função de ordenação.
 * @param algoritmo Ponteiro para a função de ordenação.
 * @param vetor Array a ser ordenado.
 * @param tamanho Tamanho do array.
 * @return double Tempo decorrido em segundos.
 */
double medirTempoOrdenacao(void (*algoritmo)(int[], int), int vetor[], int tamanho){

    clock_t inicio = clock();
    algoritmo(vetor, tamanho);
    clock_t fim = clock();

    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

int main(){

    FILE *arquivo = fopen("resultados_insertion_sort.csv", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao criar o arquivo CSV.\n");
        return 1;
    }

    fprintf(arquivo, "Tamanho,Crescente,Decrescente,Aleatorio\n");

    for (int tamanho = INICIO; tamanho <= FIM; tamanho += PASSO){
        double tempoCrescente = 0.0;
        double tempoDecrescente = 0.0;
        double tempoAleatorio = 0.0;

        int *vetor = malloc(tamanho * sizeof(int));

        if (vetor == NULL)
        {
            printf("Erro de alocacao de memoria.\n");
            fclose(arquivo);
            return 1;
        }

        for (int i = 0; i < REPETICOES; i++)
        {
            gerarOrdenado(vetor, tamanho);
            tempoCrescente += medirTempoOrdenacao(insertionSort, vetor, tamanho);

            gerarDecrescente(vetor, tamanho);
            tempoDecrescente += medirTempoOrdenacao(insertionSort, vetor, tamanho);

            gerarAleatorio(vetor, tamanho);
            tempoAleatorio += medirTempoOrdenacao(insertionSort, vetor, tamanho);
        }

        fprintf(arquivo, "%d,%.6f,%.6f,%.6f\n",
                tamanho,
                tempoCrescente / REPETICOES,
                tempoDecrescente / REPETICOES,
                tempoAleatorio / REPETICOES);

        printf("Processado tamanho %d\n", tamanho);

        free(vetor);
    }

    fclose(arquivo);

    printf("\nResultados salvos em 'resultados_insertion_sort.csv'\n");
    return 0;
}
