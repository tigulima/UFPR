#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ordenacao.h"

int main() {
    char nome[MAX_CHAR];
    int numComp;

    int tamVetor = 3;
    int* vetor = (int*)malloc(tamVetor * sizeof(int));
    if (vetor == NULL) {
        printf("Falha fatal. Impossível alocar memoria.");
        return 1;
    }

    vetor[0] = 1;
    vetor[1] = 10;
    vetor[2] = 12;

    getNome(nome);
    printf("Trabalho de %s\n", nome);
    printf("GRR %u\n", getGRR());

    numComp = mergeSort(vetor, 3);
    printf("NumComp: %d\n", numComp);
    numComp = quickSort(vetor, 3);
    printf("NumComp: %d\n", numComp);
    numComp = heapSort(vetor, 3);
    printf("NumComp: %d\n", numComp);
    numComp = mergeSortSR(vetor, 3);
    printf("NumComp: %d\n", numComp);
    numComp = quickSortSR(vetor, 3);
    printf("NumComp: %d\n", numComp);
    numComp = heapSortSR(vetor, 3);
    printf("NumComp: %d\n", numComp);

    free(vetor);

    return 0;
}
