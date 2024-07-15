#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* sF = "ascii.txt";
    FILE* pF;

    pF = fopen(sF, "w");
    if (pF == NULL)
        printf("Erro ao criar arquivo");
    
    return 0;
}

