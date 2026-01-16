#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Preenche o vetor com valores em ordem crescente (1 a tamanho).
 * * @param vetor Array de inteiros a ser preenchido.
 * @param tamanho Quantidade de elementos no vetor.
 */
void gerarOrdenado(int vetor[], int tamanho){
    for (int i = 0; i < tamanho; i++)
        vetor[i] = i + 1;
}


/**
 * @brief Preenche o vetor com valores em ordem decrescente.
 * * @param vetor Array de inteiros a ser preenchido.
 * @param tamanho Quantidade de elementos no vetor.
 */
void gerarDecrescente(int vetor[], int tamanho){
    for (int i = 0; i < tamanho; i++)
        vetor[i] = tamanho - i;
}

/**
 * @brief Preenche o vetor com números aleatórios.
 * * @param vetor Array de inteiros a ser preenchido.
 * @param tamanho Quantidade de elementos no vetor.
 */
void gerarAleatorio(int vetor[], int tamanho){
    for (int i = 0; i < tamanho; i++)
        vetor[i] = rand() % 9999999;
}


/**
 * @brief Exibe todos os elementos do vetor no console.
 * * @param vetor Array de inteiros a ser impresso.
 * @param tamanho Quantidade de elementos no vetor.
 */
void imprimirVetor(int vetor[], int tamanho){
    for (int i = 0; i < tamanho; i++)
        printf("%d ", vetor[i]);
    printf("\n");
}

/**
 * @brief Ordena um vetor utilizando o algoritmo Insertion Sort (Ordenação por Inserção).
 * * O algoritmo percorre o vetor da esquerda para a direita, "puxando" cada elemento
 * para sua posição correta na parte já ordenada do array.
 * * @param vetor Array de inteiros a ser ordenado.
 * @param tamanho Quantidade de elementos no vetor.
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
 * @brief Mede o tempo de execução de um algoritmo de ordenação.
 * * @param algoritmo Ponteiro para a função de ordenação que segue a assinatura void(int[], int).
 * @param vetor O array que será ordenado.
 * @param tamanho O tamanho do array.
 * @return double O tempo decorrido em segundos.
 */
double medirTempoOrdenacao(void (*algoritmo)(int[], int), int vetor[], int tamanho){
    clock_t inicio, fim;

    inicio = clock();
    algoritmo(vetor, tamanho);
    fim = clock();

    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

int main(){
    int tamanho, opcao;
    double tempo;


    printf("Digite a quantidade de numeros: ");
    scanf("%d", &tamanho);

    int vetor[tamanho];

    printf("1-Crescente, 2-Decrescente, 3-Aleatorio: ");
    scanf("%d", &opcao);

    switch (opcao){
        case 1:
            gerarOrdenado(vetor, tamanho);
            break;
        case 2:
            gerarDecrescente(vetor, tamanho);
            break;
        case 3:
            gerarAleatorio(vetor, tamanho);
            break;
        default:
            printf("Opcao invalida!\n");
            return 1;
    }

    imprimirVetor(vetor, tamanho);

    tempo = medirTempoOrdenacao(insertionSort, vetor, tamanho);

    imprimirVetor(vetor, tamanho);

    printf("\nTempo: %.6f segundos\n", tempo);

    return 0;
}
