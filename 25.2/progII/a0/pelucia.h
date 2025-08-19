#ifndef PELUCIA_H
#define PELUCIA_H

struct maquina_pelucia {
    unsigned int id;
    unsigned int probabilidade;

    struct maquina_pelucia *proximo;
    struct maquina_pelucia *anterior;
};

struct loja {
	struct maquina_pelucia *sentinela;  // Sentinela de início
	unsigned int numero_maquinas;
};

struct loja* criar_loja (unsigned int numero_maquinas);
int jogar (struct loja *loja);
void encerrar_dia (struct loja *loja);
void destruir_loja (struct loja *loja);
void ordena_maquinas(struct loja *loja);
void escreve_maquinas (struct loja *loja);

#endif
