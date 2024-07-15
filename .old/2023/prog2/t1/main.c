#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#define STR_TAM_MAX 1024

typedef struct {
    char *rotulo;
    char *tipo;
    char *categorias;
} atributo;

atributo *aloca_atributos(int tam){
    atributo *arff;

    if (!(arff = malloc(sizeof(atributo) * tam))) {
        fprintf(stderr, "Erro ao alocar memória");
        exit(5);
   	}

    return arff;
}

void libera_atributos(atributo *info, int tamanho){
    for(int i = 0; i < tamanho; i++){
        free(info[i].rotulo);
        free(info[i].tipo);
        free(info[i].categorias);
    }
    free(info);
};

void exibe_atributos(atributo *info, int tamanho){
    if (info == 0){
        printf("O arquivo ARFF fornecido é inválido!\n");
        exit(0);
    }

    printf("==== ATRIBUTOS DO ARQUIVO ====\n");
    for(int i = 0; i < tamanho; i++){
        printf("-> Atributo #%d\n", i+1);
        printf("Rótulo: %s\n", info[i].rotulo);
        printf("Tipo: %s\n", info[i].tipo);
        if (info[i].categorias) printf("Categorias: %s\n", info[i].categorias);
        if (i < tamanho-1) printf("------------------------------\n");
    }
    printf("===============================\n");
}

int conta_atributos(FILE *arff){
    char linha[STR_TAM_MAX];    
    int tam = 0;

    while(fgets(linha, sizeof(linha), arff) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';

        if (strncmp(linha, "@attribute", 10) == 0)
            tam++;
    }

    rewind(arff);

    return tam;
}

atributo *processa_atributos(FILE *arff){
    char linha[STR_TAM_MAX];
    int dadoLido = 0;

    atributo *atr = aloca_atributos(conta_atributos(arff));

    for(int i = 0; fgets(linha, sizeof(linha), arff) != NULL; i++) {
        linha[strcspn(linha, "\n")] = '\0';

        if (strncmp(linha, "@attribute", 10) == 0) {

            char *token;
            token = strtok(linha, " ");

            // Reads @atributo
            token = strtok(NULL, " ");

            // Process Rotulo
            atr[i].rotulo = strdup(token);

            token = strtok(NULL, " ");

            // Process Tipo
            if(strcmp(token, "numeric") && strcmp(token, "string")) {
                atr[i].tipo = strdup("categoric");
                atr[i].categorias = strdup(token);
            } else {
                atr[i].tipo = strdup(token);
                atr[i].categorias = NULL;
            }

        } else if (strncmp(linha, "@data", 5) == 0) {
            dadoLido = 1;
        } else {
            printf("Linha ignorada: %s\n", linha);
        }
    }

    rewind(arff);

    return atr;
}

int main(int argc, char **argv){
	int opt;
    char exibicao = 0;
    char *entrada = 0;

    while ((opt = getopt(argc, argv, "pi:")) != -1) {
        switch (opt) {
        case 'i':
            entrada = strdup(optarg);
            break;
        case 'p':
            exibicao = 1;
            break;
        default:
            fprintf(stderr, "Forma de uso: ./arff -i <arq_in> [-p]\n");
            exit(1);
        }
    }

    if (!entrada) {
        fprintf(stderr, "Forma de uso: ./arff -i <arq_in> [-p]\n");
        exit(2);
    }

    FILE *arff = fopen(entrada, "r");

    if (arff == NULL) {
        fprintf(stderr, "Erro ao abrir arquivo\n");
        exit(3);
    }

    atributo *atr;

    atr = processa_atributos(arff);

    int tam = conta_atributos(arff);

    if (exibicao)
        exibe_atributos(atr, tam);

    fclose(arff);
    libera_atributos(atr, tam);

    return 0 ;
}