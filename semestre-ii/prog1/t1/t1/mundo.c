#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "liblef.h"
#include "libfila.h"
#include "libconjunto.h"

#define HEROIS 50
#define LOCAIS 10
#define SKILLS 10
#define MISSOES 500
#define TAM_MUNDO 10
#define FIM_DO_MUNDO 34944

typedef struct heroi
{
    int id;
    int xp;
    int paciencia;
    int idade;
    conjunto_t *skills;
} heroi_t;

typedef struct local
{
    int id;
    int max;
    int coord[2];
    fila_t *fila;
    conjunto_t *publico;
    conjunto_t *u_skills;
} local_t;

typedef struct missao
{
    int id;
    conjunto_t *req;
} missao_t;

typedef struct mundo
{
    int temp;
    int tam;
    int n_herois;
    int n_locais;
    int herois[HEROIS];
    int locais[LOCAIS];
    conjunto_t *ch_skills;
} mundo_t;

/* Retorna um número aleatório entre x e y */
int ALEAT(x, y)
{
    return x + rand() % (y - x);
}

/* Retorna o maior número entre x e y */
int MAX(x, y)
{
    return x > y ? x : y;
}

/* Aloca a memória e insere valores para Heroi */
heroi_t *cria_heroi(conjunto_t *hab, int id)
{
    heroi_t *h;

    if (!(h = malloc(sizeof(heroi_t))))
        return NULL;

    h->id = id;
    h->xp = 0;
    h->paciencia = ALEAT(0, 100);
    h->idade = ALEAT(18, 100);
    h->skills = cria_subcjt_cjt(hab, ALEAT(2, 5));

    return h;
}

/* Aloca a memória e insere valores para Local */
local_t *cria_local(conjunto_t *pub, int id)
{
    local_t *l;

    if (!(l = malloc(sizeof(local_t))))
        return NULL;

    l->id = id;
    l->max = ALEAT(5, 30);
    l->coord[0] = ALEAT(0, TAM_MUNDO - 1);
    l->coord[1] = ALEAT(0, TAM_MUNDO - 1);
    l->fila = cria_fila();
    l->publico = pub;
    l->u_skills = cria_cjt(SKILLS);

    return l;
}

/* Aloca a memória e insere valores para Missao */
missao_t *cria_missao(conjunto_t *skills, int id)
{
    missao_t *m;

    if (!(m = malloc(sizeof(mundo_t))))
        return NULL;

    m->id = id;
    m->req = cria_subcjt_cjt(skills, ALEAT(1, SKILLS));

    return m;
}

/* Aloca a memória e insere valores para Mundo */
mundo_t *cria_mundo()
{
    mundo_t *m;

    if (!(m = malloc(sizeof(mundo_t))))
        return NULL;

    m->ch_skills = cria_cjt(SKILLS);

    return m;
}

/* Aloca a memória e insere valores para Evento */
evento_t *cria_evento(lef_t *l, int tempo, int tipo, int d1, int d2)
{
    if (tempo > FIM_DO_MUNDO)
        return NULL;

    evento_t *e;

    if (!(e = malloc(sizeof(evento_t))))
        return NULL;

    e->tempo = tempo;
    e->tipo = tipo;
    e->dado1 = d1;
    e->dado2 = d2;

    adiciona_ordem_lef(l, e);

    return e;
}

