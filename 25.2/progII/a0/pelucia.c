#include "pelucia.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct loja* criar_loja (unsigned int numero_maquinas) {
    srand(time(NULL));
    
    struct loja *loja = malloc(sizeof(struct loja));
    
    if (loja == NULL) {
        printf("\nNao foi possivel alocar memoria para loja!\n");
        return NULL;
    }
    
    // Cria a sentinela
    struct maquina_pelucia *sentinela = malloc(sizeof(struct maquina_pelucia));
    if (sentinela == NULL) {
        printf("\nNao foi possivel alocar memoria para sentinela!\n");
        free(loja);
        return NULL;
    }
    
    // Inicializa a sentinela (valores especiais para identificá-la)
    sentinela->id = 0;  // ID 0 indica sentinela
    sentinela->probabilidade = 0;
    sentinela->proximo = sentinela;
    sentinela->anterior = sentinela;
    
    loja->sentinela = sentinela;
    loja->numero_maquinas = 0;
    
    // Cria as máquinas e as adiciona na lista
    for(unsigned int i = 0; i < numero_maquinas; i++) {
        struct maquina_pelucia *maquina = malloc(sizeof(struct maquina_pelucia));
        
        if (!maquina) {
            printf("\nNao foi possivel alocar memoria para maquina!\n");
            destruir_loja(loja);
            return NULL;
        }
        
        maquina->id = i + 1;
        maquina->probabilidade = rand() % 101;
        
        // Insere a máquina após a sentinela (no início da lista)
        maquina->proximo = sentinela->proximo;
        maquina->anterior = sentinela;
        sentinela->proximo->anterior = maquina;
        sentinela->proximo = maquina;
        
        loja->numero_maquinas++;
    }

    ordena_maquinas(loja);

    return loja;
}

void ordena_maquinas(struct loja *loja) {
    if (loja->numero_maquinas <= 1) return;
    
    // Selection sort na lista circular com sentinela
    struct maquina_pelucia *atual = loja->sentinela->proximo;  // Primeira máquina real
    
    for (unsigned int i = 0; i < loja->numero_maquinas - 1; i++) {
        struct maquina_pelucia *maior = atual;
        struct maquina_pelucia *temp = atual->proximo;
        
        // Encontra a máquina com maior probabilidade
        for (unsigned int j = i + 1; j < loja->numero_maquinas; j++) {
            if (temp->probabilidade > maior->probabilidade) {
                maior = temp;
            }
            temp = temp->proximo;
        }
        
        // Troca os valores se necessário
        if (maior != atual) {
            unsigned int temp_id = atual->id;
            unsigned int temp_prob = atual->probabilidade;
            
            atual->id = maior->id;
            atual->probabilidade = maior->probabilidade;
            
            maior->id = temp_id;
            maior->probabilidade = temp_prob;
        }
        
        atual = atual->proximo;
    }
}

int jogar (struct loja *loja) {
    // Verifica se ainda existem máquinas
    if (loja->numero_maquinas == 0) {
        return -1; // Não há máquinas disponíveis
    }
    
    // Escolhe uma máquina aleatoriamente
    int maquina_escolhida = rand() % loja->numero_maquinas;
    struct maquina_pelucia *maq = loja->sentinela->proximo;  // Primeira máquina real
    
    for (int i = 0; i < maquina_escolhida; i++) {
        maq = maq->proximo;
    }
    
    // Gera número aleatório para o jogador (0-100)
    int jogada_jogador = rand() % 101;
    
    printf("Máquina %d (probabilidade %d%%) - Jogada: %d\n", 
           maq->id, maq->probabilidade, jogada_jogador);
    
    // Se jogada do jogador < probabilidade da máquina, jogador ganha
    if (jogada_jogador < maq->probabilidade) {
        int id_ganhadora = maq->id;
        
        // Remove a máquina da lista circular
        maq->anterior->proximo = maq->proximo;
        maq->proximo->anterior = maq->anterior;
        
        free(maq);
        loja->numero_maquinas--;
        
        return id_ganhadora;
    }
    
    return 0; // Jogador perdeu
}

void encerrar_dia (struct loja *loja) {
    printf("\n===== FIM DO DIA =====\n");
    printf("Máquinas restantes na loja:\n");
    
    if (loja->numero_maquinas == 0) {
        printf("Nenhuma máquina restante - todas foram ganhas!\n");
    } else {
        escreve_maquinas(loja);
    }
}

void destruir_loja (struct loja *loja) {
    if (loja == NULL) return;
    
    // Libera todas as máquinas restantes
    while (loja->numero_maquinas > 0) {
        struct maquina_pelucia *maq = loja->sentinela->proximo;
        
        // Remove da lista circular
        maq->anterior->proximo = maq->proximo;
        maq->proximo->anterior = maq->anterior;
        
        free(maq);
        loja->numero_maquinas--;
    }
    
    // Libera a sentinela
    free(loja->sentinela);
    
    // Libera a estrutura da loja
    free(loja);
}

void escreve_maquinas (struct loja *loja) {
    if (loja->numero_maquinas == 0) {
        printf("\n\n------------\n");
        printf("Nenhuma máquina disponível\n");
        return;
    }
    
    struct maquina_pelucia *maq = loja->sentinela->proximo;  // Primeira máquina real

    printf("\n\n------------\n");
    
    for(int i = 0; i < loja->numero_maquinas; i++) {
        printf("%i - %i%%\n", maq->id, maq->probabilidade);
        maq = maq->proximo;
    }
}