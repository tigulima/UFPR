#include "kdtree_completo.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-6

void matarProgramaFaltaMemoria() {
    fprintf(stderr, "Falha ao alocar memoria.");
    exit(1);
}

/* ========== FUNCOES ORIGINAIS ========== */

struct kdtree* criarArvore(unsigned int k) {
    struct kdtree *arvore = (struct kdtree *)malloc(sizeof(struct kdtree));
    if (arvore == NULL) {
        matarProgramaFaltaMemoria();
    }

    arvore->raiz = NULL;
    arvore->k = k;

    return arvore;
}

struct nodo* criarNodo(float *ponto, int classe, unsigned int k) {
    struct nodo *novoNodo = (struct nodo *)malloc(sizeof(struct nodo));
    if (novoNodo == NULL) {
        matarProgramaFaltaMemoria();
    }

    novoNodo->ponto = (float *)malloc(k * sizeof(float));
    if (novoNodo->ponto == NULL) {
        free(novoNodo);
        matarProgramaFaltaMemoria();
    }

    for (unsigned int i = 0; i < k; i++) {
        novoNodo->ponto[i] = ponto[i];
    }
    novoNodo->classe = classe;
    novoNodo->esq = NULL;
    novoNodo->dir = NULL;

    return novoNodo;
}

static struct nodo* inserirRecursivo(struct nodo *raiz, float *ponto, int classe, unsigned int k, unsigned int nivel) {
    if (raiz == NULL) {
        return criarNodo(ponto, classe, k);
    }

    unsigned int eixo = nivel % k;

    if (ponto[eixo] < raiz->ponto[eixo]) {
        raiz->esq = inserirRecursivo(raiz->esq, ponto, classe, k, nivel + 1);
    } else {
        raiz->dir = inserirRecursivo(raiz->dir, ponto, classe, k, nivel + 1);
    }

    return raiz;
}

struct kdtree* inserir(struct kdtree *arvore, float *ponto, int classe) {
    arvore->raiz = inserirRecursivo(arvore->raiz, ponto, classe, arvore->k, 0);
    return arvore;
}

static int pontosIguais(float *p1, float *p2, unsigned int k) {
    for (unsigned int i = 0; i < k; i++) {
        if (fabs(p1[i] - p2[i]) > EPSILON) {
            return 0;
        }
    }
    return 1;
}

static struct nodo* buscarRecursivo(struct nodo *nodo, float *ponto, unsigned int k, unsigned int nivel) {
    if (nodo == NULL) {
        return NULL;
    }
    
    if (pontosIguais(nodo->ponto, ponto, k)) {
        return nodo;
    }

    unsigned int eixo = nivel % k;

    if (ponto[eixo] < nodo->ponto[eixo]) {
        return buscarRecursivo(nodo->esq, ponto, k, nivel + 1);
    } else {
        return buscarRecursivo(nodo->dir, ponto, k, nivel + 1);
    }
}

struct nodo* buscar(struct kdtree *arvore, float *ponto) {
    return buscarRecursivo(arvore->raiz, ponto, arvore->k, 0);
}

static float calcularDistancia(float *p1, float *p2, unsigned int k) {
    float soma = 0.0;
    for (unsigned int i = 0; i < k; i++) {
        float diff = p1[i] - p2[i];
        soma += diff * diff;
    }
    return sqrt(soma);
}

static void insereCandidato(struct lista_vizinhos *lista, struct nodo *nodo, float dist, int pos) {
    lista->candidatos[pos].nodo = nodo;
    lista->candidatos[pos].dist = dist;
}

static int posicaoCandidato(struct lista_vizinhos *lista, float dist) {
    int i = 0;
    while (i < lista->tam && lista->candidatos[i].dist < dist) {
        i++;
    }
    return i;
}

static void abreEspacoNaLista(struct lista_vizinhos *lista, int pos) {
    for (int j = lista->z - 1; j > pos; j--) {
        lista->candidatos[j] = lista->candidatos[j - 1];
    }
}

static int insereListaVizinhos(struct lista_vizinhos *lista, struct nodo *nodo, float dist, unsigned int k) {
    int pos = posicaoCandidato(lista, dist);
    abreEspacoNaLista(lista, pos);
    insereCandidato(lista, nodo, dist, pos);

    if (lista->tam < lista->z) {
        lista->tam++;
    }

    return pos;
}

