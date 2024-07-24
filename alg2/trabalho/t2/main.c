#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ordenacao.h"

int *iniciaVetor(int tam) {
    int *vetor = (int*)malloc(tam * sizeof(int));
    if (vetor == NULL) {
        printf("Falha fatal. Impossível alocar memoria.");
        return NULL;
    }

    return vetor;
}

void preencheVetor(int vetor[], int tam) {
    srand(time(NULL));

    for (int i = 0; i < tam; i++) {
        vetor[i] = rand() % 100;
    }
}

void copiaVetor(int v[], int w[], int tam) {
    for (int i = 0; i < tam; i++) {
        w[i] = v[i];
    }
}

int main() {
    char nome[MAX_CHAR];
    int numComp, tamVetor;

    getNome(nome);
    printf("Trabalho de %s\n", nome);
    printf("GRR %u\n\n", getGRR());
    printf("\n---\n\n");

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamVetor);
    printf("\n---\n\n");

    int *vetor = iniciaVetor(tamVetor);
    int *vetor_aux = iniciaVetor(tamVetor);

    preencheVetor(vetor, tamVetor);
    copiaVetor(vetor, vetor_aux, tamVetor);

    numComp = mergeSort(vetor, tamVetor);
    printf("MergeSort NumComp: %d\n\n", numComp);
    copiaVetor(vetor_aux, vetor, tamVetor);

    numComp = quickSort(vetor, tamVetor);
    printf("QuickSort NumComp: %d\n\n", numComp);
    copiaVetor(vetor_aux, vetor, tamVetor);
    
    numComp = heapSort(vetor, tamVetor);
    printf("HeapSort NumComp: %d\n\n", numComp);
    copiaVetor(vetor_aux, vetor, tamVetor);
    
    numComp = mergeSortSR(vetor, tamVetor);
    printf("MergeSort Iterativo NumComp: %d\n\n", numComp);
    copiaVetor(vetor_aux, vetor, tamVetor);
    
    numComp = quickSortSR(vetor, tamVetor);
    printf("QuickSort Iterativo NumComp: %d\n\n", numComp);
    copiaVetor(vetor_aux, vetor, tamVetor);
    
    numComp = heapSortSR(vetor, tamVetor);
    printf("HeapSort Iterativo NumComp: %d\n\n", numComp);
    copiaVetor(vetor_aux, vetor, tamVetor);

    free(vetor);
    free(vetor_aux);


    return 0;
}
