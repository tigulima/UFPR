#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liblef.h"

/*
 * Cria uma LEF vazia
 */
lef_t *cria_lef()
{
    lef_t *l;
    if (!(l = malloc(sizeof(lef_t))))
        return NULL;

    l->Primeiro = NULL;

    return l;
}

/*
 * Destroi a LEF e retorna NULL.
 */
lef_t *destroi_lef(lef_t *l)
{
    free(l);
    l = NULL;

    return NULL;
}

/*
 * Adiciona um evento na primeira posicao da LEF. Uma nova copia
 * da estrutura evento sera feita.
 * Retorna 1 em caso de sucesso, 0 caso contrario.
 */
int adiciona_inicio_lef(lef_t *l, evento_t *evento)
{
    nodo_lef_t *nodo, *nodo_cpy;

    if (!(nodo = malloc(sizeof(nodo_lef_t))))
        return 0;

    if (!(nodo_cpy = malloc(sizeof(nodo_lef_t))))
        return 0;

    nodo->evento = evento;
    nodo->prox = NULL;

    l->Primeiro = nodo;

    memcpy(nodo_cpy, nodo, sizeof(nodo_lef_t));

    return 1;
}

/*
 * Adiciona um evento de acordo com o valor evento->tempo na LEF.
 * Uma nova copia da estrutura evento sera feita
 * Retorna 1 em caso de sucesso, 0 caso contrario.
 */
int adiciona_ordem_lef(lef_t *l, evento_t *evento)
{
    nodo_lef_t *nodo, *idx;
    evento_t *copia_evento; /* Cria uma copia do evento */

    if (!(copia_evento = malloc(sizeof(evento_t))))
        return 0;

    memcpy(copia_evento, evento, sizeof(evento_t));

    if (l->Primeiro == NULL)
    {
        adiciona_inicio_lef(l, evento);
        return 1;
    }

    if (!(nodo = malloc(sizeof(nodo_lef_t))))
        return 0;

    nodo->evento = evento;
    nodo->prox = NULL;

    idx = l->Primeiro;

    int pos;
    for (pos = 0; idx->evento->tempo < evento->tempo && idx->prox != NULL; pos++)
        idx = idx->prox;

    if (pos == 0)
    {
        nodo->prox = l->Primeiro;
        l->Primeiro = nodo;

        return 1;
    }

    idx = l->Primeiro;

    int i;
    for (i = 1; i < pos; i++)
        idx = idx->prox;

    nodo->prox = idx->prox;
    idx->prox = nodo;

    return 1;
}

/*
 * Retorna e retira o primeiro evento da LEF.
 * A responsabilidade por desalocar
 * a memoria associada eh de quem chama essa funcao.
 */
evento_t *obtem_primeiro_lef(lef_t *l)
{
    evento_t *evento;

    if (l->Primeiro == NULL)
        return NULL;

    evento = l->Primeiro->evento;
    l->Primeiro = l->Primeiro->prox;

    return evento;
}
