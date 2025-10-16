#include "redblack.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct fila{
    struct fila_nodo* inicio;
    struct fila_nodo* fim;
};

struct fila_nodo{
    struct nodo* nodo;
    struct fila_nodo* prox; 
};

// Criamos uma variável global nesse caso pois se fosse criado
// dentro de uma funçao (como "criaSentinela"), seria necessário
// passar como parâmtro para todas as funções desse código.
static struct nodo SENTINELA_nodo = {
    .chave = 0,
    .cor = PRETO,
    .pai = &SENTINELA_nodo,
    .esq = &SENTINELA_nodo,
    .dir = &SENTINELA_nodo
};

static struct nodo* SENTINELA = &SENTINELA_nodo;

void matarProgramaFaltaMemoria() {
    fprintf(stderr, "Falha ao alocar memória.\n");
    exit(1);
};

struct aluno* getAluno(){
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        matarProgramaFaltaMemoria();
    retorno->nome = malloc(sizeof("Thiago Imai Lima"));//sizeof conta o \0
	if(!retorno->nome)
		matarProgramaFaltaMemoria();
    retorno->nomeDinf = malloc(sizeof("til20"));
    if(!retorno->nomeDinf)
        matarProgramaFaltaMemoria();
    
	strcpy(retorno->nome, "Thiago Imai Lima");
    strcpy(retorno->nomeDinf, "til20");
    retorno->grr = 20204397;

	return retorno;
}

void imprimirDadosAluno(){
    struct aluno* aluno = getAluno();
    
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    return;
}

//IMPLEMENTE AS DEMAIS FUNÇÕES AQUI

//retorna SENTINELA se não foi possível inserir
struct nodo* inserir(struct nodo** raiz, int chave) {
    struct nodo* novo_nodo = criarNodo(chave);

    struct nodo* pai_do_novo_nodo = SENTINELA;
    struct nodo* nodo_atual = *raiz == NULL ? SENTINELA : *raiz;

    while (nodo_atual != SENTINELA) {
        pai_do_novo_nodo = nodo_atual;

        if (chave < nodo_atual->chave) {
            nodo_atual = nodo_atual->esq;
        } else if (chave > nodo_atual->chave) {
            nodo_atual = nodo_atual->dir;
        } else {
            free(novo_nodo);
            return SENTINELA;
        }
    }

    novo_nodo->pai = pai_do_novo_nodo;
    if (pai_do_novo_nodo == SENTINELA) {
        *raiz = novo_nodo;
    } else if (novo_nodo->chave < pai_do_novo_nodo->chave) {
        pai_do_novo_nodo->esq = novo_nodo;
    } else {
        pai_do_novo_nodo->dir = novo_nodo;
    }

    inserirFixup(*raiz, novo_nodo);

    return novo_nodo;
}

// retorna o número de nodos excluídos
int excluir(struct nodo** raiz, int chave) {

}

//retorna SENTINELA se não existe
struct nodo* buscar(struct nodo* raiz, int chave) {

}

void imprimirEmOrdem(struct nodo* nodo) {
    if (nodo == SENTINELA) {
        return;
    }

    imprimirEmOrdem(nodo->esq);
    printf("%i\t", nodo->chave);
    imprimirEmOrdem(nodo->dir);
}

void imprimirEmLargura(struct nodo* raiz) {
    if (raiz == SENTINELA) {
        return;
    }

    struct fila* fila = criarFila();
    struct nodo* nodo = NULL;

    enfileirar(&fila, raiz);

    while (fila->inicio != NULL) {
        nodo = desenfileirar(&fila);

        printf("%i\t", nodo->chave);
        if (nodo->esq != SENTINELA) {
            enfileirar(&fila, nodo->esq);
        }
        if (nodo->dir != SENTINELA) {
            enfileirar(&fila, nodo->dir);
        }
    }
}

struct fila* criarFila() {
    struct fila* fila = (struct fila*)malloc(sizeof(struct fila));
    if (!fila) {
        matarProgramaFaltaMemoria();
    }

    fila->inicio = NULL;
    fila->fim = NULL;

    return fila;
}

void enfileirar(struct fila** fila, struct nodo* nodo) {
    struct fila_nodo* novo_fila_nodo = (struct fila_nodo*)malloc(sizeof(struct fila_nodo));
    if (!novo_fila_nodo) {
        matarProgramaFaltaMemoria();
    }

    novo_fila_nodo->nodo = nodo;
    novo_fila_nodo->prox = NULL;

    if ((*fila)->inicio != NULL) {
        (*fila)->fim->prox = novo_fila_nodo;
        (*fila)->fim = novo_fila_nodo;
    } else {
        (*fila)->inicio = novo_fila_nodo;
        (*fila)->fim = novo_fila_nodo;
    }
}

