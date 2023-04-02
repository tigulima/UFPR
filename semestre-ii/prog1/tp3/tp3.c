#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct racional
{
    int num;
    int den;
} racional;

// É usado para simplificar o racional gerado
int mdc(int a, int b)
{
    while (b != 0)
    {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

racional *gera_racional()
{
    racional *r;
    int div;

    // Para o programa se nao der para alocar
    // memoria para o racional
    if (!(r = malloc(sizeof(racional))))
        return NULL;

    // Gera um racional aleatório
    r->num = (rand() % 20 + 1);
    r->den = (rand() % 20 + 1);
    // Simplifica o racional
    div = mdc(r->num, r->den);
    r->num = r->num / div;
    r->den = r->den / div;

    return r;
}

racional adiciona_vetor(racional *r, racional **v, int i)
{
    v[i] = r;

    return *v[i];
}

// É usado para ordenar o vetor
void troca_rac(racional **v, int a, int b)
{
    racional *aux;

    aux = v[a];
    v[a] = v[b];
    v[b] = aux;
}

void ordena_vetor(racional **v, int n)
{
    int i, j, menor;

    // Selection sort
    for (i = 0; i < n - 1; i++)
    {
        menor = i;
        for (j = i + 1; j < n; j++)
        {
            if ((float)v[j]->num / (float)v[j]->den < (float)v[menor]->num / (float)v[menor]->den)
                menor = j;
        }
        troca_rac(v, i, menor);
    }
}

void escreve_vetor(racional **v, int n)
{
    int i;
    for (i = 0; i < n - 1; i++)
        printf("%d/%d ", v[i]->num, v[i]->den);
    printf("%d/%d", v[i]->num, v[i]->den);
}

void deleta_vetor(racional **v, int n)
{
    int i;
    for (i = 0; i < n; i++)
        free(v[i]);
}

int main()
{
    racional *r, *v[MAX];
    int i, n;

    scanf("%d", &n);

    srand(0);
    for (i = 0; i < n; i++)
    {
        r = gera_racional();
        if (!r)
            return -1;
        else
            adiciona_vetor(r, v, i);
    }

    ordena_vetor(v, i);

    escreve_vetor(v, i);

    deleta_vetor(v, i);

    return 0;
}