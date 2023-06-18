#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

long long getCurrentTime() {
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

void generateDescendingArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
}

int main() {
    FILE* file = fopen("quick_w_time.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    fprintf(file, "# Tamanho_do_vetor Pior_tempo_de_execucao\n");

    int vectorSize;
    for (vectorSize = 100; vectorSize <= 10000; vectorSize += 100) {
        int* arr = (int*)malloc(vectorSize * sizeof(int));

        long long worstTime = 0;
        int numIterations = 100;  // Número de iterações do QuickSort no mesmo vetor

        for (int i = 0; i < numIterations; i++) {
            generateDescendingArray(arr, vectorSize);

            long long startTime = getCurrentTime();
            quickSort(arr, 0, vectorSize - 1);
            long long endTime = getCurrentTime();

            long long iterationTime = (endTime - startTime);

            if (iterationTime > worstTime) {
                worstTime = iterationTime;
            }
        }

        fprintf(file, "%d %lld.%06lld\n", vectorSize, worstTime / numIterations, worstTime % 1000000);


        free(arr);
    }

    fclose(file);

    return 0;
}
