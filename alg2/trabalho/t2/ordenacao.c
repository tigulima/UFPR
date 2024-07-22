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

//// CÓDIGO DE APOIO ////

void imprimeVetor(int v[], size_t tam) {
    printf("Vetor: ");
    for(int i = 0; i < tam; i++)
        printf("%i ",v[i]);
    printf("\n");
}

//// MERGE SORT ////

int* merge(int v[], int a, int m, int b, int *numComp) {
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

        *numComp += 1;
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

int mergeSortRecursivo(int v[], int a, int b, int *numComp) {
    int m;

    if(a >= b)
        return 0;

    m = (a + b) / 2;

    mergeSortRecursivo(v, a, m, numComp);
    mergeSortRecursivo(v, m + 1, b, numComp); 
    merge(v, a, m, b, numComp);

    return *numComp;
}

//// QUICK SORT ////

void troca(int v[], int i, int j) {
    int aux;

    aux = v[i];
    v[i] = v[j];
    v[j] = aux;

    return;
}

int quickSortRecursivo(int v[], int a, int b, int *numComp) {
    int i, j, pivo;

    i = a;
    j = b;
    pivo = v[(a + b) / 2];

    while(i <= j) {
        while(v[i] < pivo)
            i++;

        while(v[j] > pivo)
            j--;

        if(i <= j) {
            troca(v, i, j);
            i++;
            j--;
        }

        *numComp += 1;
    }

    if(a < j)
        quickSortRecursivo(v, a, j, numComp);

    if(i < b)
        quickSortRecursivo(v, i, b, numComp);

    return *numComp;
}

//// HEAP SORT ////

int maxheapfy(int v[], int i, int tam, int *numComp) {
    int esq, dir, maior;

    esq = 2 * i + 1;
    dir = 2 * i + 2;
    maior = i;

    if(esq < tam && v[esq] > v[maior])
        maior = esq;

    if(dir < tam && v[dir] > v[maior])
        maior = dir;

    if(maior != i) {
        troca(v, i, maior);
        maxheapfy(v, maior, tam, numComp);
    }

    *numComp += 1;

    return *numComp;
}

int buildMinHeap(int v[], int tam, int *numComp) {
    for(int i = tam / 2 - 1; i >= 0; i--)
        maxheapfy(v, i, tam, numComp);

    return *numComp;
}

int heapSortRecursivo(int v[], int tam, int *numComp) {
    buildMinHeap(v, tam, numComp);

    for(int i = tam - 1; i > 0; i--) {
        troca(v, 0, i);
        maxheapfy(v, 0, i, numComp);
    }

    return *numComp;
}

//// TEMPLATE ////

uint64_t mergeSort(int vetor[], size_t tam) {
    int *numComp = (int*)malloc(sizeof(int));

    *numComp = 0;

    mergeSortRecursivo(vetor, 0, tam - 1, numComp);
    imprimeVetor(vetor, tam);

    return *numComp;
}

uint64_t quickSort(int vetor[], size_t tam) {
    int *numComp = (int*)malloc(sizeof(int));

    *numComp = 0;

    quickSortRecursivo(vetor, 0, tam - 1, numComp);
    imprimeVetor(vetor, tam);

    return *numComp;
}

uint64_t heapSort(int vetor[], size_t tam) {
    int *numComp = (int*)malloc(sizeof(int));

    *numComp = 0;

    heapSortRecursivo(vetor, tam, numComp);
    imprimeVetor(vetor, tam);

    return *numComp;
}

uint64_t mergeSortSR(int vetor[], size_t tam) {
    // Merger sort iterativo

    int *numComp = (int*)malloc(sizeof(int));

    *numComp = 0;

    for(int i = 1; i < tam; i *= 2) {
        for(int j = 0; j < tam - 1; j += 2 * i) {
            int a = j;
            int m = j + i - 1;
            int b = j + 2 * i - 1;

            if(b >= tam)
                b = tam - 1;

            merge(vetor, a, m, b, numComp);
        }
    }

    imprimeVetor(vetor, tam);

    return *numComp;
}

uint64_t quickSortSR(int vetor[], size_t tam) {
    // Quick sort iterativo

    int *numComp = (int*)malloc(sizeof(int));

    *numComp = 0;

    int *pilha = (int*)malloc(tam * sizeof(int));

    int topo = -1;

    pilha[++topo] = 0;
    pilha[++topo] = tam - 1;

    while(topo >= 0) {
        int b = pilha[topo--];
        int a = pilha[topo--];

        int p = quickSortRecursivo(vetor, a, b, numComp);

        if(p - 1 > a) {
            pilha[++topo] = a;
            pilha[++topo] = p - 1;
        }

        if(p + 1 < b) {
            pilha[++topo] = p + 1;
            pilha[++topo] = b;
        }
    }

    imprimeVetor(vetor, tam);

    return *numComp;
}

uint64_t heapSortSR(int vetor[], size_t tam) {
    // Heap sort iterativo

    int *numComp = (int*)malloc(sizeof(int));

    *numComp = 0;

    buildMinHeap(vetor, tam, numComp);

    for(int i = tam - 1; i > 0; i--) {
        troca(vetor, 0, i);
        maxheapfy(vetor, 0, i, numComp);
    }

    imprimeVetor(vetor, tam);

    return *numComp;
}