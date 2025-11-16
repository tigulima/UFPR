#ifndef KDTREE_H
#define KDTREE_H

struct nodo {
    float *ponto;
    int classe;
    struct nodo *esq;
    struct nodo *dir;
};

struct kdtree {
    struct nodo *raiz;
    unsigned int k;
};

// Estruturas auxiliares para busca de k-vizinhos mais próximos
struct candidato {
    struct nodo *nodo;
    float dist;
};

struct lista_vizinhos {
    struct candidato *candidatos;
    unsigned int z;
    unsigned int tam;
    float *ponto_alvo;
};

// Estruturas auxiliares para impressão em largura
struct elem_fila {
    struct nodo *nodo;
    struct elem_fila *prox;
};

struct fila {
    struct elem_fila *inicio;
    struct elem_fila *fim;
};


void matarProgramaFaltaMemoria();
struct kdtree* criarArvore(unsigned int k);
struct nodo* criarNodo(float *ponto, int classe, unsigned int k);
struct kdtree* inserir(struct kdtree *arvore, float *ponto, int classe);
struct nodo* buscar(struct kdtree *arvore, float *ponto);
void imprimirEmLargura(struct kdtree *arvore);
struct lista_vizinhos* zVizinhos(struct kdtree *arvore, float *ponto, unsigned int z);
void destruirArvore(struct kdtree *arvore);

#endif // KDTREE_H