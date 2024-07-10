#include <stdio.h>
#include <stdlib.h>

void request(unsigned int *n) {
    printf("\nDigite um número: ");
    scanf("%u", n);
    printf("\n");
}

int somaDig(unsigned int n, int soma) {
    if(n <= 0)
        return 0;

    soma = soma + (n % 10);

    return soma + somaDig((n / 10), soma);
}

int main() {
    unsigned int n, soma, res;

    soma = 0;

    request(&n);
    res = somaDig(n, soma);

    printf("Soma dos dígitos: %d\n\n", res);

    return 0;
}