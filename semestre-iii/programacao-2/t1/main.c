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

void aloca_atributos(atributo *infos){
    char *a = "a";
    char *b = "b";
    char *c = "c";


    if (!(infos = malloc(sizeof(atributo))))
        exit(3);

    infos->rotulo = a;
    infos->tipo = b;
    infos->categorias = c;
}

void preenche_atributos(atributo *infos){
    char rotulo[STR_TAM_MAX + 1];
    char tipo[STR_TAM_MAX + 1];
    char categorias[STR_TAM_MAX + 1];
    
    aloca_atributos(infos);

    printf("Rotulo: ");
    scanf("%[^\n]", rotulo);
    getchar();

    printf("Tipo: ");
    scanf("%[^\n]", tipo);
    getchar();

    printf("Categorias: ");
    scanf("%[^\n]", categorias);
    getchar();

    // infos->rotulo = rotulo;
    // infos->tipo = tipo;
    // infos->categorias = categorias;

    printf("Foi lido: \n");
    printf("Rotulo: \n");
    puts(infos->rotulo);
    // printf("Tipo: %s\n", infos->tipo);
    // printf("Categorias lido: %s\n", infos->categorias);

    return;
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
    // VOC� DEVE IMPLEMENTAR ESTA FUN��O COMO PARTE DO A1!
}

atributo* processa_atributos(FILE *arff){
    // VOC� DEVE IMPLEMENTAR ESTA FUN��O COMO PARTE DO A1!
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

    preenche_atributos(atr);

    // VOC� DEVE IMPLEMENTAR AS ROTINAS NECESS�RIAS E A CHAMADA DE FUN��ES PARA PROCESSAR OS ATRIBUTOS ARFF AQUI

    if (exibicao){
        // VOC� DEVE CHAMAR A FUN��O DE EXIBI��O AQUI (USE A FUN��O exibe_atributos)
        // exibe_atributos(atributos, tam);
    }

    return 0 ;
}
