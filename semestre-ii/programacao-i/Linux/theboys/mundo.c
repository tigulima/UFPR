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

int ALEAT(x, y)
{
    return x + rand() % (y - x);
}

int MAX(x, y)
{
    return x > y ? x : y;
}

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

missao_t *cria_missao(conjunto_t *skills, int id)
{
    missao_t *m;

    if (!(m = malloc(sizeof(mundo_t))))
        return NULL;

    m->id = id;
    m->req = cria_subcjt_cjt(skills, ALEAT(1, SKILLS));

    return m;
}

mundo_t *cria_mundo()
{
    mundo_t *m;

    if (!(m = malloc(sizeof(mundo_t))))
        return NULL;

    m->ch_skills = cria_cjt(SKILLS);

    return m;
}

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

    lef = cria_lef();
    mundo = cria_mundo();

    /* CRIA LOCAIS */

    if (!(locais = malloc(sizeof(local_t) * LOCAIS)))
        return 0;

    for (i = 0; i < LOCAIS; i++)
        locais[i] = cria_local(cria_cjt(HEROIS), i);

    /* CRIA SKILLS */

    for (i = 0; i < SKILLS; i++)
        insere_cjt(mundo->ch_skills, i);

    /* CRIA HEROIS */

    if (!(herois = malloc(sizeof(heroi_t) * HEROIS)))
        return 0;

    for (i = 0; i < HEROIS; i++)
    {
        herois[i] = cria_heroi(mundo->ch_skills, i);
        cria_evento(lef, ALEAT(0, FIM_DO_MUNDO), 0, ALEAT(0, LOCAIS - 1), i);
    }

    /* CRIA MISSOES */

    if (!(missoes = malloc(sizeof(missao_t) * MISSOES)))
        return 0;

    for (i = 0; i < MISSOES; i++)
    {
        missoes[i] = cria_missao(mundo->ch_skills, i);
        cria_evento(lef, ALEAT(0, FIM_DO_MUNDO), 2, 0, i);
    }

    cria_evento(lef, FIM_DO_MUNDO, 3, 0, 0);

    /* SIMULACAO */

    evento = obtem_primeiro_lef(lef);
    while (lef->Primeiro != NULL)
    {
        int t = evento->tempo;
        int lotacao = locais[evento->dado1]->max;

        printf("%6d: ", t);

        switch (evento->tipo)
        {
        case 0:
        {
            int l_id = evento->dado1;
            int h_id = evento->dado2;

            if (cardinalidade_cjt(locais[l_id]->publico) < lotacao)
            {
                int tpl = MAX(1, herois[h_id]->paciencia / 10 + ALEAT(-2, 6));

                cria_evento(lef, t + tpl, 1, l_id, h_id);
                insere_cjt(locais[l_id]->publico, h_id);
                locais[l_id]->u_skills = uniao_cjt(locais[l_id]->u_skills, herois[h_id]->skills);
            }
            else if (herois[h_id]->paciencia / 4 - tamanho_fila(locais[l_id]->fila) > 0)
                insere_fila(locais[l_id]->fila, h_id);
            else
            {
                cria_evento(lef, t, 1, l_id, h_id);
                int pub = cardinalidade_cjt(locais[l_id]->publico);

                printf("CHEGA HEROI %2d Local %d (%2d/%2d), DESISTE\n", h_id, l_id, pub, lotacao);
                break;
            }

            int pub = cardinalidade_cjt(locais[l_id]->publico);
            int tam_fila = tamanho_fila(locais[l_id]->fila);

            if (vazia_fila(locais[l_id]->fila))
                printf("CHEGA HEROI %2d Local %d (%2d/%2d), ENTRA\n", h_id, l_id, pub, lotacao);
            else
                printf("CHEGA HEROI %2d Local %d (%2d/%2d), FILA %d\n", h_id, l_id, lotacao, lotacao, tam_fila);

            break;
        }
        case 1:
        {
            int l_id = evento->dado1;
            int h_id = evento->dado2;
            if (!vazia_fila(locais[l_id]->fila))
            {
                int h_id_fila;
                retira_fila(locais[l_id]->fila, &h_id_fila);
                retira_cjt(locais[l_id]->publico, h_id);

                cria_evento(lef, t, 0, l_id, h_id_fila);

                int pub = cardinalidade_cjt(locais[l_id]->publico);
                printf("SAIDA HEROI %2d Local %d (%2d/%2d), RETIRA FILA %d\n", h_id, l_id, pub, lotacao, h_id_fila);

                break;
            }

            locais[l_id]->u_skills = diferenca_cjt(locais[l_id]->u_skills, herois[h_id]->skills);
            retira_cjt(locais[l_id]->publico, h_id);

            int l_id_destino = ALEAT(0, LOCAIS);

            int d = MAX(l_id, l_id_destino) == l_id ? (l_id - l_id_destino) : (l_id_destino - l_id);
            int v = 100 - MAX(0, herois[h_id]->idade - 40);
            int tdl = d / v;

            cria_evento(lef, t + tdl / 15, 0, l_id_destino, h_id);

            int pub = cardinalidade_cjt(locais[l_id]->publico);
            printf("SAIDA HEROI %2d Local %d (%2d/%2d)\n", h_id, l_id, pub, lotacao);

            break;
        }
        case 2:
        {
            int m_id = evento->dado2;

            printf("MISSAO %d HAB_REQ: ", m_id);
            imprime_cjt(missoes[m_id]->req);
            printf("\n");

            int l_id = -1, l_id_aux = -1;
            int i;
            for (i = 0; i < LOCAIS; i++)
            {
                printf("%6d: MISSAO %d HAB_EQL %d: ", t, m_id, i);
                imprime_cjt(locais[i]->u_skills);
                printf("\n");

                if (contido_cjt(missoes[m_id]->req, locais[i]->u_skills))
                {
                    l_id_aux = i;

                    if (l_id < 0)
                        l_id = l_id_aux;

                    if (locais[l_id_aux]->publico->card < locais[l_id]->publico->card)
                        l_id = l_id_aux;
                }
            }

            if (l_id > 0)
            {
                printf("%6d: MISSAO %d HER_ESQ %d: ", t, m_id, l_id);
                imprime_cjt(locais[l_id]->publico);
                printf("\n");

                inicia_iterador_cjt(locais[l_id]->publico);

                int h_id;
                for (i = 0; i < locais[l_id]->publico->card; i++)
                {
                    incrementa_iterador_cjt(locais[l_id]->publico, &h_id);
                    herois[h_id]->xp++;
                }
            }
            else
            {
                printf("%6d: MISSAO %d IMPOSSIVEL \n", t, m_id);
                if (t < FIM_DO_MUNDO - 1)
                    cria_evento(lef, ALEAT(t, FIM_DO_MUNDO), 2, 0, m_id);
            }

            break;
        }
        case 3:
        {
            printf("Fim");
            printf("\n");

            lef->Primeiro = NULL;
            break;
        }
        }

        free(evento);
        evento = obtem_primeiro_lef(lef);
    }

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
