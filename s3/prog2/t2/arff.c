#include "arff.h"

atributo *aloca_atributos(int quantidade)
{

    atributo *arff;

    if (!(arff = malloc(sizeof(atributo) * quantidade)))
    {
        fprintf(stderr, "Erro ao alocar memória");
        exit(5);
    }

    return arff;
}

void libera_atributos(atributo *infos, int quantidade)
{
    for (int i = 0; i < quantidade; i++)
    {
        free(infos[i].rotulo);
        free(infos[i].tipo);
        free(infos[i].categorias);
    }
    free(infos);
};

void exibe_atributos(atributo *infos, int quantidade)
{
    // Fun��o do A1 (com modifica��es para o atributo de categorias)
    if (infos == 0)
    {
        printf("O arquivo ARFF fornecido é inválido!\n");
        exit(0);
    }

    printf("==== ATRIBUTOS DO ARQUIVO ====\n");
    for (int i = 0; i < quantidade; i++)
    {
        printf("-> Atributo #%d\n", i + 1);
        printf("Rótulo: %s\n", infos[i].rotulo);
        printf("Tipo: %s\n", infos[i].tipo);
        if (infos[i].categorias)
        {
            printf("Categorias: ");
            for (int j = 0; infos[i].categorias[j] != NULL; j++)
                printf("%s ", infos[i].categorias[j]);

            printf("\n");
        }
        if (i < quantidade - 1)
            printf("------------------------------\n");
    }
    printf("===============================\n");
}

int conta_atributos(FILE *arff)
{
    // Fun��o do A1
    char linha[STR_TAM_MAX];
    int tam = 0;

    while (fgets(linha, sizeof(linha), arff) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';

        if (strncmp(linha, "@attribute", 10) == 0)
            tam++;

        if (strncmp(linha, "@data", 5) == 0)
            break;
    }

    rewind(arff);

    return tam;
}

void tira_chaves(char *str)
{
    int j = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != '{' && str[i] != '}')
        {
            str[j] = str[i];
            j++;
        }
    }

    str[j] = '\0';
}

void processa_categorias(atributo *elemento, char *categorias)
{
    // Recbe uma string com as categorias e atualiza o elemento com um vetor de strings (modificar a struct)
    char *token;
    token = strtok(categorias, ",");
    int i = 0;

    while (token != NULL)
    {
        if (!(elemento->categorias = realloc(elemento->categorias, sizeof(char *) * (i + 1))))
        {
            fprintf(stderr, "Erro ao alocar memória");
            exit(5);
        }

        tira_chaves(token);
        elemento->categorias[i] = strdup(token);
        token = strtok(NULL, ",");
        i++;
    }

    elemento->categorias[i] = NULL;
}

atributo *processa_atributos(FILE *arff, int quantidade)
{
    // Fun��o do A1 (com modifica��es para o atributo de categorias)
    char linha[STR_TAM_MAX];
    int dadoLido = 0;

    atributo *atr = aloca_atributos(conta_atributos(arff));

    for (int i = 0; fgets(linha, sizeof(linha), arff) != NULL; i++)
    {
        linha[strcspn(linha, "\n")] = '\0';

        if (strncmp(linha, "@attribute", 10) == 0)
        {

            char *token;
            token = strtok(linha, " ");

            // le @atributo
            token = strtok(NULL, " ");

            // Processa Rotulo
            atr[i].rotulo = strdup(token);

            token = strtok(NULL, " ");

            // Processa Tipo
            if (strcmp(token, "numeric") && strcmp(token, "string"))
            {
                atr[i].tipo = strdup("categoric");
                processa_categorias(&atr[i], token);
            }
            else
            {
                atr[i].tipo = strdup(token);
                atr[i].categorias = NULL;
            }
        }
        else if (strncmp(linha, "@data", 5) == 0)
            dadoLido = 1;
    }

    rewind(arff);

    return atr;
}

void valida_arff(FILE *arff, atributo *atributos, int quantidade)
{
    // Recebe um arquivo arff com ponteiro de leitura antes do "@data"; passa por todas as linhas de dados e valida cada elementos de cada coluna em
    // rela��o ao vetor de atributos tamb�m fornecido como argumento.`

    char linha[STR_TAM_MAX];
    int dadoLido = 0;
    int tam_linha = 0;

    int int_test;
    char *eh_int;

    for (int i = 0; fgets(linha, sizeof(linha), arff) != NULL; i++)
    {
        linha[strcspn(linha, "\n")] = '\0';

        if (strncmp(linha, "@data", 5) == 0)
        {
            dadoLido = 1;
        }
        else if (dadoLido)
        {
            char *token;
            token = strtok(linha, ",");

            for (int j = 0; token != NULL; j++)
            {
                if (strcmp(atributos[j].tipo, "numeric") == 0)
                {
                    int_test = strtod(token, &eh_int);

                    if (*eh_int != '\0')
                    {
                        printf("Erro linha %d: não é numérico!\n", i + 1);
                        return;
                    }
                }

                tam_linha++;
                token = strtok(NULL, ",");
            }

            if (tam_linha != quantidade)
            {
                printf("Erro linha %d: quantidade de atributos inválida!\n", i + 1);
                return;
            }

            tam_linha = 0;
        }
    }

    printf("\nArquivo válido!\n");

    rewind(arff);
}
