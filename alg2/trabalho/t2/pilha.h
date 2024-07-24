#ifndef PILHA_H_
#define PILHA_H_

#include <stdlib.h>
#include <stdio.h>

#define TAM_MAX 100

typedef struct {
    int *valor;
    int topo;
    int tamanho;
} pilha_t;

pilha_t *inicializa(int tamanho);

unsigned char ehVazio(pilha_t *pilha);

unsigned char ehCheio(pilha_t *pilha);

void push(pilha_t *pilha, int valor);

int pop(pilha_t *pilha);

void destroi (pilha_t *pilha);

#endif 