struct nodo* desenfileirar(struct fila** fila) {
    struct fila_nodo* inicio_fila_nodo = NULL;
    struct nodo* nodo = NULL;
    if ((*fila)->inicio != NULL) {
        inicio_fila_nodo = (*fila)->inicio;
        (*fila)->inicio = (*fila)->inicio->prox;
        if ((*fila)->inicio == NULL) {
            (*fila)->fim = NULL;
        }
    } else {
        return NULL;
    }

    nodo = inicio_fila_nodo->nodo;
    free(inicio_fila_nodo);

    return nodo;
}

struct nodo* criarNodo(int chave) {
    struct nodo* novo_nodo = (struct nodo*)malloc(sizeof(struct nodo));
    if (!novo_nodo) {
        matarProgramaFaltaMemoria();
    }

    novo_nodo->chave = chave;
    novo_nodo->cor = VERMELHO;
    novo_nodo->esq = SENTINELA;
    novo_nodo->dir = SENTINELA;
    novo_nodo->pai = SENTINELA;

    return novo_nodo;
}

void insertFixup(struct nodo** raiz, struct nodo* novo_nodo) {
    while (novo_nodo != *raiz && novo_nodo->pai->cor == VERMELHO) {
        struct nodo* avo = novo_nodo->pai->pai;

        if (novo_nodo->pai == avo->esq) {
            struct nodo* tio = avo->dir;

            if (tio->cor == VERMELHO) {
                novo_nodo->pai->cor = PRETO;
                tio->cor = PRETO;
                avo->cor = VERMELHO;
                novo_nodo = avo;
            } else {
                 if (novo_nodo == novo_nodo->pai->dir) {
                    novo_nodo = novo_nodo->pai;
                    rotacaoEsquerda(raiz, novo_nodo);
                 }
                 novo_nodo->pai->cor = PRETO;
                 avo->cor = VERMELHO;
                 rotacaoDireita(raiz, avo);
            }
        } else {
            struct nodo* tio = avo->esq;

            if (tio->cor == VERMELHO) {
                novo_nodo->pai->cor = PRETO;
                tio->cor = PRETO;
                avo->cor = VERMELHO;
                novo_nodo = avo;
            } else {
                 if (novo_nodo == novo_nodo->pai->esq) {
                    novo_nodo = novo_nodo->pai;
                    rotacaoDireita(raiz, novo_nodo);
                 }
                 novo_nodo->pai->cor = PRETO;
                 avo->cor = VERMELHO;
                 rotacaoEsquerda(raiz, avo);
            }
        }
    }
    (*raiz)->cor = PRETO;
}

void rotacaoEsquerda(struct nodo** raiz, struct nodo* nodo_pivo) {
    struct nodo* filho_dir = nodo_pivo->dir;

    nodo_pivo->dir = filho_dir->esq;
    if (filho_dir->esq != SENTINELA) {
        filho_dir->esq->pai = nodo_pivo;
    }

    filho_dir->pai = nodo_pivo->pai;

    if (nodo_pivo->pai == SENTINELA) {
        *raiz = filho_dir;
    } else if (nodo_pivo->pai->esq == nodo_pivo) {
        nodo_pivo->pai->esq = filho_dir;
    } else {
        nodo_pivo->pai->dir = filho_dir;
    }

    filho_dir->esq = nodo_pivo;
    nodo_pivo->pai = filho_dir;
}

void rotacaoDireita(struct nodo** raiz, struct nodo* nodo_pivo) {
        struct nodo* filho_esq = nodo_pivo->esq;

    nodo_pivo->esq = filho_esq->dir;
    if (filho_esq->dir != SENTINELA) {
        filho_esq->dir->pai = nodo_pivo;
    }

    filho_esq->pai = nodo_pivo->pai;

    if (nodo_pivo->pai == SENTINELA) {
        *raiz = filho_esq;
    } else if (nodo_pivo->pai->dir == nodo_pivo) {
        nodo_pivo->pai->dir = filho_esq;
    } else {
        nodo_pivo->pai->esq = filho_esq;
    }

    filho_esq->dir = nodo_pivo;
    nodo_pivo->pai = filho_esq;
}