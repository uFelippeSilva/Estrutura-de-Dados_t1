#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int arr[], int n) {
    int i, j, minIndex, temp;
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        if (minIndex != i) {
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

int main() {
    int minSize = 100;
    int maxSize = 10000;
    int increment = 100;
    int numIterations = (maxSize - minSize) / increment + 1;
    int dataSize, i, j;
    clock_t start, end;
    double total_time;
    
    FILE *file = fopen("selection_a_time.txt", "w");
    if (file == NULL) {
        printf("Erro ao criar o arquivo.");
        return 1;
    }
    
    fprintf(file, "# TamanhoVetor TempoMedio\n");

    for (dataSize = minSize; dataSize <= maxSize; dataSize += increment) {
        int *arr = (int *)malloc(dataSize * sizeof(int));
        double average_time = 0.0;
        
        for (i = 0; i < numIterations; i++) {
            // Inicializa o vetor com valores aleatórios
            for (j = 0; j < dataSize; j++) {
                arr[j] = rand() % 1000;
            }

            // Executa o algoritmo e mede o tempo
            start = clock();
            selectionSort(arr, dataSize);
            end = clock();
            total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
            
            average_time += total_time;
        }
        
        average_time /= numIterations;
        
        fprintf(file, "%d %lf\n", dataSize, average_time);
        
        free(arr);
    }
    
    fclose(file);
    
    printf("Dados salvos no arquivo 'selection_a_time.txt'.\n");

    return 0;
}
