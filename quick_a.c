#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void trocar(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int particionar(int arr[], int baixo, int alto) {
    int pivo = arr[alto];
    int i = (baixo - 1);

    for (int j = baixo; j < alto; j++) {
        if (arr[j] <= pivo) {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }
    trocar(&arr[i + 1], &arr[alto]);
    return (i + 1);
}

void quickSort(int arr[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(arr, baixo, alto);
        quickSort(arr, baixo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

int main() {
    FILE* arquivo = fopen("quick_a_time.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int tamanhoVetor;
    int incremento = 10;
    int numExecucoes = (1000 - 100) / incremento + 1;

    // Loop para executar o QuickSort para diferentes tamanhos de vetor
    for (tamanhoVetor = 100; tamanhoVetor <= 1000; tamanhoVetor += incremento) {
        int* vetor = (int*)malloc(tamanhoVetor * sizeof(int));

        // Preencher o vetor com valores aleatórios
        for (int i = 0; i < tamanhoVetor; i++) {
            vetor[i] = rand();
        }

        clock_t inicio = clock(); // Marcar o tempo de início
        quickSort(vetor, 0, tamanhoVetor - 1);
        clock_t fim = clock(); // Marcar o tempo de fim

        double tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

        fprintf(arquivo, "%d %lf\n", tamanhoVetor, tempoExecucao);

        free(vetor);
    }

    fclose(arquivo);

    printf("Dados salvos em quick_a_time.txt.\n");

    return 0;
}
