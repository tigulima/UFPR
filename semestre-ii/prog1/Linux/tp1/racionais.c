#include <stdio.h>

typedef struct racional
{
    int num;
    int den;
} racional;

racional ler_racional()
{
    racional r;

    scanf("%d %d", &r.num, &r.den);

    return r;
}

void escreve_racional(int num, int den)
{
    if (num % den != 0)
        printf("%d/%d\n", num, den);
    else
        printf("%d\n", num / den);
}

void simplifica_escreve(int num, int den)
{
    int menor = den;
    if (num < den)
        menor = num;

    for (int i = 1; i <= menor && num % i == 0 && den % i == 0; i++)
    {
        num = num / i;
        den = den / i;
        i = 1;
    }

    escreve_racional(num, den);
}

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

int mmc(int a, int b)
{
    return a * (b / mdc(a, b));
}

void soma(int a_num, int a_den, int b_num, int b_den)
{
    int num, den;

    den = mmc(a_den, b_den);
    num = ((den / a_den) * a_num + (den / b_den) * b_num);

    simplifica_escreve(num, den);
};

void subt(int a_num, int a_den, int b_num, int b_den)
{
    int num, den;

    den = mmc(a_den, b_den);
    num = ((den / a_den) * a_num - (den / b_den) * b_num);

    simplifica_escreve(num, den);
}

void mult(int a_num, int a_den, int b_num, int b_den)
{
    int num, den;

    num = a_num * b_num;
    den = a_den * b_den;

    simplifica_escreve(num, den);
}

void divi(int a_num, int a_den, int b_num, int b_den)
{
    int num, den;

    num = a_num * b_den;
    den = a_den * b_num;

    simplifica_escreve(num, den);
}

void main()
{
    racional a, b;

    a = ler_racional();
    b = ler_racional();

    if (a.den != 0 && b.den != 0)
    {
        soma(a.num, a.den, b.num, b.den);
        subt(a.num, a.den, b.num, b.den);
        mult(a.num, a.den, b.num, b.den);
        divi(a.num, a.den, b.num, b.den);
    }
}