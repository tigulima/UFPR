#ifndef __LOG__
#define __LOG__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "arff.h"

#define STR_TAM_MAX 1024

typedef struct
{
    char *str;
    double num;
} ocorrencia;

enum
{
    SRC_ADD,
    DES_ADD,
    PKT_ID,
    FROM_NODE,
    TO_NODE,
    PKT_TYPE,
    PKT_SIZE,
    FLAGS,
    FID,
    SEQ_NUMBER,
    NUMBER_OF_PKT,
    NUMBER_OF_BYTE,
    NODE_NAME_FROM,
    NODE_NAME_TO,
    PKT_IN,
    PKT_OUT,
    PKT_R,
    PKT_DELAY_NODE,
    PKT_RATE,
    BYTE_RATE,
    PKT_AVG_SIZE,
    UTILIZATION,
    PKT_DELAY,
    PKT_SEND_TIME,
    PKT_RESEVED_TIME,
    FIRST_PKT_SENT,
    LAST_PKT_RESEVED,
    PKT_CLASS,
    NUM_COLUNAS,
};

void separa_colunas(char *colunas[NUM_COLUNAS], char linha[STR_TAM_MAX]);

void gera_ataques(FILE *arff, atributo *atributos, int quantidade);

void gera_entidades(FILE *arff, atributo *atributos, int quantidade);

void gera_tamanho(FILE *arff, atributo *atributos, int quantidade);

void gera_blacklist(FILE *arff, atributo *atributos, int quantidade);

#endif