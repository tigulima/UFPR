#include "ordenacao.h"
#include "pilha.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void getNome(char nome[]) {
    strncpy(nome, "Thiago Imai Lima", MAX_CHAR);
    // adicionada terminação manual para caso de overflow
    nome[MAX_CHAR - 1] = '\0';
}

uint32_t getGRR() { return 20204397; }

// CÓDIGO DE APOIO

void imprimeVetor(int v[], size_t tam) {
    printf("Vetor: ");
    for(int i = 0; i < tam; i++)
        printf("%i ",v[i]);
    printf("\n");
}

// MERGE SORT

void copiar(int v[], int w[], int a, int b) {
    for(int i = 0; i <= b - a; i++)
        v[a + i] = w[i];

    return;
}

int* merge(int v[], int a, int m, int b, int *numComp) {
    // Merge Sort recursivo
    int i, j, k;
    int *w;

    // Aloca vetor auxiliar
    w = (int*)malloc((b - a + 1) * sizeof(int));

    // Inicializa variáveis
    i = a;
    j = m + 1;
    k = 0;

    while (k <= b - a) {
        if (j > b || (i <= m && v[i] <= v[j])) {
            w[k] = v[i];
            i++;
        } else {
            w[k] = v[j];
            j++;
        }

        k++;
        *numComp += 1;
    }

    copiar(v, w, a, b);
    
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

int particionar(int v[], int a, int b, int *numComp) {
    int pivo, m;

    pivo = v[b];
    m = a;

    for (int i = a; i < b; i++) {
        if(v[i] <= pivo) {
            troca(v, i, m);
            m++;
        }

        *numComp += 1;
    }

    troca(v, m, b);

    return m;
}

int quickSortRecursivo(int v[], int a, int b, int *numComp) {
    int m;

    if(a >= b)
        return 0;

    m = particionar(v, a, b, numComp);

    quickSortRecursivo(v, a, m - 1, numComp);
    quickSortRecursivo(v, m + 1, b, numComp);

    return *numComp;
}

void quickSortIterativo(int v[], int a, int b, int *numComp) {
    int m;
    pilha_t *pilha = NULL;

    pilha = inicializa(b - a + 1);

    push(pilha, a);
    push(pilha, b);
    while(!ehVazio(pilha)) {
        b = pop(pilha);
        a = pop(pilha);

        if (a < b) {
            m = particionar(v, a, b, numComp);
            push(pilha, a);
            push(pilha, m - 1);
            push(pilha, m + 1);
            push(pilha, b);
        }
    }

    destroi(pilha);

    return;
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

int maxheapfySR(int v[], int i, int tam, int *numComp) {

    while(i < tam) {
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        int maior = i;

        if(esq < tam && v[esq] > v[maior])
            maior = esq;

        if(dir < tam && v[dir] > v[maior])
            maior = dir;

        if(maior != i) {
            troca(v, i, maior);
            i = maior;
        } else {
            break;
        }

        *numComp += 1;
    }

    return *numComp;
}

int buildMaxHeap(int v[], int tam, int *numComp) {
    for(int i = tam / 2 - 1; i >= 0; i--)
        maxheapfy(v, i, tam, numComp);

    return *numComp;
}

int heapSortRecursivo(int v[], int tam, int *numComp) {
    buildMaxHeap(v, tam, numComp);

    for(int i = tam - 1; i > 0; i--) {
        troca(v, 0, i);
        maxheapfy(v, 0, i, numComp);
    }

    return *numComp;
}

//// TEMPLATE ////

uint64_t mergeSort(int vetor[], size_t tam) {
    int numComp = 0;

    mergeSortRecursivo(vetor, 0, tam - 1, &numComp);
    // imprimeVetor(vetor, tam);

    return numComp;
}

uint64_t quickSort(int vetor[], size_t tam) {
    int numComp = 0;

    quickSortRecursivo(vetor, 0, tam - 1, &numComp);
    // imprimeVetor(vetor, tam);

    return numComp;
}

uint64_t heapSort(int vetor[], size_t tam) {
    int numComp = 0;

    heapSortRecursivo(vetor, tam, &numComp);
    // imprimeVetor(vetor, tam);

    return numComp;
}

uint64_t mergeSortSR(int vetor[], size_t tam) {
    // Merger sort iterativo

    int numComp = 0;

    for(int i = 1; i < tam; i *= 2) {
        for(int j = 0; j < tam - 1; j += 2 * i) {
            int a = j;
            int m = j + i - 1;
            int b = j + 2 * i - 1;

            if(b >= tam)
                b = tam - 1;

            merge(vetor, a, m, b, &numComp);
        }
    }

    // imprimeVetor(vetor, tam);

    return numComp;
}

uint64_t quickSortSR(int vetor[], size_t tam) {
    // Quick sort iterativo

    int numComp = 0;

    quickSortIterativo(vetor, 0, tam - 1, &numComp);

    // imprimeVetor(vetor, tam);

    return numComp;
}

uint64_t heapSortSR(int vetor[], size_t tam) {
    // Heap sort iterativo

    int numComp = 0;

    buildMaxHeap(vetor, tam, &numComp);

    for(int i = tam - 1; i > 0; i--) {
        troca(vetor, 0, i);
        maxheapfy(vetor, 0, i, &numComp);
    }

    // imprimeVetor(vetor, tam);

    return numComp;
}