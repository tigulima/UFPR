#ifndef KDTREE_COMPLETO_H
#define KDTREE_COMPLETO_H

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

/* Funcoes originais */
void matarProgramaFaltaMemoria();
struct kdtree* criarArvore(unsigned int k);
struct nodo* criarNodo(float *ponto, int classe, unsigned int k);
struct kdtree* inserir(struct kdtree *arvore, float *ponto, int classe);
struct nodo* buscar(struct kdtree *arvore, float *ponto);
struct lista_vizinhos* zVizinhos(struct kdtree *arvore, float *ponto, unsigned int z);
void destruirArvore(struct kdtree *arvore);

/* Funcoes novas - Remocao */
struct kdtree* remover(struct kdtree *arvore, float *ponto);

/* Funcoes novas - Impressao */
void imprimirPreOrdem(struct kdtree *arvore);
void imprimirEmOrdem(struct kdtree *arvore);
void imprimirPosOrdem(struct kdtree *arvore);
void imprimirPorNivel(struct kdtree *arvore);

/* Funcoes novas - Informacoes */
int altura(struct kdtree *arvore);
int contarNodos(struct kdtree *arvore);
int estaVazia(struct kdtree *arvore);
struct nodo* encontrarMinimo(struct kdtree *arvore, unsigned int dimensao);

/* Funcoes novas - Consultas */
void listarPorClasse(struct kdtree *arvore, int classe);
int contarPorClasse(struct kdtree *arvore, int classe);

#endif // KDTREE_COMPLETO_H

