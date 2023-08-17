#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *filename;

    filename = "teste";

    f = fopen(filename, "w");
    if (fopen(filename, "r") == NULL)
        printf("ERRO ao criar arquivo!\n");
    else
        printf("Deu certo!\n");

    fclose();

    return 0;
}
