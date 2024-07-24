#include "pilha.h"

pilha_t *inicializa(int tamanho) {
    pilha_t *pilha;

    if (!(pilha = (pilha_t *) malloc(sizeof(pilha_t)))) {
        printf("Erro ao alocar memoria para a pilha\n");
        return NULL;
    }

    if (!(pilha->valor = (int *) malloc (tamanho * sizeof(int)))) {
        printf("Erro ao alocar memoria para a pilha-> valor\n");   
        return NULL;
    }

    pilha->topo = 0;
    pilha->tamanho = tamanho;

    return pilha;
}

unsigned char ehVazio(pilha_t *pilha) {
    return pilha->topo == 0;
}

unsigned char ehCheio(pilha_t *pilha) {
    return pilha->topo == pilha->tamanho - 1;
}

void push(pilha_t *pilha, int valor) {
    if (ehCheio(pilha)) {
        // printf("A pilha está cheia!\n");
        return;
    }
    pilha->valor[++pilha->topo] = valor;
    return;
}

int pop(pilha_t *pilha) {
    if (ehVazio(pilha)) {
        // printf("A pilha está vazia!\n");
        return -1;
    }
    return pilha->valor[pilha->topo--];
}

void destroi (pilha_t *pilha) {
    free(pilha->valor);
    pilha->topo = 0;
    pilha->tamanho = 0;

    free(pilha);

    return;
}