#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int valor;
    struct nodo* nodo_esq;
    struct nodo* nodo_dir;
};

void print_arvore() {
    
};

int main() {

    struct nodo* valor1;

    valor1 = malloc(sizeof(struct nodo));

    if(!valor1) {
        printf("Não rolou n");
    }

    valor1->valor = 10;

    struct nodo* valor2;

    valor2 = malloc(sizeof(struct nodo));

    if(!valor2) {
        printf("Não rolou n");
    }

    valor2->valor = 10;
    valor1->nodo_esq = valor2;
};