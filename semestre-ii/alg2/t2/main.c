#include <stdio.h>
#include <stdlib.h>

#define ER_ALLOC 0

typedef struct presente
{
    int valor;
    int peso;
} presente;

// Handling de erros do programa
void error(int error_id)
{
    switch (error_id)
    {
    case ER_ALLOC:
        printf("\nERRO! Não há memória suficiente!\n");
    }

    exit(0);
}

// Entradas do programa
presente *le_presentes(int *n, int *p_max)
{
    presente *p;

    scanf("%d", n);
    scanf("%d", p_max);

    if (!(p = malloc(sizeof(presente) * *n)))
        return NULL;

    for (int i = 0; i < *n; i++)
    {
        scanf("%d", &p[i].valor);
        scanf("%d", &p[i].peso);
    }

    return p;
}

// Saidas do programa
void imprime_resultado(presente *p, int melhor_combinacao[], int n)
{
    int soma_valor = 0;

    printf("\n");

    for (int i = 0; i < n; i++)
    {
        if (melhor_combinacao[i])
        {
            printf("%d ", i + 1);
            soma_valor += p[i].valor;
        }
    }
    printf("\n%d\n", soma_valor);

    return;
}

// Descobre qual é a melhor combinacao de presentes
void calcula_combinacoes(presente *p, int v[], int n, int p_max, int *maior_valor, int *melhor_combinacao)
{
    int peso = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i] == 1)
            peso += p[i].peso;
    }

    if (peso > p_max)
        return;

    int valor = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i] == 1)
            valor += p[i].valor;
    }

    if (valor > *maior_valor)
    {
        *maior_valor = valor;
        for (int i = 0; i < n; i++)
        {
            melhor_combinacao[i] = v[i];
        }
    }

    return;
}

// Codigo recursivo que gera todas
// as combinacoes possiveis de presentes
void gera_combinacoes(presente *p, int v[], int n, int i, int p_max, int *maior_valor, int *melhor_combinacao)
{
    if (i == n)
    {
        calcula_combinacoes(p, v, n, p_max, maior_valor, melhor_combinacao);
        return;
    }

    v[i] = 0;
    gera_combinacoes(p, v, n, i + 1, p_max, maior_valor, melhor_combinacao);

    v[i] = 1;
    gera_combinacoes(p, v, n, i + 1, p_max, maior_valor, melhor_combinacao);

    return;
}

int main()
{
    int n, p_max;
    presente *p;

    p = le_presentes(&n, &p_max);

    if (!p)
        error(ER_ALLOC);

    int v[n];
    int maior_valor = 0;
    int melhor_combinacao[n];
    gera_combinacoes(p, v, n, 0, p_max, &maior_valor, melhor_combinacao);

    imprime_resultado(p, melhor_combinacao, n);

    return 0;
}