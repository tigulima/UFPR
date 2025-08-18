#include <stdio.h>
#include <stdlib.h>

#define TAM_NOME 100

struct pessoa {
    char nome[TAM_NOME];
    short idade;
    int64_t cpf;
};

struct dicionario_pessoa {
    // Não entendo 100% o ponteiro para ponteiro
    struct pessoa** pessoas;
    size_t numItens;
};

void inicializar(struct dicionario_pessoa* dict) {
    dict->pessoas = malloc(sizeof(struct pessoa*));
    if (!dict->pessoas) {
        fprintf(stderr, "Falha ao alocar memória para o dicionário.\n");
        exit(EXIT_FAILURE);
    }
    dict->pessoas[0] = NULL; // Inicializa o primeiro elemento como NULL
    dict->numItens = 0;
};

int inserir(struct pessoa* pessoa, struct dicionario_pessoa* dict) {
    // alocamos espaço dinâmicamente
    dict->pessoas = realloc(dict->pessoas, sizeof(struct pessoa*) * (dict->numItens + 1));

    if (!dict->pessoas) {
        return 0; // Falha de alocação
    }
    dict->pessoas[dict->numItens] = pessoa;
    dict->numItens++;
    return 1;
};

struct pessoa* remover(int64_t* chave, struct dicionario_pessoa* dict) {
    for (size_t i = 0; i < dict->numItens; i++) {
        if (dict->pessoas[i]->cpf == *chave) {
            struct pessoa* removida = dict->pessoas[i];
            // Desloca os elementos para preencher o espaço vazio
            for (size_t j = i; j < dict->numItens - 1; j++) {
                dict->pessoas[j] = dict->pessoas[j + 1];
            }
            dict->numItens--;
            return removida;
        }
    }
    return NULL;
};

struct pessoa* buscar(int64_t* chave, struct dicionario_pessoa* dict) {
    for (size_t i = 0; i < dict->numItens; i++) {
        if (dict->pessoas[i]->cpf == *chave) {
            return dict->pessoas[i];
        }
    }
    return NULL;
};

int destruir(struct dicionario_pessoa* dict) {
    if (dict->numItens == 0) {
        return 0;
    }

    // for (size_t i = 0; i < dict->numItens; i++) {
    //     free(dict->pessoas[i]);
    // }

    free(dict->pessoas);
    dict->numItens = 0;

    return 1;
};

int main() {
    struct dicionario_pessoa dict;
    inicializar(&dict);
    
    struct pessoa* p1 = malloc(sizeof(struct pessoa));
    snprintf(p1->nome, TAM_NOME, "Alice");
    p1->idade = 30;
    p1->cpf = 12345678901;

    inserir(p1, &dict);

    struct pessoa* p2 = malloc(sizeof(struct pessoa));
    snprintf(p2->nome, TAM_NOME, "Bob");
    p2->idade = 25;
    p2->cpf = 98765432100;

    inserir(p2, &dict);

    int64_t chaveBusca = 12345678901;
    struct pessoa* resultado = buscar(&chaveBusca, &dict);
    if (resultado) {
        printf("Pessoa encontrada: %s, Idade: %d, CPF: %lld\n", resultado->nome, resultado->idade, resultado->cpf);
    } else {
        printf("Pessoa não encontrada.\n");
    }

    destruir(&dict);
    free(p1);
    free(p2);
    return 0;
};