static void zVizinhosRecursivo(struct nodo *nodo, struct lista_vizinhos *lista, unsigned int k, unsigned int nivel) {
    if (nodo == NULL) {
        return;
    }

    float dist = calcularDistancia(lista->ponto_alvo, nodo->ponto, k);
    if (lista->tam < lista->z || dist < lista->candidatos[lista->tam - 1].dist) {
        insereListaVizinhos(lista, nodo, dist, k);
    }

    unsigned int eixo = nivel % k;

    if (lista->ponto_alvo[eixo] < nodo->ponto[eixo]) {
        zVizinhosRecursivo(nodo->esq, lista, k, nivel + 1);
        if (lista->tam < lista->z || fabs(lista->ponto_alvo[eixo] - nodo->ponto[eixo]) < lista->candidatos[lista->tam - 1].dist) {
            zVizinhosRecursivo(nodo->dir, lista, k, nivel + 1);
        }
    } else {
        zVizinhosRecursivo(nodo->dir, lista, k, nivel + 1);
        if (lista->tam < lista->z || fabs(lista->ponto_alvo[eixo] - nodo->ponto[eixo]) < lista->candidatos[lista->tam - 1].dist) {
            zVizinhosRecursivo(nodo->esq, lista, k, nivel + 1);
        }
    }
}

struct lista_vizinhos* zVizinhos(struct kdtree *arvore, float *ponto, unsigned int z) {
    struct lista_vizinhos *lista;

    lista = (struct lista_vizinhos *)malloc(sizeof(struct lista_vizinhos));
    if (lista == NULL) {
        matarProgramaFaltaMemoria();
    }

    lista->candidatos = (struct candidato *)malloc(z * sizeof(struct candidato));
    if (lista->candidatos == NULL) {
        free(lista);
        matarProgramaFaltaMemoria();
    }

    lista->z = z;
    lista->tam = 0;
    lista->ponto_alvo = ponto;

    zVizinhosRecursivo(arvore->raiz, lista, arvore->k, 0);

    return lista;
}

static void destruirArvoreRecursivo(struct nodo *nodo) {
    if (nodo == NULL) {
        return;
    }
    destruirArvoreRecursivo(nodo->esq);
    destruirArvoreRecursivo(nodo->dir);
    free(nodo->ponto);
    free(nodo);
}

void destruirArvore(struct kdtree *arvore) {
    destruirArvoreRecursivo(arvore->raiz);
    free(arvore);
}

/* ========== FUNCOES NOVAS - REMOCAO ========== */

/* Encontra o nodo com valor minimo em uma dimensao especifica
   Usado para encontrar substituto na remocao */
static struct nodo* encontrarMinimoRecursivo(struct nodo *nodo, unsigned int dim, unsigned int k, unsigned int nivel) {
    if (nodo == NULL) {
        return NULL;
    }

    unsigned int eixo = nivel % k;

    // Se o eixo atual e a dimensao procurada coincidem, o minimo esta a esquerda
    if (eixo == dim) {
        if (nodo->esq == NULL) {
            return nodo;
        }
        return encontrarMinimoRecursivo(nodo->esq, dim, k, nivel + 1);
    }

    // Caso contrario, precisa verificar ambos os lados
    struct nodo *esq = encontrarMinimoRecursivo(nodo->esq, dim, k, nivel + 1);
    struct nodo *dir = encontrarMinimoRecursivo(nodo->dir, dim, k, nivel + 1);
    
    struct nodo *minimo = nodo;
    if (esq != NULL && esq->ponto[dim] < minimo->ponto[dim]) {
        minimo = esq;
    }
    if (dir != NULL && dir->ponto[dim] < minimo->ponto[dim]) {
        minimo = dir;
    }
    
    return minimo;
}

/* Remove um nodo da arvore mantendo a propriedade da KD-Tree */
static struct nodo* removerRecursivo(struct nodo *raiz, float *ponto, unsigned int k, unsigned int nivel) {
    if (raiz == NULL) {
        return NULL;
    }

    unsigned int eixo = nivel % k;

