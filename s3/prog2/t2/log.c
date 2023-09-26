#include "log.h"

void cria_arquivo(char *nome, char *conteudo)
{
    FILE *arquivo = fopen(nome, "w");

    if (!arquivo)
    {
        fprintf(stderr, "Erro ao criar arquivo %s\n", nome);
        exit(3);
    }

    fprintf(arquivo, "%s", conteudo);
    fclose(arquivo);
}

void libera_ocorrencia(ocorrencia **ocorrencias, int qt)
{
    for (int i = 0; i < qt; i++)
        free((*ocorrencias)[i].str);
    free(*ocorrencias);
    free(ocorrencias);
}

void processa_ocorrencias(FILE *arff, ocorrencia **ocorrencias, int *qt, void (*op)(ocorrencia **, int *, char *))
{
    char linha[STR_TAM_MAX];
    int dadoLido = 0;

    for (int i = 0; fgets(linha, sizeof(linha), arff) != NULL; i++)
    {
        linha[strcspn(linha, "\n")] = '\0';

        if (strncmp(linha, "@data", 5) == 0)
        {
            dadoLido = 1;
        }
        else if (dadoLido)
        {
            op(ocorrencias, qt, linha);
        }
    }

    rewind(arff);
}

void separa_colunas(char *colunas[NUM_COLUNAS], char linha[STR_TAM_MAX])
{
    char *token = strtok(linha, ",");

    for (int i = 0; i < NUM_COLUNAS; i++)
    {
        colunas[i] = strdup(token);
        token = strtok(NULL, ",");
    }
    colunas[NUM_COLUNAS] = NULL;
}

// ATAQUES

void calcula_ataques(ocorrencia **ocorrencias, int *qt_ataques, char *linha)
{
    char *colunas[NUM_COLUNAS];
    separa_colunas(colunas, linha);

    if (strcmp(colunas[PKT_CLASS], "Normal"))
    {
        int existe = 0;

        for (int i = 0; i < *qt_ataques && existe == 0; i++)
        {
            if (!strcmp((*ocorrencias)[i].str, colunas[PKT_CLASS]))
            {
                existe = 1;
                (*ocorrencias)[i].num++;
            }
        }

        if (!existe)
        {
            if (!(*ocorrencias = realloc(*ocorrencias, sizeof(ocorrencia) * (*qt_ataques + 1))))
            {
                printf("Erro ao realocar memoria!\n");
                exit(1);
            };

            (*ocorrencias)[*qt_ataques].str = strdup(colunas[PKT_CLASS]);
            (*ocorrencias)[*qt_ataques].num = 1;

            (*qt_ataques)++;
        }
    }

    for (int i = 0; i < NUM_COLUNAS; i++)
        free(colunas[i]);
}

