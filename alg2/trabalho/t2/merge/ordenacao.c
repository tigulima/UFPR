#include "ordenacao.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void getNome(char nome[]) {
    strncpy(nome, "Thiago Imai Lima", MAX_CHAR);
    // adicionada terminação manual para caso de overflow
    nome[MAX_CHAR - 1] = '\0';
}

uint32_t getGRR() { return 20204397; }

int* mergeSortMerge(int v[], int a, int m, int b) {
    int i, j, k;
    int *w;

    w = (int*)malloc((b - a + 1) * sizeof(int));

    i = a;
    j = m + 1;
    k = 0;

    while(i <= m && j <= b) {
        if(v[i] < v[j])
            w[k++] = v[i++];
        else
            w[k++] = v[j++];
    }

    while(i <= m)
        w[k++] = v[i++];

    while(j <= b)
        w[k++] = v[j++];

    for(i = a; i <= b; i++)
        v[i] = w[i - a];

    free(w);

    return v;
}

int mergeSortSort(int v[], int a, int b) {
    int m;

    if(a >= b)
        return 0;

    m = (a + b) / 2;

    mergeSortSort(v, a, m);
    mergeSortSort(v, m + 1, b); 
    mergeSortMerge(v, a, m, b);

    return 10;
}

void printVetor(int v[], size_t tam) {
    printf("Vetor:\n");
    for(int i = 0; i < tam; i++)
        printf("%i ",v[i]);
    printf("\n");
}

uint64_t mergeSort(int vetor[], size_t tam) {
    int result;

    result = mergeSortSort(vetor, 0, tam);
    printVetor(vetor, tam);

    return result;
}