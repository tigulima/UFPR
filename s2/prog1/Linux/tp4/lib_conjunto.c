#include <stdio.h>
#include <stdlib.h>
#include "lib_conjunto.h"

/*
 * TAD conjunto
 * Autores:
 *    Andre Ricardo Abed Gregio
 *    Fabiano Silva
 *    Luis Carlos Erpen de Bona
 *    Marcos Alexandre Castilho
 *
 * Versao 1.0.0 de 10/11/2021
 * Versao 1.0.1 de 16/08/2022
 * Versao 1.1.0 de 17/11/2022
 */

struct conjunto
{
    int max;  /* tamanho maximo do vetor atualmente alocado     */
    int card; /* cardinalidade, isto eh, tamanho usado ate max  */
    int ptr;  /* ponteiro para algum indice do vetor (iterador) */
    int *v;   /* vetor de inteiros com no maximo max elementos  */
};
typedef struct conjunto conjunto_t;

/*
 * Cria um conjunto vazio e o retorna, se falhar retorna NULL.
 * max eh o tamanho maximo do conjunto, isto eh, o tamanho maximo do vetor
 */
conjunto_t *cria_cjt(int max)
{
    conjunto_t *c;

    if (!(c = malloc(sizeof(conjunto_t))))
        return NULL;

    c->max = max;
    c->card = 0;
    c->ptr = 0;

    if (!(c->v = malloc(sizeof(int) * max)))
        return NULL;

    return c;
}

/*
 * Remove todos os elementos do conjunto, libera espaco e devolve NULL.
 */
conjunto_t *destroi_cjt(conjunto_t *c)
{
    free(c->v);
    c->v = NULL;

    free(c);

    return NULL;
}

/*
 * Retorna 1 se o conjunto esta vazio e 0 caso contrario.
 */
int vazio_cjt(conjunto_t *c)
{
    return cardinalidade_cjt(c) == 0;
}

/*
 * Retorna a cardinalidade do conjunto, isto eh, o numero de elementos presentes nele.
 */
int cardinalidade_cjt(conjunto_t *c)
{
    return c->card;
}

/*
 * Insere o elemento no conjunto, garante que nao existam repeticoes.
 * Retorna 1 se a operacao foi bem sucedida. Se tentar inserir elemento existente,
 * nao faz nada e retorna 1 tambem. Retorna 0 em caso de falha por falta de espaco.
 */
int insere_cjt(conjunto_t *c, int elemento)
{
    if (cardinalidade_cjt(c) == c->max)
        return 0;

    if (pertence_cjt(c, elemento))
        return 1;

    c->card++;
    c->v[c->card] = elemento;

    return 1;
}

/*
 * Remove o elemento 'elemento' do conjunto caso ele exista.
 * Retorna 1 se a operacao foi bem sucedida e 0 se o elemento nao existe.
 */
int retira_cjt(conjunto_t *c, int elemento)
{
    int i;
    for (i = 0; i < c->card && c->v[i] != elemento; i++)
    {
    }

    if (i == c->card)
        return 0;

    for (i; i < c->card; i++)
        c->v[i] = c->v[i + 1];

    free(c->v[i + 1]);
    c->v[i + 1] = NULL;

    return 1;
}

/*
 * Retorna 1 se o elemento pertence ao conjunto e 0 caso contrario.
 */
int pertence_cjt(conjunto_t *c, int elemento)
{
    int i;
    for (i = 0; i < c->card && c->v[i] != elemento; i++)
    {
    }

    if (i == c->card)
        return 1;

    return 0;
}

/*
 * Retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario.
 */
int contido_cjt(conjunto_t *c1, conjunto_t *c2)
{
    int i, maior_conj;

    if (c1->card >= c2->card)
        maior_conj = c1->card;
    else
        maior_conj = c2->card;

    for (i = 0; i < maior_conj && c1->v[i] == c2->v[i]; i++)
    {
    }

    if (i == c1->card)
        return 1;

    return 0;
}

/*
 * Retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario.
 */
int sao_iguais_cjt(conjunto_t *c1, conjunto_t *c2)
{
    int i;

    if (c1->card != c2->card)
        return 0;

    for (i = 0; i < c1->card && c1->v[i] == c2->v[i]; i++)
    {
    }

    if (i == c1->card)
        return 1;

    return 0;
}

/*
 * Cria e retorna o conjunto diferenca entre c1 e c2, nesta ordem.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t *diferenca_cjt(conjunto_t *c1, conjunto_t *c2);

/*
 * Cria e retorna o conjunto interseccao entre os conjuntos c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t *interseccao_cjt(conjunto_t *c1, conjunto_t *c2);

/*
 * Cria e retorna o conjunto uniao entre os conjunto c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t *uniao_cjt(conjunto_t *c1, conjunto_t *c2);

/*
 * Cria e retorna uma copia do conjunto c e NULL em caso de falha.
 */
conjunto_t *copia_cjt(conjunto_t *c);

/*
 * Cria e retorna um subconjunto com elementos aleatorios do conjunto c.
 * Se o conjunto for vazio, retorna um subconjunto vazio.
 * Se n >= cardinalidade (c) entao retorna o proprio conjunto c.
 * Supoe que a funcao srand () tenha sido chamada antes.
 */
conjunto_t *cria_subcjt_cjt(conjunto_t *c, int n);

/*
 * Imprime os elementos do conjunto sempre em ordem crescente,
 * mesmo que a estrutura interna nao garanta isso.
 * Na impressao os elementos sao separados por um unico espaco
 * em branco entre os elementos, sendo que apos o ultimo nao
 * deve haver espacos em branco. Ao final imprime um \n.
 */
void imprime_cjt(conjunto_t *c)
{
    int i;
    for (i = 0; i < c->card; i++)
        printf("%d ", c->v[i]);
}

/*
 * As funcoes abaixo implementam um iterador que vao permitir
 * percorrer os elementos do conjunto.
 * O ponteiro ptr da struct (iterador) pode ser inicializado para apontar
 * para o primeiro elemento e incrementado ate' o ultimo elemento
 * do conjunto.
 */

/*
 * Inicializa ptr usado na funcao incrementa_iterador
 */
void inicia_iterador_cjt(conjunto_t *c);

/*
 * Devolve no parametro ret_iterador o elemento apontado e incrementa o iterador.
 * A funcao retorna 0 caso o iterador ultrapasse o ultimo elemento, ou retorna
 * 1 caso o iterador aponte para um elemento valido (dentro do conjunto).
 */
int incrementa_iterador_cjt(conjunto_t *c, int *ret_iterador);

/*
 * Escolhe um elemento qualquer do conjunto para ser removido, o remove e
 * o retorna.
 * Nao faz teste se conjunto eh vazio, deixa para main fazer isso
 */
int retira_um_elemento_cjt(conjunto_t *c);
