#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int size) {
    int i, key, j;
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

double calculateAverageTime(int arr[], int size) {
    clock_t start, end;
    start = clock();

    insertionSort(arr, size);

    end = clock();
    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000000;
    return time_taken;
}

int main() {
    FILE* file = fopen("insertion_a_time.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(file, "# Tamanho_do_vetor Tempo_de_execucao\n");

    for (int size = 100; size <= 10000; size += 100) {
        int* arr = (int*)malloc(size * sizeof(int));
        if (arr == NULL) {
            printf("Erro ao alocar memória.\n");
            return 1;
        }

        for (int i = 0; i < size; i++) {
            arr[i] = rand();
        }

        double average_time = calculateAverageTime(arr, size);
        fprintf(file, "%d %lf\n", size, average_time);

        free(arr);
    }

    fclose(file);
    printf("Dados salvos com sucesso no arquivo 'insertion_a_time.txt'.\n");

    return 0;
}
