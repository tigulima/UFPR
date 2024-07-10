#include <stdio.h>
#include <stdlib.h>

void request(int *n) {
    printf("\nDigite o numero de vezes que deseja imprimir 'Ola Mundo': ");
    scanf("%d", n);
    printf("\n");
}

void olaMundoRec(int nVezes) {
    if (nVezes == 0) 
        return;

    olaMundoRec(nVezes - 1);
    printf("%d. Ola Mundo\n", nVezes);
}

int main() {
    int n;

    request(&n);
    olaMundoRec(n);

    printf("\n");

    return 0;
}