#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOTICIAS 100

typedef struct {
    char titulo[32];
    char texto[512];
    int idade;
} Noticia;

typedef struct {
    Noticia noticias[MAX_NOTICIAS];
    int quantidade;
} FilaNoticias;

void requisita(char *titulo, char *texto) {
    getchar();
    printf("\nDigite o título: ");
    fgets(titulo, 33, stdin);
    printf("Digite o texto: ");
    fgets(texto, 513, stdin);
}

void envelheceNoticias(FilaNoticias *fila) {
    for (int i = 0; i < fila->quantidade; i++) {
        fila->noticias[i].idade++;
    }
}

void cadastraNoticia(FilaNoticias *fila) {
    if (fila->quantidade >= MAX_NOTICIAS) {
        printf("Limite de notícias alcançado!\n");
        return;
    }

    Noticia novaNoticia;
    requisita(novaNoticia.titulo, novaNoticia.texto);
    novaNoticia.idade = 0;

    fila->noticias[fila->quantidade++] = novaNoticia;
    printf("Notícia cadastrada com sucesso!\n");
}

void fechaEdicao(FilaNoticias *filaBreakingNews, FilaNoticias *filaInformes) {
    int countBreakingNews = 0;
    int countInformes = 0;

    // Conta notícias válidas de cada tipo
    for (int i = 0; i < filaBreakingNews->quantidade; i++) {
        if (filaBreakingNews->noticias[i].idade <= 3) {
            countBreakingNews++;
        }
    }

    for (int i = 0; i < filaInformes->quantidade; i++) {
        if (filaInformes->noticias[i].idade <= 3) {
            countInformes++;
        }
    }

    // Verifica critérios para seleção de notícias
    if (countBreakingNews >= 2) {
        printf("=======================================================\n");
        for (int i = 0; i < filaBreakingNews->quantidade; i++) {
            if (filaBreakingNews->noticias[i].idade <= 3) {
                printf("< %s >\n%s", filaBreakingNews->noticias[i].titulo, filaBreakingNews->noticias[i].texto);
                printf("==\n");
            }
        }
        printf("=======================================================\n");
    } else if (countBreakingNews == 1 && countInformes >= 1) {
        printf("=======================================================\n");
        for (int i = 0; i < filaBreakingNews->quantidade; i++) {
            if (filaBreakingNews->noticias[i].idade <= 3) {
                printf("< %s >\n%s", filaBreakingNews->noticias[i].titulo, filaBreakingNews->noticias[i].texto);
                printf("==\n");
            }
        }
        for (int i = 0; i < filaInformes->quantidade; i++) {
            if (filaInformes->noticias[i].idade <= 3) {
                printf("< %s >\n%s", filaInformes->noticias[i].titulo, filaInformes->noticias[i].texto);
                printf("==\n");
            }
        }
        printf("=======================================================\n");
    } else if (countBreakingNews == 0 && countInformes >= 2) {
        printf("=======================================================\n");
        for (int i = 0; i < filaInformes->quantidade; i++) {
            if (filaInformes->noticias[i].idade <= 3) {
                printf("< %s >\n%s", filaInformes->noticias[i].titulo, filaInformes->noticias[i].texto);
                printf("==\n");
            }
        }
        printf("=======================================================\n");
    } else if (countBreakingNews == 1 && countInformes == 0) {
        printf("=======================================================\n");
        for (int i = 0; i < filaBreakingNews->quantidade; i++) {
            if (filaBreakingNews->noticias[i].idade <= 3) {
                printf("< %s >\n%s", filaBreakingNews->noticias[i].titulo, filaBreakingNews->noticias[i].texto);
                printf("==\n");
            }
        }
        printf("=======================================================\n");
    } else if (countBreakingNews == 0 && countInformes == 1) {
        printf("=======================================================\n");
        for (int i = 0; i < filaInformes->quantidade; i++) {
            if (filaInformes->noticias[i].idade <= 3) {
                printf("< %s >\n%s", filaInformes->noticias[i].titulo, filaInformes->noticias[i].texto);
                printf("==\n");
            }
        }
        printf("=======================================================\n");
    } else if (countBreakingNews == 0 && countInformes == 0) {
        printf("Esta edição foi pulada por falta de notícias!\n");
    }

    // Envelhece as notícias
    envelheceNoticias(filaBreakingNews);
    envelheceNoticias(filaInformes);
}

int main() {
    FilaNoticias filaBreakingNews = { .quantidade = 0 };
    FilaNoticias filaInformes = { .quantidade = 0 };

    int opcao;
    do {
        printf("\nSelecione uma opção:\n");
        printf("(1) Cadastrar notícia\n");
        printf("(2) Fechar edição\n");
        printf("(3) Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastraNoticia(&filaBreakingNews);
                break;
            case 2:
                fechaEdicao(&filaBreakingNews, &filaInformes);
                break;
            case 3:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 3);

    return 0;
}
