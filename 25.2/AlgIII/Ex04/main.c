#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int chave;
    struct nodo *pai;
    struct nodo *fd;
    struct nodo *fe;
};

void transplantar(struct nodo *arvore, struct nodo *sai, struct nodo *entra) {
    return;
}

void excluir(struct nodo *arvore, struct nodo *n) {
    if (n->fe == NULL) {
        transplantar(arvore, n, n->fd);
        return;
    }
    if (n->fd == NULL) {
        transplantar(arvore, n, n->fe);
        return;
    }
}

int main() {

}