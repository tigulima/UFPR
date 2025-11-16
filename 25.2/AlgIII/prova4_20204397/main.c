#include "kdtree.h"
#include <stdio.h>
#include <stdlib.h>

static void matarProgramaErroLeitura() {
    fprintf(stderr, "Erro na leitura dos dados.");
    exit(1);
}

static void lerPontos(unsigned int K, float *ponto) {
    for (unsigned int j = 0; j < K; j++) {
        if (scanf("%f", &ponto[j]) != 1) {
            free(ponto);
            matarProgramaErroLeitura();
        }
    }
}

static void carregarPontosNaArvore(struct kdtree *arvore, unsigned int N, unsigned int K) {
    for (unsigned int i = 0; i < N; i++) {
        float *ponto = (float *)malloc(K * sizeof(float));
        if (ponto == NULL) {
            matarProgramaFaltaMemoria();
        }
        lerPontos(K, ponto);
        int classe;
        if (scanf("%d", &classe) != 1) {
            free(ponto);
            matarProgramaErroLeitura();
        }

        inserir(arvore, ponto, classe);
        free(ponto);
    }
}

int main() {
    unsigned int n, k;

    printf("Insira N e K.\n");
    if (scanf("%u %u", &n, &k) != 2) {
        matarProgramaErroLeitura();
    }
    if (k == 0 || n == 0) {
        matarProgramaErroLeitura();
    }

    struct kdtree *arvore = criarArvore(k);

    printf("Insira os pontos.\n");
    carregarPontosNaArvore(arvore, n, k);
    printf("Árvore construída.\n");

    char op;
    scanf(" %c", &op);
    while (op != 'f') {
        switch (op) {
            case 'b':
                {
                    float *ponto = (float *)malloc(k * sizeof(float));
                    if (ponto == NULL) {
                        matarProgramaFaltaMemoria();
                    }
                    lerPontos(k, ponto);

                    struct nodo *resultado = buscar(arvore, ponto);

                    if (resultado != NULL) {
                        printf("Encontrado. Classe %d.\n", resultado->classe);
                    } else {
                        printf("Não encontrado.\n");
                    }

                    free(ponto);
                    break;
                }
            case 'l':
                {
                    imprimirEmLargura(arvore);
                    break;
                }
            case 'z':
                {
                    unsigned int z;
                    if (scanf("%u", &z) != 1) {
                        matarProgramaErroLeitura();
                    }

                    float *ponto = (float *)malloc(k * sizeof(float));
                    if (ponto == NULL) {
                        matarProgramaFaltaMemoria();
                    }
                    lerPontos(k, ponto);

                    struct lista_vizinhos *vizinhos = zVizinhos(arvore, ponto, z);

                    printf("Vizinhos mais próximos:\n");
                    for (int i = 0; i < vizinhos->tam; i++) {
                        struct nodo *v = vizinhos->candidatos[i].nodo;
                        
                        for (int j = 0; j < k; j++) {
                            printf("%.1f%s", v->ponto[j], (j == k - 1) ? "" : ", ");
                        }
                        printf(" (classe %d), dist = %.4f\n", v->classe, vizinhos->candidatos[i].dist);
                    }

                    free(vizinhos->candidatos);
                    free(vizinhos);
                    free(ponto);
                    break;
                }
            default:
                printf("Operação inválida.\n");
                break;
        }
        scanf(" %c", &op);
    }

    destruirArvore(arvore);
    return 0;
}

