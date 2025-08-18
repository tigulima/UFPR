#include "pelucia.h"

#include <stdio.h>
#include <stdlib.h>

struct loja* criar_loja (unsigned int numero_maquinas) {
    
    struct loja *loja = malloc(sizeof(struct loja*));
    
    if (loja == NULL) {
        printf("\nNao foi possivel alocar memoria para loja!\n");
        return NULL;
    }
    
    loja->numero_maquinas = 0;
    
    struct maquina_pelucia *maq_anterior = NULL;
    struct maquina_pelucia *primeira_maquina = malloc(sizeof(struct maquina_pelucia));
    
    if (primeira_maquina == NULL) {
        printf("\nNao foi possivel alocar memoria para maquina!\n");
        return NULL;
    }
    
    primeira_maquina->id = 1;
    primeira_maquina->probabilidade = 0;
    
    primeira_maquina->anterior = NULL;
    primeira_maquina->proximo = NULL;
    
    maq_anterior = primeira_maquina;
    
    loja->numero_maquinas++;
    loja->inicio = primeira_maquina;

    maq_anterior = primeira_maquina;
    
    for(int i = 1; i < numero_maquinas; i++) {
        struct maquina_pelucia *maquina = malloc(sizeof(struct maquina_pelucia));
        
        if (!maquina) {
            printf("\nNao foi possivel alocar memoria para maquina!\n");
            return NULL;
        }
        
        maq_anterior->proximo = maquina;
        
        maquina->id = i+1;
        maquina->probabilidade = 0;
        
        maquina->anterior = maq_anterior;
        maquina->proximo = NULL;
        
        maq_anterior = maquina;
        
        loja->numero_maquinas++;
    }
    
    maq_anterior->proximo = primeira_maquina;
    primeira_maquina->anterior = maq_anterior;

    ordena_maquinas(loja);

    return loja;
}

void ordena_maquinas(struct loja *loja) {
    struct maquina_pelucia *maq = loja->inicio;
    struct maquina_pelucia *maq_aux = NULL;

    
    for(int i = 0; i < loja->numero_maquinas; i++) {
        
        for (int j = 0; j < i; j++) {
            maq = maq->proximo;
        }
        
        for(int j = i + 1; j < (loja->numero_maquinas - i); j++) {
            printf("\n%i\n", maq->id);
            if (maq->probabilidade >= maq->proximo->probabilidade) {
                maq_aux = maq;
            } else {
                maq_aux = maq->proximo;
            }
            
            maq = maq->proximo;
        }
        troca_maquinas(loja, maq_aux, i);
    }
    
    return;
}

void troca_maquinas(struct loja *loja, struct maquina_pelucia *maq_maior, int posicao) {
    struct maquina_pelucia *maq_troca = loja->inicio;
    struct maquina_pelucia *maq_aux = NULL;

    maq_aux = malloc(sizeof(struct maquina_pelucia));

    if (maq_aux == NULL) {
        printf("nNao foi possivel alocar memoria para maquina auxiliar");
        return;
    }
    
    for(int i = 0; i < posicao; i++) {
        maq_troca = maq_troca->proximo;
    }
    
    if (maq_troca->id == maq_maior->id) {
        return;
    }
    
    maq_aux->id = maq_troca->id;
    // printf("\n\nChegou aqui\n\n");
    maq_aux->probabilidade = maq_troca->probabilidade;
    maq_aux->anterior = maq_troca->anterior;
    maq_aux->proximo = maq_troca->proximo;
    
    maq_troca->id = maq_maior->id;
    maq_troca->probabilidade = maq_maior->probabilidade;
    maq_troca->anterior = maq_maior->anterior;
    maq_troca->proximo = maq_maior->proximo;

    maq_maior->id = maq_aux->id;
    maq_maior->probabilidade = maq_aux->probabilidade;
    maq_maior->anterior = maq_aux->anterior;
    maq_maior->proximo = maq_aux->proximo;

    free(maq_aux);
}

int jogar (struct loja *loja) {
    
}

void encerrar_dia (struct loja *loja) {
    
}

void destruir_loja (struct loja *loja) {

}

void escreve_maquinas (struct loja *loja) {
    struct maquina_pelucia *maq = loja->inicio;

    printf("\n\n------------\n");
    
    for(int i = 0; i < loja->numero_maquinas; i++) {
        printf("%i - ", maq->id);
        maq = maq->proximo;
    }
}