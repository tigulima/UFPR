#include <stdio.h>
#include <stdlib.h>

void request(unsigned int *n) {
    printf("\nDigite um número: ");
    scanf("%u", n);
    printf("\n");
}

int binario(int n, int soma) {
    if (n <= 0)
        return 0;

    soma = soma + ((n % 2)* 10);

    return soma + binario(n / 10, soma);
}

int main() {
    int n, soma, res;

    request(&n);
    res = binario(n, soma);

    printf("Binario: %d\n\n", res);

    return 0;
}