#include <stdio.h>
#include <stdlib.h>

void request(unsigned int *n) {
    printf("\nDigite um número: ");
    scanf("%u", n);
    printf("\n");
}

unsigned int soma(unsigned int n) {
    if (n <= 0)
        return 0;

    return n + soma(n-1);
}

int main() {
    unsigned int n, res;

    request(&n);
    res = soma(n);

    printf("Somatório: %u\n\n", res);

    return 0;
}