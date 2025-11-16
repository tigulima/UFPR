#include "kdtree_completo.h"
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

/* Exibe menu de opcoes */
static void exibirMenu() {
    printf("\n=== MENU ===\n");
    printf("b - Buscar ponto\n");
    printf("z - Z vizinhos mais proximos\n");
    printf("i - Inserir novo ponto\n");
    printf("r - Remover ponto\n");
    printf("1 - Imprimir pre-ordem\n");
    printf("2 - Imprimir em-ordem\n");
    printf("3 - Imprimir pos-ordem\n");
    printf("4 - Imprimir por nivel\n");
    printf("h - Mostrar altura\n");
    printf("n - Contar nodos\n");
    printf("c - Listar por classe\n");
    printf("m - Mostrar minimo em dimensao\n");
    printf("f - Finalizar\n");
    printf("Opcao: ");
}

int main() {
    unsigned int n, k;

    printf("Insira N e K.\n");
    if (scanf("%u %u", &n, &k) != 2) {
        matarProgramaErroLeitura();
    }

    struct kdtree *arvore = criarArvore(k);

    printf("Insira os pontos.\n");
    carregarPontosNaArvore(arvore, n, k);
    printf("Arvore construida.\n");

    char op;
    scanf(" %c", &op);
    
    while (op != 'f') {
        switch (op) {
            /* Operacoes originais */
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
                        printf("Nao encontrado.\n");
                    }

                    free(ponto);
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

                    printf("Vizinhos mais proximos:\n");
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

            /* Novas operacoes de manipulacao */
            case 'i':
                {
                    // Insere um novo ponto na arvore
                    float *ponto = (float *)malloc(k * sizeof(float));
                    if (ponto == NULL) {
                        matarProgramaFaltaMemoria();
                    }
                    
                    printf("Digite as coordenadas e classe:\n");
                    lerPontos(k, ponto);
                    
                    int classe;
                    if (scanf("%d", &classe) != 1) {
                        free(ponto);
                        matarProgramaErroLeitura();
                    }

                    inserir(arvore, ponto, classe);
                    printf("Ponto inserido.\n");
                    
                    free(ponto);
                    break;
                }
                
            case 'r':
                {
                    // Remove um ponto da arvore
                    float *ponto = (float *)malloc(k * sizeof(float));
                    if (ponto == NULL) {
                        matarProgramaFaltaMemoria();
                    }
                    
                    printf("Digite as coordenadas do ponto a remover:\n");
                    lerPontos(k, ponto);

                    struct nodo *resultado = buscar(arvore, ponto);
                    if (resultado != NULL) {
                        remover(arvore, ponto);
                        printf("Ponto removido.\n");
                    } else {
                        printf("Ponto nao encontrado.\n");
                    }
                    
                    free(ponto);
                    break;
                }

            /* Novas operacoes de impressao */
            case '1':
                // Imprime arvore em pre-ordem
                imprimirPreOrdem(arvore);
                break;
                
            case '2':
                // Imprime arvore em ordem
                imprimirEmOrdem(arvore);
                break;
                
            case '3':
                // Imprime arvore em pos-ordem
                imprimirPosOrdem(arvore);
                break;
                
            case '4':
                // Imprime arvore por nivel (largura)
                imprimirPorNivel(arvore);
                break;

            /* Novas operacoes de informacao */
            case 'h':
                // Mostra altura da arvore
                printf("Altura da arvore: %d\n", altura(arvore));
                break;
                
            case 'n':
                // Conta total de nodos
                printf("Total de nodos: %d\n", contarNodos(arvore));
                break;

            /* Novas operacoes de consulta */
            case 'c':
                {
                    // Lista todos os pontos de uma classe
                    int classe;
                    printf("Digite a classe:\n");
                    if (scanf("%d", &classe) != 1) {
                        matarProgramaErroLeitura();
                    }
                    
                    int total = contarPorClasse(arvore, classe);
                    printf("Total de pontos: %d\n", total);
                    
                    if (total > 0) {
                        listarPorClasse(arvore, classe);
                    }
                    break;
                }
                
            case 'm':
                {
                    // Encontra minimo em uma dimensao
                    unsigned int dim;
                    printf("Digite a dimensao (0 a %u):\n", k - 1);
                    if (scanf("%u", &dim) != 1) {
                        matarProgramaErroLeitura();
                    }
                    
                    if (dim >= k) {
                        printf("Dimensao invalida.\n");
                        break;
                    }
                    
                    struct nodo *min = encontrarMinimo(arvore, dim);
                    if (min != NULL) {
                        printf("Minimo na dimensao %u: %.2f\n", dim, min->ponto[dim]);
                        printf("Ponto completo: ");
                        for (unsigned int i = 0; i < k; i++) {
                            printf("%.2f%s", min->ponto[i], (i < k - 1) ? ", " : "");
                        }
                        printf(" (classe %d)\n", min->classe);
                    } else {
                        printf("Arvore vazia.\n");
                    }
                    break;
                }

            case '?':
                // Mostra menu de ajuda
                exibirMenu();
                break;

            default:
                printf("Operacao invalida.\n");
                break;
        }
        
        scanf(" %c", &op);
    }

    destruirArvore(arvore);
    return 0;
}

