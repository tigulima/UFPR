#include "redblack.h"

#include <stdlib.h>
#include <string.h>

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

struct nodo* criarNodo(int chave) {
    struct nodo* novoNodo = (struct nodo*)malloc(sizeof(struct nodo));
    if(!novoNodo)
        matarProgramaFaltaMemoria();

    novoNodo->chave = chave;
    novoNodo->cor = 1; // Novo nodo é vermelho
    novoNodo->fe = NULL;
    novoNodo->fd = NULL;
    novoNodo->pai = NULL;

    return novoNodo;
}

struct nodo* inserir(struct nodo** raiz, int chave) {
    // Implementação da inserção em árvore rubro-negra

    struct nodo* novoNodo = criarNodo(chave);
    struct nodo* sentinela = raiz[0]->pai;

}


void redBlackInsertFixup(struct nodo* raiz) {
    
}

void rotacaoDireita(struct nodo* raiz) {

}

void rotacaoEsquerda(struct nodo* raiz) {

}