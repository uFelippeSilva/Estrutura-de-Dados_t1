#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para preencher o array com valores incrementados de 10 em 10
void preencherArray(int array[], int tamanho) {
    int valor = 100;
    for (int i = 0; i < tamanho; i++) {
        array[i] = valor;
        valor += 10;
    }
}

// Função para realizar o Distribution Sort
void distributionSort(int array[], int tamanho) {
    // Encontrar o valor máximo no array
    int max = array[0];
    for (int i = 1; i < tamanho; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    // Criar um array auxiliar para contar as ocorrências de cada valor
    int *count = (int *)malloc((max + 1) * sizeof(int));
    if (count == NULL) {
        printf("Erro na alocação de memória.\n");
        return;
    }

    // Inicializar o array count com zeros
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    // Contar as ocorrências de cada valor
    for (int i = 0; i < tamanho; i++) {
        count[array[i]]++;
    }

    // Atualizar o array original com os valores ordenados
    int j = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i] > 0) {
            array[j] = i;
            j++;
            count[i]--;
        }
    }

    free(count);
}

int main() {
    int tamanho = 100; // Tamanho inicial do array
    int incremento = 10;
    int* array = NULL;
    int numExecucoes = 100;

    // Abrir o arquivo para salvar os resultados
    FILE *arquivo = fopen("distribution_a_time.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo 'distribution_a_time.txt'.\n");
        return 1;
    }

    for (int k = 0; k < 1000; k++) {
        // Alocar memória para o array
        array = (int*)malloc(tamanho * sizeof(int));
        if (array == NULL) {
            printf("Erro na alocação de memória.\n");
            return 1;
        }

        // Calcular o tamanho da memória alocada em bytes
        size_t tamanhoMemoria = tamanho * sizeof(int);

        // Executar o algoritmo de ordenação várias vezes para calcular o tempo médio
        clock_t tempoTotal = 0;

        for (int i = 0; i < numExecucoes; i++) {
            preencherArray(array, tamanho);

            // Medir o tempo de execução
            clock_t inicio = clock();
            distributionSort(array, tamanho);
            clock_t fim = clock();

            // Calcular o tempo de execução em microssegundos
            double tempoExecucao = (double)(fim - inicio) / (CLOCKS_PER_SEC / 1000000.0);

            // Somar o tempo de execução
            tempoTotal += tempoExecucao;
        }

        // Calcular o tempo médio em microssegundos
        double tempoMedio = (double)tempoTotal / numExecucoes;

        // Salvar os resultados no arquivo
        fprintf(arquivo, "# Tamanho do vetor: %d\n", tamanho);
        fprintf(arquivo, "# Tamanho da memória alocada: %zu bytes\n", tamanhoMemoria);
        fprintf(arquivo, "%d %.6f\n", tamanho, tempoMedio);

        // Liberar a memória do array
        free(array);

        // Aumentar o tamanho do array
        tamanho += incremento;

        if (tamanho > 10000) {
            break;
        }
    }

    // Fechar o arquivo
    fclose(arquivo);

    return 0;
}
