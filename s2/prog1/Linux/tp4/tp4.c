#include <stdio.h>
#include <stdlib.h>
#include "lib_conjunto.h"
#define MAX 100

int main()
{
    conjunto_t *c;

    cria_cjt(5);

    printf("%d", insere_cjt(c, 5));

    /* ler os herois e suas habilidades */

    /* ler a missao */

    /* ler as equipes de herois */

    /* a solucao eh encontrada se a missao esta contido na uniao das
     * habilidades de uma equipe, mas tomando-se aquela de menor tamanho. */

    /* libera toda a memoria alocada dinamicamente */

    return 0;
}
