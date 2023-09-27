#include "log.h"

void cria_arquivo(char *nome, char *conteudo)
{
    // Cria um arquivo com o nome e conteudo fornecidos
    FILE *arquivo = fopen(nome, "w");

    if (!arquivo)
    {
        fprintf(stderr, "Erro ao criar arquivo %s\n", nome);
        exit(3);
    }

    // Adiciona o conteudo no arquivo criado
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

    // pula linhas antes do @data
    for (int i = 0; fgets(linha, sizeof(linha), arff) != NULL; i++)
    {
        linha[strcspn(linha, "\n")] = '\0';

        if (strncmp(linha, "@data", 5) == 0)
            dadoLido = 1;
        else if (dadoLido)
            // Separa as ocorrencias importantes para o documento a ser gerado
            op(ocorrencias, qt, linha);
    }

    rewind(arff);
}

void separa_colunas(char *colunas[NUM_COLUNAS], char linha[STR_TAM_MAX])
{
    // Transforma a linha em um vetor de strings
    char *token = strtok(linha, ",");

    for (int i = 0; i < NUM_COLUNAS && token != NULL; i++)
    {
        colunas[i] = strdup(token);
        token = strtok(NULL, ",");
    }
}

void inicializa_ocorrencias(ocorrencia **ocorrencias, int *qt, char *str, int num)
{
    // Se o vetor de ocorrencias estiver vazio, aloca memoria para a primeira ocorrencia
    if (!(*ocorrencias = malloc(sizeof(ocorrencia))))
    {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    // Cria uma nova ocorrencia e adiciona o ataque novo
    (*ocorrencias)[*qt].str = str;
    (*ocorrencias)[*qt].num = num;
    (*qt)++;
}

void incrementa_ocorrencias(ocorrencia **ocorrencias, int *qt, char *str, int num)
{
    // Realoca e adiciona ocorrencias novas
    if (!(*ocorrencias = realloc(*ocorrencias, sizeof(ocorrencia) * (*qt + 1))))
    {
        printf("Erro ao realocar memoria!\n");
        exit(1);
    };

    (*ocorrencias)[*qt].str = str;
    (*ocorrencias)[*qt].num = num;
    (*qt)++;
}

// ATAQUES

void calcula_ataques(ocorrencia **ocorrencias, int *qt_ataques, char *linha)
{
    char *colunas[NUM_COLUNAS];
    separa_colunas(colunas, linha);

    // Se PKT_CLASS não for "Normal", trata o ataque
    if (strcmp(colunas[PKT_CLASS], "Normal"))
    {
        int existe = 0;

        if (*qt_ataques == 0)
            inicializa_ocorrencias(ocorrencias, qt_ataques, strdup(colunas[PKT_CLASS]), 1);

        // Incrementa o numero de ocorrencias para cada ataque existente
        for (int i = 0; i < *qt_ataques; i++)
        {
            if (!strcmp((*ocorrencias)[i].str, colunas[PKT_CLASS]))
            {
                existe = 1;
                (*ocorrencias)[i].num++;
            }
        }

        if (!existe)
            incrementa_ocorrencias(ocorrencias, qt_ataques, strdup(colunas[PKT_CLASS]), 1);
    }

    // Libera as colunas alocadas
    for (int i = 0; i < NUM_COLUNAS; i++)
        free(colunas[i]);
}

void gera_ataques(FILE *arff, atributo *atributos, int quantidade)
{
    printf("\n-> Gerando relatorio de ataques... ");

    // Aloca ocorrecias para o vetor de ocorrencias,
    // É um ponteiro para ponteiro por conta do realloc
    ocorrencia **ocorrencias = malloc(sizeof(ocorrencia));
    if (!ocorrencias)
    {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    int qt_ocorrencias = 0;

    processa_ocorrencias(arff, ocorrencias, &qt_ocorrencias, calcula_ataques);

    char text[FILE_SIZE_LIMIT] = "";

    // Cria uma unica string com os dados processados
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

    // Se PKT_CLASS não for "Normal", trata o ataque
    if (strcmp(colunas[PKT_CLASS], "Normal"))
    {
        int existe = 0;

        if (*qt_entidades == 0)
            inicializa_ocorrencias(ocorrencias, qt_entidades, strdup(colunas[SRC_ADD]), 1);

        // Incrementa o numero de ocorrencias para cada ataque existente
        for (int j = 0; j < *qt_entidades; j++)
        {
            if (!strcmp((*ocorrencias)[j].str, colunas[SRC_ADD]))
            {
                existe = 1;
                (*ocorrencias)[j].num++;
            }
        }

        if (!existe)
            incrementa_ocorrencias(ocorrencias, qt_entidades, strdup(colunas[SRC_ADD]), 1);
    }

    // Libera as colunas alocadas
    for (int i = 0; i < NUM_COLUNAS; i++)
        free(colunas[i]);
}

void gera_entidades(FILE *arff, atributo *atributos, int quantidade)
{
    printf("\n-> Gerando relatorio de entidades... ");

    // Aloca ocorrecias para o vetor de ocorrencias,
    // É um ponteiro para ponteiro por conta do realloc
    ocorrencia **ocorrencias = malloc(sizeof(ocorrencia));
    if (!ocorrencias)
    {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    int qt_ocorrencias = 0;

    processa_ocorrencias(arff, ocorrencias, &qt_ocorrencias, calcula_entidades);

    char text[FILE_SIZE_LIMIT] = "";

    // Cria uma unica string com os dados processados
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

    // Cria uma unica string com os dados processados
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

    // Se PKT_CLASS não for "Normal", trata o ataque
    if (strcmp(colunas[PKT_CLASS], "Normal"))
    {
        int existe = 0;

        if (*qt_ataques == 0)
            inicializa_ocorrencias(ocorrencias, qt_ataques, strdup(colunas[PKT_CLASS]), atof(colunas[PKT_AVG_SIZE]));

        // Incrementa o numero de ocorrencias para cada ataque existente
        for (int i = 0; i < *qt_ataques && existe == 0; i++)
        {
            if (!strcmp((*ocorrencias)[i].str, colunas[PKT_CLASS]))
            {
                existe = 1;
                (*ocorrencias)[i].num = ((*ocorrencias)[i].num + atof(colunas[PKT_AVG_SIZE])) / 2;
            }
        }

        if (!existe)
            incrementa_ocorrencias(ocorrencias, qt_ataques, strdup(colunas[PKT_CLASS]), atof(colunas[PKT_AVG_SIZE]));
    }

    // Libera as colunas alocadas
    for (int i = 0; i < NUM_COLUNAS; i++)
        free(colunas[i]);
}

void gera_tamanho(FILE *arff, atributo *atributos, int quantidade)
{
    printf("\n-> Gerando relatorio de tamanho... ");

    // Aloca ocorrecias para o vetor de ocorrencias,
    // É um ponteiro para ponteiro por conta do realloc
    ocorrencia **ocorrencias = malloc(sizeof(ocorrencia));
    int qt_ocorrencias = 0;

    processa_ocorrencias(arff, ocorrencias, &qt_ocorrencias, calcula_tamanho);

    char text[FILE_SIZE_LIMIT] = "";

    // Cria uma unica string com os dados processados
    for (int i = 0; i < qt_ocorrencias; i++)
    {
        char *linha = malloc(sizeof(char) * 1024);
        sprintf(linha, "%s;%.0f\n", (*ocorrencias)[i].str, (*ocorrencias)[i].num);
        strcat(text, linha);
        free(linha);
    }

    // Cria uma unica string com os dados processados
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

    // Se PKT_CLASS não for "Normal", trata o ataque
    if (strcmp(colunas[PKT_CLASS], "Normal"))
    {
        int existe = 0;

        if (*qt_ataques == 0)
            inicializa_ocorrencias(ocorrencias, qt_ataques, strdup(colunas[SRC_ADD]), 1);

        // Incrementa o numero de ocorrencias para cada ataque existente
        for (int i = 0; i < *qt_ataques && existe == 0; i++)
        {
            if (!strcmp((*ocorrencias)[i].str, colunas[SRC_ADD]))
            {
                existe = 1;
                (*ocorrencias)[i].num++;
            }
        }

        if (!existe)
            incrementa_ocorrencias(ocorrencias, qt_ataques, strdup(colunas[SRC_ADD]), 1);
    }

    // Libera as colunas alocadas
    for (int i = 0; i < NUM_COLUNAS; i++)
        free(colunas[i]);
}

void gera_blacklist(FILE *arff, atributo *atributos, int quantidade)
{
    printf("\n-> Gerando relatorio de blacklist... ");

    // Aloca ocorrecias para o vetor de ocorrencias,
    // É um ponteiro para ponteiro por conta do realloc
    ocorrencia **ocorrencias = malloc(sizeof(ocorrencia));
    int qt_ocorrencias = 0;

    processa_ocorrencias(arff, ocorrencias, &qt_ocorrencias, calcula_blacklist);

    char text[FILE_SIZE_LIMIT] = "";

    // Cria uma unica string com os dados processados
    for (int i = 0; i < qt_ocorrencias; i++)
    {
        char *linha = malloc(sizeof(char) * 1024);
        sprintf(linha, "%s\n", (*ocorrencias)[i].str);
        strcat(text, linha);
        free(linha);
    }

    // Cria uma unica string com os dados processados
    printf("Arquivo BLACKLIST.bl criado!\n\n");
    cria_arquivo("BLACKLIST.bl", text);

    libera_ocorrencia(ocorrencias, qt_ocorrencias);
    rewind(arff);
}