    // Se encontrou o nodo a remover
    if (pontosIguais(raiz->ponto, ponto, k)) {
        // Se tem filho direito, substitui pelo minimo da direita
        if (raiz->dir != NULL) {
            struct nodo *min = encontrarMinimoRecursivo(raiz->dir, eixo, k, nivel + 1);
            
            // Copia os dados do minimo para este nodo
            for (unsigned int i = 0; i < k; i++) {
                raiz->ponto[i] = min->ponto[i];
            }
            raiz->classe = min->classe;
            
            // Remove o minimo da subarvore direita
            raiz->dir = removerRecursivo(raiz->dir, min->ponto, k, nivel + 1);
        }
        // Se so tem filho esquerdo, move para direita e encontra minimo
        else if (raiz->esq != NULL) {
            struct nodo *min = encontrarMinimoRecursivo(raiz->esq, eixo, k, nivel + 1);
            
            for (unsigned int i = 0; i < k; i++) {
                raiz->ponto[i] = min->ponto[i];
            }
            raiz->classe = min->classe;
            
            // Move subarvore esquerda para direita e remove minimo
            raiz->dir = raiz->esq;
            raiz->esq = NULL;
            raiz->dir = removerRecursivo(raiz->dir, min->ponto, k, nivel + 1);
        }
        // Se e folha, apenas remove
        else {
            free(raiz->ponto);
            free(raiz);
            return NULL;
        }
    }
    // Continua buscando o nodo
    else if (ponto[eixo] < raiz->ponto[eixo]) {
        raiz->esq = removerRecursivo(raiz->esq, ponto, k, nivel + 1);
    } else {
        raiz->dir = removerRecursivo(raiz->dir, ponto, k, nivel + 1);
    }

    return raiz;
}

struct kdtree* remover(struct kdtree *arvore, float *ponto) {
    arvore->raiz = removerRecursivo(arvore->raiz, ponto, arvore->k, 0);
    return arvore;
}

/* ========== FUNCOES NOVAS - IMPRESSAO ========== */

/* Imprime um ponto completo com suas coordenadas e classe */
static void imprimirPonto(struct nodo *nodo, unsigned int k) {
    printf("(");
    for (unsigned int i = 0; i < k; i++) {
        printf("%.2f", nodo->ponto[i]);
        if (i < k - 1) {
            printf(", ");
        }
    }
    printf(") classe=%d", nodo->classe);
}

/* Pre-ordem: raiz -> esquerda -> direita */
static void imprimirPreOrdemRecursivo(struct nodo *nodo, unsigned int k) {
    if (nodo == NULL) {
        return;
    }
    
    imprimirPonto(nodo, k);
    printf("\n");
    imprimirPreOrdemRecursivo(nodo->esq, k);
    imprimirPreOrdemRecursivo(nodo->dir, k);
}

void imprimirPreOrdem(struct kdtree *arvore) {
    printf("Pre-ordem:\n");
    imprimirPreOrdemRecursivo(arvore->raiz, arvore->k);
}

/* Em-ordem: esquerda -> raiz -> direita */
static void imprimirEmOrdemRecursivo(struct nodo *nodo, unsigned int k) {
    if (nodo == NULL) {
        return;
    }
    
    imprimirEmOrdemRecursivo(nodo->esq, k);
    imprimirPonto(nodo, k);
    printf("\n");
    imprimirEmOrdemRecursivo(nodo->dir, k);
}

void imprimirEmOrdem(struct kdtree *arvore) {
    printf("Em-ordem:\n");
    imprimirEmOrdemRecursivo(arvore->raiz, arvore->k);
}

/* Pos-ordem: esquerda -> direita -> raiz */
static void imprimirPosOrdemRecursivo(struct nodo *nodo, unsigned int k) {
    if (nodo == NULL) {
        return;
    }
    
    imprimirPosOrdemRecursivo(nodo->esq, k);
    imprimirPosOrdemRecursivo(nodo->dir, k);
    imprimirPonto(nodo, k);
    printf("\n");
}

void imprimirPosOrdem(struct kdtree *arvore) {
    printf("Pos-ordem:\n");
    imprimirPosOrdemRecursivo(arvore->raiz, arvore->k);
}

/* Estrutura auxiliar para fila usada na impressao por nivel */
struct nodo_fila {
    struct nodo *nodo;
    struct nodo_fila *prox;
};