void gera_ataques(FILE *arff, atributo *atributos, int quantidade)
{
    ocorrencia **ocorrencias = malloc(sizeof(ocorrencia));
    if (!ocorrencias)
    {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    int qt_ocorrencias = 0;

    processa_ocorrencias(arff, ocorrencias, &qt_ocorrencias, calcula_ataques);

    char text[1024 * 1024] = "";

    for (int i = 0; i < qt_ocorrencias; i++)
    {
        char *linha = malloc(sizeof(char) * 1024);
        sprintf(linha, "%s;%.0f\n", (*ocorrencias)[i].str, (*ocorrencias)[i].num);
        strcat(text, linha);
        free(linha);
    }

    printf("Arquivo R_ATAQUES.txt criado!\n");
    cria_arquivo("R_ATAQUES.txt", text);

    libera_ocorrencia(ocorrencias, qt_ocorrencias);
    rewind(arff);
}

// ENTIDADES

void calcula_entidades(ocorrencia **ocorrencias, int *qt_entidades, char *linha)
{

    char *colunas[NUM_COLUNAS];
    separa_colunas(colunas, linha);

    if (strcmp(colunas[PKT_CLASS], "Normal"))
    {
        int existe = 0;

        for (int j = 0; j < *qt_entidades; j++)
        {
            if (!strcmp((*ocorrencias)[j].str, colunas[SRC_ADD]))
            {
                existe = 1;
                (*ocorrencias)[j].num++;
            }
        }

        if (!existe)
        {
            if (!(*ocorrencias = realloc(*ocorrencias, sizeof(ocorrencia) * (*qt_entidades + 1))))
            {
                printf("Erro ao realocar memoria!\n");
                exit(1);
            }
            (*ocorrencias)[*qt_entidades].str = strdup(colunas[SRC_ADD]);
            (*ocorrencias)[*qt_entidades].num = 1;
            (*qt_entidades)++;
        }
    }

    for (int i = 0; i < NUM_COLUNAS; i++)
        free(colunas[i]);
}

void gera_entidades(FILE *arff, atributo *atributos, int quantidade)
{
    ocorrencia **ocorrencias = malloc(sizeof(ocorrencia));
    int qt_ocorrencias = 0;

    processa_ocorrencias(arff, ocorrencias, &qt_ocorrencias, calcula_entidades);

    char text[1024 * 1024] = "";

    for (int i = 0; i < qt_ocorrencias; i++)
    {
        char *linha = malloc(sizeof(char) * 1024);
        if ((*ocorrencias)[i].num <= 5)
            sprintf(linha, "%s;potencialmente_maliciosa\n", (*ocorrencias)[i].str);
        else if ((*ocorrencias)[i].num > 5)
            sprintf(linha, "%s;maliciosa\n", (*ocorrencias)[i].str);
        strcat(text, linha);
        free(linha);
    }

    printf("Arquivo R_ENTIDADES.txt criado!\n");
    cria_arquivo("R_ENTIDADES.txt", text);

    libera_ocorrencia(ocorrencias, qt_ocorrencias);
    rewind(arff);
}

// TAMANHO

void calcula_tamanho(ocorrencia **ocorrencias, int *qt_ataques, char *linha)
{
    char *colunas[NUM_COLUNAS];
    separa_colunas(colunas, linha);

    if (strcmp(colunas[PKT_CLASS], "Normal"))
    {
        int existe = 0;

        for (int i = 0; i < *qt_ataques && existe == 0; i++)
        {
            if (!strcmp((*ocorrencias)[i].str, colunas[PKT_CLASS]))
            {
                existe = 1;
                (*ocorrencias)[i].num++;
            }
        }

        if (!existe)
        {
            if (!(*ocorrencias = realloc(*ocorrencias, sizeof(ocorrencia) * (*qt_ataques + 1))))
            {
                printf("Erro ao realocar memoria!\n");
                exit(1);
            };

            (*ocorrencias)[*qt_ataques].str = strdup(colunas[PKT_CLASS]);
            (*ocorrencias)[*qt_ataques].num = atof(colunas[PKT_AVG_SIZE]);

            (*qt_ataques)++;
        }
    }

    for (int i = 0; i < NUM_COLUNAS; i++)
        free(colunas[i]);
}

void gera_tamanho(FILE *arff, atributo *atributos, int quantidade)
{
    ocorrencia **ocorrencias = malloc(sizeof(ocorrencia));
    int qt_ocorrencias = 0;

    processa_ocorrencias(arff, ocorrencias, &qt_ocorrencias, calcula_tamanho);

    char text[1024 * 1024] = "";

    for (int i = 0; i < qt_ocorrencias; i++)
    {
        char *linha = malloc(sizeof(char) * 1024);
        sprintf(linha, "%s;%.0f\n", (*ocorrencias)[i].str, (*ocorrencias)[i].num);
        strcat(text, linha);
        free(linha);
    }

    printf("Arquivo R_TAMANHO.txt criado!\n");
    cria_arquivo("R_TAMANHO.txt", text);

    libera_ocorrencia(ocorrencias, qt_ocorrencias);
    rewind(arff);
}

// BLACKLIST

void calcula_blacklist(ocorrencia **ocorrencias, int *qt_ataques, char *linha)
{
    char *colunas[NUM_COLUNAS];
    separa_colunas(colunas, linha);

    if (strcmp(colunas[PKT_CLASS], "Normal"))
    {
        int existe = 0;

        for (int i = 0; i < *qt_ataques && existe == 0; i++)
        {
            if (!strcmp((*ocorrencias)[i].str, colunas[SRC_ADD]))
            {
                existe = 1;
                (*ocorrencias)[i].num++;
            }
        }

        if (!existe)
        {
            if (!(*ocorrencias = realloc(*ocorrencias, sizeof(ocorrencia) * (*qt_ataques + 1))))
            {
                printf("Erro ao realocar memoria!\n");
                exit(1);
            };

            (*ocorrencias)[*qt_ataques].str = strdup(colunas[SRC_ADD]);
            (*ocorrencias)[*qt_ataques].num = 1;

            (*qt_ataques)++;
        }
    }

    for (int i = 0; i < NUM_COLUNAS; i++)
        free(colunas[i]);
}

void gera_blacklist(FILE *arff, atributo *atributos, int quantidade)
{
    ocorrencia **ocorrencias = malloc(sizeof(ocorrencia));
    int qt_ocorrencias = 0;

    processa_ocorrencias(arff, ocorrencias, &qt_ocorrencias, calcula_blacklist);

    char text[1024 * 1024] = "";

    for (int i = 0; i < qt_ocorrencias; i++)
    {
        char *linha = malloc(sizeof(char) * 1024);
        sprintf(linha, "%s\n", (*ocorrencias)[i].str);
        strcat(text, linha);
        free(linha);
    }

    printf("Arquivo BLACKLIST.bl criado!\n");
    cria_arquivo("BLACKLIST.bl", text);

    libera_ocorrencia(ocorrencias, qt_ocorrencias);
    rewind(arff);
}