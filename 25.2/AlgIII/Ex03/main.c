#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_EXP 100

enum tipo_nodo {
    OP,
    VAR,
    INDEFINIDO,
};

struct nodo {
    enum tipo_nodo tipo;
    char operacao;
    double valor;
    struct nodo* fe;
    struct nodo* fd;
};

struct nodo* cria_nodo(){
    struct nodo* novo_nodo = malloc(sizeof(struct nodo));

    if (!novo_nodo) {
        printf("\nAAAAAAA\n");
        return NULL;
    }

    novo_nodo->tipo = INDEFINIDO;
    novo_nodo->fe = NULL;
    novo_nodo->fd = NULL;

    return novo_nodo;
};

struct nodo* insere_nodo(struct nodo* n){
    struct nodo* novo_nodo = cria_nodo();

    if (n->fe == NULL) {
        n->fe = novo_nodo;
        printf("\ninserido nodo na esquerda");
        return novo_nodo;
    }

    if (n->fd == NULL) {
        n->fd = novo_nodo;
        printf("\ninserido nodo na direita");
        return novo_nodo;
    }

    printf("\nEsse nodo ta atoladinho\n");
    return NULL;

}

// int destroi_arvore(struct nodo* n){

// }

// int separa_expressao() {

// }

int is_valor(char *str) {
    switch (*str) {
        case '+': return 0;
        case '-': return 0;
        case '*': return 0;
        case '/': return 0;
        default: return 1;
    }
}

struct nodo* cria_arvore(char* expressao) {
    struct nodo* n = cria_nodo();
    struct nodo* nodo_atual = n;

    const char *separador = " ";
    char *token;

    // pega o primeiro item da notacao polonesa, que
    // eh uma operacao, e adiciona na raiz
    token = strtok(expressao, separador);
    
    printf("\n-> %s\n", token);
    nodo_atual->operacao = *token;
    nodo_atual->tipo = OP;
    
    // cria um proximo nodo e adiciona a esquerda da raiz
    struct nodo* prox_nodo = insere_nodo(nodo_atual);
    
    while ((token = strtok(NULL, separador)) != NULL) {
        printf("\n-> %s\n", token);
        if (is_valor(token)) {
            prox_nodo->valor = atof(token);
            prox_nodo->tipo = VAR;
        } else {
            nodo_atual = prox_nodo;
            nodo_atual->operacao = *token;
            nodo_atual->tipo = OP;
        }

        prox_nodo = insere_nodo(nodo_atual);
    }

    return n;
}

void print_arvore(struct nodo* n){
    if (!n) {
        return;
    }

    print_arvore(n->fe);

    if (n->tipo == VAR) {
        printf("%.2f ", n->valor);
    } else {
        printf("%c ", n->operacao);
    }

    print_arvore(n->fd);
}

int main(){
    char str[TAM_EXP];

    printf("escreeeaaaaaa: ");
    fgets(str, TAM_EXP, stdin);

    struct nodo* arvore = cria_arvore(str);


    // struct nodo* raiz = cria_nodo();

    // raiz->operacao = '/';
    // raiz->valor = 1;
    
    // struct nodo* e1 = insere_nodo(raiz);

    // e1->operacao = '-';

    // struct nodo* d1 = insere_nodo(raiz);

    // d1->operacao = '*';

    // struct nodo* e21 = insere_nodo(e1);

    // e21->operacao = '*';

    // struct nodo* d21 = insere_nodo(e1);

    // d21->operacao = '*';

    // struct nodo* e31 = insere_nodo(e21);

    // e31->operacao = 'a';

    // struct nodo* d31 = insere_nodo(e21);

    // d31->operacao = 'b';

    // struct nodo* e32 = insere_nodo(d21);

    // e32->operacao = 'c';

    // struct nodo* d32 = insere_nodo(d21);

    // d32->operacao = 'd';

    // struct nodo* e22 = insere_nodo(d1);

    // e22->operacao = 'e';

    // struct nodo* d22 = insere_nodo(d1);

    // d22->operacao = 'f';


    printf("\n------------\n");
    print_arvore(arvore);

    return 0;
}