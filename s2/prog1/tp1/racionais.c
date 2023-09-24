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

void escreve_racional(racional r)
{
    if (r.den != 1)
        printf("%d/%d\n", r.num, r.den);
    else
        printf("%d\n", r.num);
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

racional simplifica(racional r)
{
    int div = mdc(r.num, r.den);

    r.num = r.num / div;
    r.den = r.den / div;

    return r;
}

racional soma(racional a, racional b)
{
    racional r;

    r.den = mmc(a.den, b.den);
    r.num = ((r.den / a.den) * a.num + (r.den / b.den) * b.num);

    return r;
};

racional subt(racional a, racional b)
{
    racional r;

    r.den = mmc(a.den, b.den);
    r.num = ((r.den / a.den) * a.num - (r.den / b.den) * b.num);

    return r;
}

racional mult(racional a, racional b)
{
    racional r;

    r.num = a.num * b.num;
    r.den = a.den * b.den;

    return r;
}

racional divi(racional a, racional b)
{
    racional r;

    r.num = a.num * b.den;
    r.den = a.den * b.num;

    return r;
}

int main()
{
    racional a, b, r;

    a = ler_racional();
    b = ler_racional();

    if (a.den != 0 && b.den != 0)
    {
        r = simplifica(soma(a, b));
        escreve_racional(r);

        r = simplifica(subt(a, b));
        escreve_racional(r);

        r = simplifica(mult(a, b));
        escreve_racional(r);

        r = simplifica(divi(a, b));
        escreve_racional(r);

        return 0;
    }
    else
    {
        return 1;
    }
}