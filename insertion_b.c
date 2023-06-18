#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para realizar o Insertion Sort
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int size, i;
    FILE *file;
    clock_t start, end;
    double cpu_time_used;

    // Abre o arquivo para escrita
    file = fopen("insertion_b_time.txt", "w");

    // Loop para diferentes tamanhos de vetor
    for (size = 100; size <= 10000; size += 100) {
        int *arr = (int *)malloc(size * sizeof(int));

        // Melhor caso: vetor já ordenado
        for (i = 0; i < size; i++) {
            arr[i] = i + 1;
        }

        start = clock();
        insertionSort(arr, size);
        end = clock();

        // Calcula o tempo de execução em segundos
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Escreve os dados no arquivo
        fprintf(file, "%d %f\n", size, cpu_time_used);

        free(arr);
    }

    // Fecha o arquivo
    fclose(file);

    return 0;
}
