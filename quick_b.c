#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void generateBestCase(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
}

int main() {
    FILE *file;
    file = fopen("quick_b_time.txt", "w");
    
    if (file == NULL) {
        printf("Falha ao abrir o arquivo.");
        return 1;
    }
    
    int start_size = 100;
    int end_size = 10000;
    int increment = 100;
    
    for (int size = start_size; size <= end_size; size += increment) {
        int* arr = (int*)malloc(size * sizeof(int));
        
        generateBestCase(arr, size);
        
        clock_t start = clock();
        
        quickSort(arr, 0, size - 1);
        
        clock_t end = clock();
        double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        
        fprintf(file, "%d %lf\n", size, elapsed_time);
        
        free(arr);
    }
    
    fclose(file);
    
    printf("Dados salvos em quick_b_time.txt.\n");

    return 0;
}
