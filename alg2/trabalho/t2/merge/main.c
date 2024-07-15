#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ordenacao.h"

int main() {
    char nome[MAX_CHAR];
    int numComp;

    int tamVetor = 8;
    int* vetor = (int*)malloc(tamVetor * sizeof(int));
    if (vetor == NULL) {
        printf("Falha fatal. Impossível alocar memoria.");
        return 1;
    }

    vetor[0] = 1;
    vetor[1] = 10;
    vetor[2] = 12;
    vetor[3] = 43;
    vetor[4] = 21;
    vetor[5] = 2;
    vetor[6] = 87;
    vetor[7] = 4;

    getNome(nome);
    printf("Trabalho de %s\n", nome);
    printf("GRR %u\n", getGRR());

    numComp = mergeSort(vetor, tamVetor);
    printf("NumComp: %d\n", numComp);

    free(vetor);

    return 0;
}
