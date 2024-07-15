#include <stdio.h>
#include "lib_racionais.h"

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