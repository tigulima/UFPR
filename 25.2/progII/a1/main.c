#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gbv.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <opção> <biblioteca> [documentos...]\n", argv[0]);
        return 1;
    }

    const char *opcao = argv[1];
    const char *biblioteca = argv[2];

    Library lib;
    if (gbv_open(&lib, biblioteca) != 0) {
        printf("Erro ao abrir biblioteca %s\n", biblioteca);
        return 1;
    }

    if (strcmp(opcao, "-a") == 0) {
        for (int i = 3; i < argc; i++) {
            gbv_add(&lib, biblioteca, argv[i]);
        }
    } else if (strcmp(opcao, "-r") == 0) {
        for (int i = 3; i < argc; i++) {
            gbv_remove(&lib, biblioteca, argv[i]);
        }
    } else if (strcmp(opcao, "-l") == 0) {
        gbv_list(&lib);
    } else if (strcmp(opcao, "-v") == 0 && argc >= 4) {
        gbv_view(&lib, biblioteca, argv[3]);
    } else if (strcmp(opcao, "-o") == 0 && argc >= 4) {
        gbv_order(&lib, biblioteca, argv[3]);
    } else if (strcmp(opcao, "-z") == 0 && argc >= 4) {
        const char *biblioteca_z = gbv_derivacao(&lib, biblioteca);
        if (biblioteca_z == NULL) {
            printf("Erro ao criar biblioteca de derivação.\n");
            return 1;
        }
        for (int i = 3; i < argc; i++) {
            gbv_add(&lib, biblioteca_z, argv[i]);
        }
    } else {
        printf("Opção inválida.\n");
    }

    // Libera a memória alocada
    if (lib.docs != NULL) {
        free(lib.docs);
    }

    return 0;
}

