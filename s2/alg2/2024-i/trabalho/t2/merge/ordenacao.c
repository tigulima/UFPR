#include "ordenacao.h"

#include <string.h>
#include <stdio.h>

void getNome(char nome[]) {
    strncpy(nome, "Thiago Imai Lima", MAX_CHAR);
    // adicionada terminação manual para caso de overflow
    nome[MAX_CHAR - 1] = '\0';
}

uint32_t getGRR() { return 20204397; }

int meio(int a, int b) {
    return (b - a)/2;
}

int mergeSortSort(int v[], int a, int b) {
    int m;

    m = meio(a, b);

    // mergeSortSort(v, a, m);
    // mergeSortSort(v, m+1, b);

    return v[1];
}

uint64_t mergeSort(int vetor[], size_t tam) {
    int result;

    result = mergeSortSort(vetor, 0, tam);

    return result;
}