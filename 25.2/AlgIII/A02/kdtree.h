#ifndef KDTREE_H
#define KDTREE_H

#include <stdlib.h>
#include <stdio.h>

struct kd_nodo {
    float *ponto;
    int classe;
    struct kd_nodo *esq;
    struct kd_nodo *dir;
};

struct kdtree {
    struct kd_nodo *raiz;
    int k;
};

struct kdtree* criarKdtree();
struct kd_nodo* buscar(struct kdtree *arvore, float *ponto);
struct kd_nodo** zVizinhos(struct kdtree *arvore, float *ponto, int z, int *num_encontrados);
void matarProgramaFaltaMemoria();
void imprimirEmLargura(struct kdtree *arvore);
void liberarKdtree(struct kdtree *arvore);

#endif // KDTREE_H