#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void merge(int vetor[], int comeco, int meio, int fim) {
    int com1 = comeco, com2 = meio + 1, comAux = 0, tam = fim - comeco + 1;
    int *vetAux;
    vetAux = (int*)malloc(tam * sizeof(int));

    while(com1 <= meio && com2 <= fim) {
        if(vetor[com1] < vetor[com2]) {
            vetAux[comAux] = vetor[com1];
            com1++;
        } else {
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        comAux++;
    }

    while(com1 <= meio) {
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++) {
        vetor[comAux] = vetAux[comAux - comeco];
    }

    free(vetAux);
}

void mergeSort(int vetor[], int comeco, int fim) {
    if (comeco < fim) {
        int meio = (fim + comeco) / 2;

        mergeSort(vetor, comeco, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, comeco, meio, fim);
    }
}

int main() {
    LARGE_INTEGER frequency, start, end;
    FILE *file;
    char filename[] = "merge_a_time.txt";
    int i, numExecutions = 10;
    int inicio = 100;
    int fim = 10000;
    int incremento = 10;
    int tamanhoArray;
    int *vetor;

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(file, "# Tamanho_do_Vetor Tempo_de_Execucao\n");

    QueryPerformanceFrequency(&frequency);

    for (int tamanho = inicio; tamanho <= fim; tamanho += incremento) {
        tamanhoArray = tamanho;
        vetor = (int*)malloc(tamanhoArray * sizeof(int));

        srand(GetTickCount());
        for (int j = 0; j < tamanhoArray; j++) {
            vetor[j] = rand();
        }

        unsigned int t_total = 0;

        for (i = 0; i < numExecutions; i++) {
            QueryPerformanceCounter(&start);
            mergeSort(vetor, 0, tamanhoArray - 1);
            QueryPerformanceCounter(&end);

            unsigned int t = (end.QuadPart - start.QuadPart) * 1000000 / frequency.QuadPart;
            t_total += t;
        }

        unsigned int t_average = t_total / numExecutions;

        fprintf(file, "%d %u\n", tamanhoArray, t_average);

        free(vetor);
    }

    fclose(file);

    printf("Tempos de execucao calculados e salvos em '%s'.\n", filename);

    return 0;
}