/* Imprime arvore por nivel (BFS - Breadth-First Search) */
void imprimirPorNivel(struct kdtree *arvore) {
    if (arvore->raiz == NULL) {
        printf("Arvore vazia\n");
        return;
    }

    printf("Por nivel:\n");

    // Cria fila para BFS
    struct nodo_fila *inicio = (struct nodo_fila *)malloc(sizeof(struct nodo_fila));
    if (inicio == NULL) {
        matarProgramaFaltaMemoria();
    }
    inicio->nodo = arvore->raiz;
    inicio->prox = NULL;
    struct nodo_fila *fim = inicio;

    // Processa fila ate esvaziar
    while (inicio != NULL) {
        struct nodo *atual = inicio->nodo;
        struct nodo_fila *temp = inicio;
        inicio = inicio->prox;
        free(temp);

        if (atual == NULL) {
            continue;
        }

        // Imprime nodo atual
        imprimirPonto(atual, arvore->k);
        printf("\n");

        // Adiciona filhos na fila
        if (atual->esq != NULL) {
            struct nodo_fila *novo = (struct nodo_fila *)malloc(sizeof(struct nodo_fila));
            if (novo == NULL) {
                matarProgramaFaltaMemoria();
            }
            novo->nodo = atual->esq;
            novo->prox = NULL;
            if (fim != NULL) {
                fim->prox = novo;
            }
            fim = novo;
        }

        if (atual->dir != NULL) {
            struct nodo_fila *novo = (struct nodo_fila *)malloc(sizeof(struct nodo_fila));
            if (novo == NULL) {
                matarProgramaFaltaMemoria();
            }
            novo->nodo = atual->dir;
            novo->prox = NULL;
            if (fim != NULL) {
                fim->prox = novo;
            }
            fim = novo;
        }
    }
}

/* ========== FUNCOES NOVAS - INFORMACOES ========== */

/* Calcula a altura da subarvore */
static int alturaRecursivo(struct nodo *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    
    int alturaEsq = alturaRecursivo(nodo->esq);
    int alturaDir = alturaRecursivo(nodo->dir);
    
    return 1 + (alturaEsq > alturaDir ? alturaEsq : alturaDir);
}

int altura(struct kdtree *arvore) {
    return alturaRecursivo(arvore->raiz);
}

/* Conta o numero total de nodos */
static int contarNodosRecursivo(struct nodo *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return 1 + contarNodosRecursivo(nodo->esq) + contarNodosRecursivo(nodo->dir);
}

int contarNodos(struct kdtree *arvore) {
    return contarNodosRecursivo(arvore->raiz);
}

/* Verifica se a arvore esta vazia */
int estaVazia(struct kdtree *arvore) {
    return arvore->raiz == NULL;
}

/* Encontra o nodo com valor minimo em uma dimensao */
struct nodo* encontrarMinimo(struct kdtree *arvore, unsigned int dimensao) {
    if (dimensao >= arvore->k) {
        return NULL;
    }
    return encontrarMinimoRecursivo(arvore->raiz, dimensao, arvore->k, 0);
}

/* ========== FUNCOES NOVAS - CONSULTAS ========== */

/* Lista todos os pontos de uma classe especifica */
static void listarPorClasseRecursivo(struct nodo *nodo, int classe, unsigned int k) {
    if (nodo == NULL) {
        return;
    }
    
    listarPorClasseRecursivo(nodo->esq, classe, k);
    
    if (nodo->classe == classe) {
        imprimirPonto(nodo, k);
        printf("\n");
    }
    
    listarPorClasseRecursivo(nodo->dir, classe, k);
}

void listarPorClasse(struct kdtree *arvore, int classe) {
    printf("Pontos da classe %d:\n", classe);
    listarPorClasseRecursivo(arvore->raiz, classe, arvore->k);
}

/* Conta quantos pontos existem de uma classe */
static int contarPorClasseRecursivo(struct nodo *nodo, int classe) {
    if (nodo == NULL) {
        return 0;
    }
    
    int count = (nodo->classe == classe) ? 1 : 0;
    return count + contarPorClasseRecursivo(nodo->esq, classe) + contarPorClasseRecursivo(nodo->dir, classe);
}

int contarPorClasse(struct kdtree *arvore, int classe) {
    return contarPorClasseRecursivo(arvore->raiz, classe);
}

