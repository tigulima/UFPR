#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STR_TAM_MAX 1024

typedef struct {
    char *rotulo;
    char *tipo;
    char *categorias;
} atributo;

void aloca_atributos(atributo *infos, int tam){
    if (!(infos = malloc(sizeof(atributo) * tam))) {
        fprintf(stderr, "Erro ao alocar memória");
        exit(5);
   	}
}

void exibe_atributos(atributo *infos, int tamanho){
    if (infos == 0){
        printf("O arquivo ARFF fornecido � inv�lido!\n");
        exit(0);
    }

    printf("==== ATRIBUTOS DO ARQUIVO ====\n");
    for(int i = 0; i < tamanho; i++){
        printf("-> Atributo #%d\n", i+1);
        printf("R�tulo: %s\n", infos[i].rotulo);
        printf("Tipo: %s\n", infos[i].tipo);
        if (infos[i].categorias) printf("Categorias: %s\n", infos[i].categorias);
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

    return tam;
}

void processa_atributos(atributo *atr, FILE *arff){
    char linha[STR_TAM_MAX];
    int dadoLido = 0;
    int i = 0;

    aloca_atributos(atr, conta_atributos(arff));
	rewind(arff);

    while(fgets(linha, sizeof(linha), arff) != NULL) {
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
                if(token != "numeric" && token != "string") {
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
        i++;
    }
}

int main(int argc, char **argv){
	int opt;
    char exibicao = 0;
    char *entrada = 0;

    atributo *atr;

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

    if ( ! entrada ) {
        fprintf(stderr, "Forma de uso: ./arff -i <arq_in> [-p]\n");
        exit(2);
    }

    FILE *arff = fopen(entrada, "r");

    if (arff == NULL) {
        fprintf(stderr, "Erro ao abrir arquivo\n");
        exit(3);
    }

    processa_atributos(atr, arff);
    int tam = conta_atributos(arff);

    if (exibicao)
        exibe_atributos(atr, tam);

    fclose(arff);

    free(atr[tam].rotulo);
    free(atr[tam].tipo);
    free(atr[tam].categorias);

    return 0 ;
}
