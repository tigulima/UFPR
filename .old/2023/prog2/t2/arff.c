#include "arff.h"

atributo *aloca_atributos(int quantidade)
{
    atributo *infos;

    if (!(infos = malloc(sizeof(atributo) * quantidade)))
    {
        fprintf(stderr, "Erro ao alocar memória");
        exit(5);
    }

    return infos;
}

void libera_atributos(atributo *infos, int quantidade)
{
    for (int i = 0; i < quantidade; i++)
    {
        free(infos[i].rotulo);
        free(infos[i].tipo);
        if (infos[i].categorias != NULL)
        {
            for (int j = 0; infos[i].categorias[j] != NULL; j++)
                free(infos[i].categorias[j]);
            free(infos[i].categorias);
        }
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

    // Incrementamos tam para cada linha que tenha @attribute
    while (fgets(linha, sizeof(linha), arff) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';

        if (!strncmp(linha, "@attribute", 10))
            tam++;
        // Para o loop se achar @data
        else if (!strncmp(linha, "@data", 5))
            break;
    }

    rewind(arff);
    return tam;
}

void tira_chaves(char *str)
{
    // Retira as chaves de uma string
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

void processa_categorias(atributo *infos, char *categorias)
{
    // Recbe uma string com as categorias e atualiza o elemento com um vetor de strings (modificar a struct)
    char *token;
    token = strtok(categorias, ",");
    int i = 0;

    // Inicializa o vetor de categorias
    if (!(infos->categorias = malloc(sizeof(char *) * (i + 1))))
    {
        fprintf(stderr, "Erro ao alocar memória");
        exit(5);
    }

    tira_chaves(token);
    infos->categorias[i] = strdup(token);
    token = strtok(NULL, ",");
    i++;

    while (token != NULL)
    {
        // Aloca mais um espaço no vetor de categorias para a categoria nova
        if (!(infos->categorias = realloc(infos->categorias, sizeof(char *) * (i + 1))))
        {
            fprintf(stderr, "Erro ao alocar memória");
            exit(5);
        }

        tira_chaves(token);
        infos->categorias[i] = strdup(token);
        token = strtok(NULL, ",");
        i++;
    }

    // Aloca mais um espaço no vetor de categorias para o NULL
    // Fazemos isso para facilitar a iteração no futuro
    if (!(infos->categorias = realloc(infos->categorias, sizeof(char *) * (i + 1))))
    {
        fprintf(stderr, "Erro ao alocar memória");
        exit(5);
    }

    infos->categorias[i] = NULL;
}

atributo *processa_atributos(FILE *arff, int quantidade)
{
    // Fun��o do A1 (com modifica��es para o atributo de categorias)

    char linha[STR_TAM_MAX];
    int dadoLido = 0;

    atributo *atr = aloca_atributos(conta_atributos(arff));

    fgets(linha, sizeof(linha), arff);
    for (int i = 0; i < quantidade && dadoLido == 0; i++)
    {
        linha[strcspn(linha, "\n")] = '\0';

        if (!strncmp(linha, "@attribute", 10))
        {
            char *token;
            token = strtok(linha, " ");

            // le @atributo
            token = strtok(NULL, " ");

            // Processa Rotulo
            if (token)
                atr[i].rotulo = strdup(token);
            else
            {
                printf("Erro linha %d: \"%s\" rótulo de atributo inválido!\n", i + 1, token);
                exit(0);
            }
            token = strtok(NULL, " ");

            // Processa Tipo
            if (token)
            {
                if (strcmp(token, "numeric") && strcmp(token, "string"))
                {
                    // Se for categoric, copia o token para o tipo e processa as categorias
                    atr[i].tipo = strdup("categoric");
                    processa_categorias(&atr[i], token);
                }
                else
                {
                    // Se for numeric ou string, copia o token para o tipo
                    atr[i].tipo = strdup(token);
                    atr[i].categorias = NULL;
                }
            }
            else
            {
                printf("Erro linha %d: \"%s\"tipo de atributo inválido!\n", i + 1, token);
                exit(0);
            }
            fgets(linha, sizeof(linha), arff);
        }
        else if (!strncmp(linha, "@data", 5))
            // Se for @data, sai do loop
            dadoLido = 1;
        else if (!strcmp(linha, ""))
        {
            // Le proxima linha. Se @data, sai do loop
            fgets(linha, sizeof(linha), arff);
            if (!strncmp(linha, "@data", 5))
                dadoLido = 1;
            else
            {
                // Ignora linha vazia
                printf("Atenção! linha %d: linha vazia!\n\n", i + 1);
                i--;
            }
        }
        else
        {
            // Retorna erro caso n�o tenha lido @attribute e @data
            printf("Erro linha %d: \"%s\" linha inválida!\n", i + 1, linha);
            exit(0);
        }
    }

    rewind(arff);
    return atr;
}

void valida_arff(FILE *arff, atributo *infos, int qt_atributos)
{
    // Recebe um arquivo arff com ponteiro de leitura antes do "@data"; passa por todas as linhas de dados e valida cada elementos de cada coluna em
    // rela��o ao vetor de atributos tamb�m fornecido como argumento.`

    printf("\n-> Validando arquivo... ");

    char linha[STR_TAM_MAX];
    int dadoLido = 0;
    int tam_linha = 0;

    char *eh_int;

    // Le linha por linha
    for (int i = 0; fgets(linha, sizeof(linha), arff) != NULL; i++)
    {
        linha[strcspn(linha, "\n")] = '\0';

        // Ignora as linhas ate encontrar @data
        if (!strncmp(linha, "@data", 5))
            dadoLido = 1;
        else if (dadoLido && !strcmp(linha, ""))
        {
            printf("Erro linha %d: linha vazia!\n", i + 1);
            return;
        }
        else if (dadoLido)
        {
            char *token;
            token = strtok(linha, ",");

            for (int j = 0; j < qt_atributos; j++)
            {
                // Nao precisamos verificar se é string pois qualquer coisa pode ser string
                if (!strcmp(infos[j].tipo, "numeric"))
                {
                    // Verifica se a string pode ser convertida para double
                    strtod(token, &eh_int);
                    if (*eh_int != '\0')
                    {
                        printf("Erro linha %d: \"%s\" não é numérico!\n", i + 1, token);
                        return;
                    }
                }
                else if (!strncmp(infos[j].tipo, "categoric", 9))
                {
                    // Verifica se a string está entre as categorias
                    int k = 0;
                    while (infos[j].categorias[k] != NULL)
                    {
                        if (!strcmp(infos[j].categorias[k], token))
                            break;
                        k++;
                    }
                    if (infos[j].categorias[k] == NULL)
                    {
                        printf("Erro linha %d: \"%s\" não é uma categoria válida!\n", i + 1, token);
                        return;
                    }
                }

                tam_linha++;
                token = strtok(NULL, ",");
            }

            // Verifica se a linha tem a quantidade correta de atributos
            if (tam_linha != qt_atributos || token != NULL)
            {
                printf("Erro linha %d: quantidade de atributos inválida!\n", i + 1);
                return;
            }

            tam_linha = 0;
        }
    }

    printf("Arquivo válido!\n");
    rewind(arff);
}
