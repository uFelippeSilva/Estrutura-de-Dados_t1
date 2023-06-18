#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Função para gerar um vetor ordenado em ordem decrescente de tamanho "size"
void generateDescendingArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
}

// Função para realizar o Insertion Sort em um vetor de tamanho "size"
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Função para medir o tempo de execução em microssegundos
long long measureTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((long long)tv.tv_sec) * 1000000 + tv.tv_usec;
}

int main() {
    FILE *file = fopen("insertion_w_time.txt", "w");  // Abre o arquivo para escrita
    
    // Loop para diferentes tamanhos de vetor
    for (int size = 100; size <= 10000; size += 100) {
        int *arr = (int *)malloc(size * sizeof(int));
        
        generateDescendingArray(arr, size);  // Gera um vetor ordenado em ordem decrescente
        
        long long start_time = measureTime();  // Marca o tempo de início
        
        insertionSort(arr, size);  // Executa o Insertion Sort
        
        long long end_time = measureTime();  // Marca o tempo de fim
        long long execution_time = end_time - start_time;  // Calcula o tempo de execução
        
        fprintf(file, "%d %lld\n", size, execution_time);  // Escreve no arquivo de texto
        
        free(arr);  // Libera a memória alocada para o vetor
    }
    
    fclose(file);  // Fecha o arquivo
    
    return 0;
}
