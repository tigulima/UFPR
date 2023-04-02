#include <stdio.h>

typedef struct racional
{
    int num[2];
    int den[2];
    int num_final;
    int den_final;
} racional;

racional ler_racional()
{
    racional r;

    for (int i = 0; i < 2; i++)
        scanf("%d %d", &r.num[i], &r.den[i]);

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

void soma(int a, int b, int c, int d)
{
    int num, den;

    den = mmc(b, d);
    num = ((den / b) * a + (den / d) * c);

    simplifica_escreve(num, den);
};

void subt(int a, int b, int c, int d)
{
    int num, den;

    den = mmc(b, d);
    num = ((den / b) * a - (den / d) * c);

    simplifica_escreve(num, den);
}

void mult(int a, int b, int c, int d)
{
    int num, den;

    num = a * c;
    den = b * d;

    simplifica_escreve(num, den);
}

void divi(int a, int b, int c, int d)
{
    int num, den;

    num = a * d;
    den = b * c;

    simplifica_escreve(num, den);
}

void main()
{
    racional r;

    r = ler_racional();

    if (r.den[0] != 0 && r.den[1] != 0)
    {
        soma(r.num[0], r.den[0], r.num[1], r.den[1]);
        subt(r.num[0], r.den[0], r.num[1], r.den[1]);
        mult(r.num[0], r.den[0], r.num[1], r.den[1]);
        divi(r.num[0], r.den[0], r.num[1], r.den[1]);
    }
}