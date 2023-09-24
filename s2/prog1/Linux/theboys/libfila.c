#include <stdio.h>
#include <stdlib.h>
#include "libfila.h"

/* Cria uma fila vazia e a retorna, se falhar retorna NULL. */
fila_t *cria_fila()
{
    fila_t *f;

    if (!(f = malloc(sizeof(fila_t))))
        return NULL;

    f->ini = NULL;
    f->tamanho = 0;

    return f;
}

/* Remove todos os elementos da fila, libera espaco e devolve NULL. */
fila_t *destroi_fila(fila_t *f)
{
    nodo_f_t *aux;

    aux = f->ini->prox;

    while (f->ini->prox != NULL)
    {
        free(f->ini);
        f->ini = aux;
        aux = f->ini->prox;
    }
    free(f->ini);

    free(f);
    f = NULL;

    return NULL;
}

/* Retorna 1 se a fila esta vazia e 0 caso contrario. */
int vazia_fila(fila_t *f)
{
    return f->tamanho == 0;
}

/* Retorna o numero de ementos da fila. */
int tamanho_fila(fila_t *f)
{
    return f->tamanho;
}

/* Insere o elemento no final da fila (politica FIFO).
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario. */
int insere_fila(fila_t *f, int elemento)
{
    nodo_f_t *nodo;

    if (!(nodo = malloc(sizeof(nodo_f_t))))
        return 0;

    if (f->ini == NULL)
        f->ini = nodo;
    else
        f->fim->prox = nodo;

    f->fim = nodo;

    f->fim->elem = elemento;
    f->fim->prox = NULL;

    f->tamanho++;

    return 1;
}

/* Remove o elemento do inicio da fila (politica FIFO) e o retorna
 * no parametro *elemento. Retorna 1 se a operacao foi bem sucedida
 * e 0 caso contrario. */
int retira_fila(fila_t *f, int *elemento)
{
    nodo_f_t *aux;

    if (f->ini == NULL)
        return 0;

    *elemento = f->ini->elem;
    aux = f->ini->prox;

    free(f->ini);
    f->ini = NULL;

    f->ini = aux;
    f->tamanho--;

    return 1;
}

/* para depuracao */
void imprime_fila(fila_t *f)
{
    nodo_f_t *aux;

    aux = f->ini;

    while (aux->prox != NULL)
    {
        printf("%d ", aux->elem);
        aux = aux->prox;
    }
    printf("%d ", aux->elem);
}