int main()
{
    lef_t *lef;

    mundo_t *mundo;
    evento_t *evento;

    heroi_t **herois;
    local_t **locais;
    missao_t **missoes;

    int i;

    srand(time(NULL));

    lef = cria_lef(); /* LEF = Lista de Eventos Futuros*/
    mundo = cria_mundo();

    /*///////////////
    // CRIA LOCAIS //
    ///////////////*/

    /* Aloca memória para a lista de locais */
    if (!(locais = malloc(sizeof(local_t) * LOCAIS)))
        return 0;

    /* Cria e adiciona local na lista de locais */
    for (i = 0; i < LOCAIS; i++)
        locais[i] = cria_local(cria_cjt(HEROIS), i);

    /*///////////////
    // CRIA SKILLS //
    ///////////////*/

    /* Cria a lista de habilidades presentes no mundo */
    for (i = 0; i < SKILLS; i++)
        insere_cjt(mundo->ch_skills, i);

    /*///////////////
    // CRIA HEROIS //
    ///////////////*/

    /* Aloca a mamória da lista de herois */
    if (!(herois = malloc(sizeof(heroi_t) * HEROIS)))
        return 0;

    /* Cria e adiciona heroi na lista de herois */
    for (i = 0; i < HEROIS; i++)
    {
        herois[i] = cria_heroi(mundo->ch_skills, i);

        /* Cria um evento de CHEGADA do heroi criado em um tempo
           e um local aleatórios e adiciona na LEF */
        cria_evento(lef, ALEAT(0, FIM_DO_MUNDO), 0, ALEAT(0, LOCAIS - 1), i);
    }

    /*////////////////
    // CRIA MISSOES //
    ////////////////*/

    /* Aloca a mamória da lista de missoes */
    if (!(missoes = malloc(sizeof(missao_t) * MISSOES)))
        return 0;

    /* Cria e adiciona missao na lista de missoes */
    for (i = 0; i < MISSOES; i++)
    {
        missoes[i] = cria_missao(mundo->ch_skills, i);
        /* Cria um evento de MISSAO em um tempo aleatorio */
        cria_evento(lef, ALEAT(0, FIM_DO_MUNDO), 2, 0, i);
    }

    /* Cria um evento do fim dos tempos */
    cria_evento(lef, FIM_DO_MUNDO, 3, 0, 0);

    /*/////////////
    // SIMULACAO //
    /////////////*/

    /* Retira o primeiro evento da LEF e guarda na variável evento */
    evento = obtem_primeiro_lef(lef);
    while (lef->Primeiro != NULL)
    {
        int t = evento->tempo;
        int lotacao = locais[evento->dado1]->max;

        printf("%6d: ", t); /* Escreve o tempo atual na tela */

        switch (evento->tipo)
        {

            /*/////////
            // CHEGA //
            /////////*/

        case 0:
        {
            int l_id = evento->dado1; /* Local ID */
            int h_id = evento->dado2; /* Heroi ID */

            /* Se existe espaço no local l_id, o heroi h_id entra */
            if (cardinalidade_cjt(locais[l_id]->publico) < lotacao)
            {
                int tpl = MAX(1, herois[h_id]->paciencia / 10 + ALEAT(-2, 6));

                /* Cria evento de saída do heroi para quando sua paciencia acabar */
                cria_evento(lef, t + tpl, 1, l_id, h_id);

                /* Atualiza publico e habilidades do local */
                insere_cjt(locais[l_id]->publico, h_id);
                locais[l_id]->u_skills = uniao_cjt(locais[l_id]->u_skills, herois[h_id]->skills);
            }
            /* Se não existe espaço no local l_id, o heroi h_id decide se vai entrar ou ficar na fila */
            else if (herois[h_id]->paciencia / 4 - tamanho_fila(locais[l_id]->fila) > 0)
                insere_fila(locais[l_id]->fila, h_id);
            else
            {
                cria_evento(lef, t, 1, l_id, h_id);
                int pub = cardinalidade_cjt(locais[l_id]->publico);

                /* Escreve mensagem de desistencia caso o heroi decida nao entrar na fila */
                printf("CHEGA HEROI %2d Local %d (%2d/%2d), DESISTE\n", h_id, l_id, pub, lotacao);
                break;
            }

            int pub = cardinalidade_cjt(locais[l_id]->publico); /* Quantidade de pessoas dentro do local */
            int tam_fila = tamanho_fila(locais[l_id]->fila);    /* Tamanho da fila para entrar no local */

            /* Escreve na tela a o evento de chegada com a quantidade de pessoas no local e/ou na fila */
            if (vazia_fila(locais[l_id]->fila))
                printf("CHEGA HEROI %2d Local %d (%2d/%2d), ENTRA\n", h_id, l_id, pub, lotacao);
            else
                printf("CHEGA HEROI %2d Local %d (%2d/%2d), FILA %d\n", h_id, l_id, lotacao, lotacao, tam_fila);

            break;
        }

            /*/////////
            // SAIDA //
            /////////*/

        case 1:
        {
            int l_id = evento->dado1; /* Local ID */
            int h_id = evento->dado2; /* Heroi ID */

            /* Verifica se havia alguem esperando na fila.
               Se alguem sai do local, a proxima pessoa
               esperando na fila, entra nesse local */
            if (!vazia_fila(locais[l_id]->fila))
            {
                /* Retira essa pessoa da fila */
                int h_id_fila;
                retira_fila(locais[l_id]->fila, &h_id_fila);
                retira_cjt(locais[l_id]->publico, h_id);

                /* Cria evento de entrada desse herói no lugar */
                cria_evento(lef, t, 0, l_id, h_id_fila);

                /* Escreve o evento de SAIDA */
                int pub = cardinalidade_cjt(locais[l_id]->publico);
                printf("SAIDA HEROI %2d Local %d (%2d/%2d), RETIRA FILA %d\n", h_id, l_id, pub, lotacao, h_id_fila);

                break;
            }

            /* Se não tem ninguem na fila: */

            /* Retira o heroi e suas habilidades do local */
            locais[l_id]->u_skills = diferenca_cjt(locais[l_id]->u_skills, herois[h_id]->skills);
            retira_cjt(locais[l_id]->publico, h_id);

            /* Escolhe para onde esse heroi vai agora */
            int l_id_destino = ALEAT(0, LOCAIS);

            /* Calcula a distancia entre o local atual e o proximo */
            int d = MAX(l_id, l_id_destino) == l_id ? (l_id - l_id_destino) : (l_id_destino - l_id);
            int v = 100 - MAX(0, herois[h_id]->idade - 40);
            int tdl = d / v;

            /* Cria evento de CHEGADA do hoeroi no tempo em que ele */
            /* demoraria para chegar no local */
            cria_evento(lef, t + tdl / 15, 0, l_id_destino, h_id);

            /* Escreve o evento de SAIDA */
            int pub = cardinalidade_cjt(locais[l_id]->publico);
            printf("SAIDA HEROI %2d Local %d (%2d/%2d)\n", h_id, l_id, pub, lotacao);

            break;
        }

            /*//////////
            // MISSAO //
            //////////*/

        case 2:
        {
            int m_id = evento->dado2;

            /* Escreve as habilidades necessárias na missao */
            printf("MISSAO %d HAB_REQ: ", m_id);
            imprime_cjt(missoes[m_id]->req);
            printf("\n");

            /* Escreve as habilidades presente no local e decide
               se os herois do local podem concluir a missao */
            int i, l_id = -1, l_id_aux = -1;
            for (i = 0; i < LOCAIS; i++)
            {
                /*  Escreve as habilidades presente no local  */
                printf("%6d: MISSAO %d HAB_EQL %d: ", t, m_id, i);
                imprime_cjt(locais[i]->u_skills);
                printf("\n");

                /*  Decide se os herois podem concluir a missao  */
                if (contido_cjt(missoes[m_id]->req, locais[i]->u_skills))
                {
                    l_id_aux = i;

                    if (l_id < 0)
                        l_id = l_id_aux;

                    if (locais[l_id_aux]->publico->card < locais[l_id]->publico->card)
                        l_id = l_id_aux;
                }
            }

            /* Decide se os herois podem concluir a missao */
            if (l_id > 0)
            {
                /* Escreve os herois do local */
                printf("%6d: MISSAO %d HER_ESQ %d: ", t, m_id, l_id);
                imprime_cjt(locais[l_id]->publico);
                printf("\n");

                inicia_iterador_cjt(locais[l_id]->publico);

                /* Atualiza XP dos heróis */
                int h_id;
                for (i = 0; i < locais[l_id]->publico->card; i++)
                {
                    incrementa_iterador_cjt(locais[l_id]->publico, &h_id);
                    herois[h_id]->xp++;
                }
            }
            else
            {
                /* Caso a missao seja impossivel, repete ela num futuro aleatorio */
                printf("%6d: Missao %d IMPOSSIVEL \n", t, m_id);
                if (t < FIM_DO_MUNDO - 1)
                    cria_evento(lef, ALEAT(t, FIM_DO_MUNDO), 2, 0, m_id);
            }

            break;
        }

            /*////////////////
            // FIM DO MUNDO //
            ////////////////*/

        case 3:
        {
            printf("Fim");
            printf("\n");

            lef->Primeiro = NULL;
            break;
        }
        }

        /* Apaga o evento atual e puxa o próximo evento */
        free(evento);
        evento = obtem_primeiro_lef(lef);
    }

    /* Libera os espaços alocados no programa */

    for (i = 0; i < HEROIS; i++)
        printf("HEROI %2d EXPERIENCIA %d\n", i, herois[i]->xp);

    for (i = 0; i < HEROIS; i++)
        free(herois[i]);

    for (i = 0; i < LOCAIS; i++)
        free(locais[i]);

    for (i = 0; i < MISSOES; i++)
        free(missoes[i]);

    free(mundo);
    free(herois);
    free(locais);
    free(missoes);

    destroi_lef(lef);

    return 0;
}
