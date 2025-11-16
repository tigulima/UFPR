#include "kdtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-6

void matarProgramaFaltaMemoria() {
    fprintf(stderr, "Falha ao alocar memoria.");
    exit(1);
};

// CRIAÇÃO

struct kdtree* criarArvore(unsigned int k) {
    struct kdtree *arvore = (struct kdtree *)malloc(sizeof(struct kdtree));
    if (arvore == NULL) {
        matarProgramaFaltaMemoria();
    }

    arvore->raiz = NULL;
    arvore->k = k;

    return arvore;
}

struct nodo* criarNodo(float *ponto, int classe, unsigned int k) {
    struct nodo *novoNodo = (struct nodo *)malloc(sizeof(struct nodo));
    if (novoNodo == NULL) {
        matarProgramaFaltaMemoria();
    }

    novoNodo->ponto = (float *)malloc(k * sizeof(float));
    if (novoNodo->ponto == NULL) {
        free(novoNodo);
        matarProgramaFaltaMemoria();
    }

    for (unsigned int i = 0; i < k; i++) {
        novoNodo->ponto[i] = ponto[i];
    }
    novoNodo->classe = classe;
    novoNodo->esq = NULL;
    novoNodo->dir = NULL;

    return novoNodo;
}

// INSERÇÃO

static struct nodo* inserirRecursivo(struct nodo *raiz, float *ponto, int classe, unsigned int k, unsigned int nivel) {
    if (raiz == NULL) {
        return criarNodo(ponto, classe, k);
    }

    unsigned int eixo = nivel % k;

    if (ponto[eixo] < raiz->ponto[eixo]) {
        raiz->esq = inserirRecursivo(raiz->esq, ponto, classe, k, nivel + 1);
    } else {
        raiz->dir = inserirRecursivo(raiz->dir, ponto, classe, k, nivel + 1);
    }

    return raiz;
}

struct kdtree* inserir(struct kdtree *arvore, float *ponto, int classe) {
    arvore->raiz = inserirRecursivo(arvore->raiz, ponto, classe, arvore->k, 0);
    return arvore;
}

// BUSCA

static int pontosIguais(float *p1, float *p2, unsigned int k) {
    for (unsigned int i = 0; i < k; i++) {
        if (fabs(p1[i] - p2[i]) > EPSILON) {
            return 0;
        }
    }
    return 1;
}

static struct nodo* buscarRecursivo(struct nodo *nodo, float *ponto, unsigned int k, unsigned int nivel) {
    if (nodo == NULL) {
        return NULL;
    }
    
    if (pontosIguais(nodo->ponto, ponto, k)) {
        return nodo;
    }

    unsigned int eixo = nivel % k;

    if (ponto[eixo] < nodo->ponto[eixo]) {
        return buscarRecursivo(nodo->esq, ponto, k, nivel + 1);
    } else {
        return buscarRecursivo(nodo->dir, ponto, k, nivel + 1);
    }
}

struct nodo* buscar(struct kdtree *arvore, float *ponto) {
    return buscarRecursivo(arvore->raiz, ponto, arvore->k, 0);
}

// ZPONTOS

static float calcularDistancia(float *p1, float *p2, unsigned int k) {
    float soma = 0.0;
    for (int i = 0; i < k; i++) {
        float diff = p1[i] - p2[i];
        soma += diff * diff;
    }
    return sqrt(soma);
}

static void insereCandidato(struct lista_vizinhos *lista, struct nodo *nodo, float dist, int pos) {
    lista->candidatos[pos].nodo = nodo;
    lista->candidatos[pos].dist = dist;
}

static int posicaoCandidato(struct lista_vizinhos *lista, float dist) {
    int i = 0;
    while (i < lista->tam && lista->candidatos[i].dist < dist) {
        i++;
    }
    return i;
}

static void abreEspacoNaLista(struct lista_vizinhos *lista, int pos) {
    for (int j = lista->z - 1; j > pos; j--) {
        lista->candidatos[j] = lista->candidatos[j - 1];
    }
}

static int insereListaVizinhos(struct lista_vizinhos *lista, struct nodo *nodo, float dist, unsigned int k) {
    int pos = posicaoCandidato(lista, dist);
    abreEspacoNaLista(lista, pos);
    insereCandidato(lista, nodo, dist, pos);

    if (lista->tam < lista->z) {
        lista->tam++;
    }

    return pos;
}

static void zVizinhosRecursivo(struct nodo *nodo, struct lista_vizinhos *lista, unsigned int k, unsigned int nivel) {
    if (nodo == NULL) {
        return;
    }

    float dist = calcularDistancia(lista->ponto_alvo, nodo->ponto, k);
    if (lista->tam < lista->z || dist < lista->candidatos[lista->tam - 1].dist) {
        insereListaVizinhos(lista, nodo, dist, k);
    }

    unsigned int eixo = nivel % k;

    if (lista->ponto_alvo[eixo] < nodo->ponto[eixo]) {
        zVizinhosRecursivo(nodo->esq, lista, k, nivel + 1);
        // se algum eixo for menor que a distância do último vizinho, verifica o outro lado
        if (lista->tam < lista->z || fabs(lista->ponto_alvo[eixo] - nodo->ponto[eixo]) < lista->candidatos[lista->tam - 1].dist) {
            zVizinhosRecursivo(nodo->dir, lista, k, nivel + 1);
        }
    } else {
        zVizinhosRecursivo(nodo->dir, lista, k, nivel + 1);
        if (lista->tam < lista->z || fabs(lista->ponto_alvo[eixo] - nodo->ponto[eixo]) < lista->candidatos[lista->tam - 1].dist) {
            zVizinhosRecursivo(nodo->esq, lista, k, nivel + 1);
        }
    }
}

struct lista_vizinhos* zVizinhos(struct kdtree *arvore, float *ponto, unsigned int z) {
    struct lista_vizinhos *lista;

    lista = (struct lista_vizinhos *)malloc(sizeof(struct lista_vizinhos));
    if (lista == NULL) {
        matarProgramaFaltaMemoria();
    }

    lista->candidatos = (struct candidato *)malloc(z * sizeof(struct candidato));
    if (lista->candidatos == NULL) {
        free(lista);
        matarProgramaFaltaMemoria();
    }

    lista->z = z;
    lista->tam = 0;
    lista->ponto_alvo = ponto;

    zVizinhosRecursivo(arvore->raiz, lista, arvore->k, 0);

    return lista;
}

static void destruirArvoreRecursivo(struct nodo *nodo) {
    if (nodo == NULL) {
        return;
    }
    destruirArvoreRecursivo(nodo->esq);
    destruirArvoreRecursivo(nodo->dir);
    free(nodo->ponto);
    free(nodo);
}

void destruirArvore(struct kdtree *arvore) {
    destruirArvoreRecursivo(arvore->raiz);
    free(arvore);
}