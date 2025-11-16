#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "kdtree.h"

/**
 * @brief Função de erro (copiada de kdtree.c para consistência).
 * Imprime erro em stderr e finaliza o programa com código 1.
 */
// void matarProgramaFaltaMemoria() {
//     fprintf(stderr, "Falha ao alocar memoria.\n");
//     exit(1);
// }

/**
 * @brief Calcula a distância Euclidiana entre dois pontos de dimensão k.
 * (Necessário para a impressão da saída de 'zVizinhos').
 */
static float calcularDistancia(float *p1, float *p2, int k) {
    float soma = 0.0;
    for (int i = 0; i < k; i++) {
        float diff = p1[i] - p2[i];
        soma += diff * diff;
    }
    return sqrt(soma);
}

/**
 * @brief Lê um ponto (vetor de k floats) da stdin para um buffer.
 * Retorna 1 em sucesso, 0 em falha.
 */
static int lerPonto(float *buffer, int k) {
    for (int i = 0; i < k; i++) {
        if (scanf("%f", &buffer[i]) != 1) {
            fprintf(stderr, "Erro ao ler vetor de ponto.\n");
            return 0; // Falha
        }
    }
    return 1; // Sucesso
}


int main() {
    
    // --- 1. Fase de Criação ---
    // A própria criarKdtree() lida com os prompts "Insira N e K."
    // e "Insira os pontos." [cite: 54, 56]
    struct kdtree *arvore = criarKdtree();
    
    // Imprime a confirmação após a leitura dos N pontos [cite: 60]
    printf("Árvore Construída.\n");

    // Guarda o 'k' para uso no loop principal
    int k = arvore->k;
    
    // Buffer reutilizável para ler pontos da stdin
    float *ponto_buffer = (float *)malloc(k * sizeof(float));
    if (ponto_buffer == NULL) {
        matarProgramaFaltaMemoria();
    }

    char comando[16];

    // --- 2. Fase de Interação ---
    // Loop principal de comandos [cite: 44]
    while (scanf("%15s", comando) == 1) {

        // Comando: f (finalizar) [cite: 48]
        if (strcmp(comando, "f") == 0) {
            break; // Sai do loop
        }

        // Comando: b (buscar) [cite: 45]
        else if (strcmp(comando, "b") == 0) {
            if (lerPonto(ponto_buffer, k)) {
                struct kd_nodo* resultado = buscar(arvore, ponto_buffer);
                if (resultado != NULL) {
                    printf("Encontrado. Classe %d.\n", resultado->classe); // [cite: 62]
                } else {
                    printf("Não encontrado.\n"); // [cite: 64]
                }
            }
        }

        // Comando: l (imprimir em largura) [cite: 46]
        else if (strcmp(comando, "l") == 0) {
            imprimirEmLargura(arvore);
        }

        // Comando: z (z-vizinhos) [cite: 47]
        else if (strcmp(comando, "z") == 0) {
            int num_vizinhos = 0;
            if (scanf("%d", &num_vizinhos) != 1) {
                fprintf(stderr, "Erro ao ler numero de vizinhos.\n");
                continue;
            }

            if (lerPonto(ponto_buffer, k)) {
                int num_encontrados = 0;
                
                // Usando a API ajustada
                struct kd_nodo **vizinhos = zVizinhos(arvore, ponto_buffer, num_vizinhos, &num_encontrados);

                printf("Vizinhos mais próximos:\n"); // [cite: 66]
                
                // Itera nos resultados e imprime no formato exato do PDF [cite: 67-69]
                for (int i = 0; i < num_encontrados; i++) {
                    struct kd_nodo *v = vizinhos[i];
                    
                    // Imprime o ponto (ex: 4.9, 2.4, 3.3, 1.0)
                    for (int d = 0; d < k; d++) {
                        // O PDF usa 1 casa decimal para o ponto
                        printf("%.1f%s", v->ponto[d], (d == k - 1) ? "" : ", ");
                    }
                    
                    // Calcula a distância para impressão
                    float dist = calcularDistancia(v->ponto, ponto_buffer, k);
                    
                    // Imprime classe e distância (ex: (classe 1), dist=0.1414)
                    // O PDF usa 4 casas decimais para a distância
                    printf(" (classe %d), dist=%.4f\n", v->classe, dist);
                }
                
                // IMPORTANTE: zVizinhos alocou o vetor 'vizinhos', o main deve liberá-lo
                free(vizinhos);
            }
        }
        
        // Comando desconhecido
        else {
            fprintf(stderr, "Comando desconhecido: %s\n", comando);
        }
    }

    // --- 3. Fase de Limpeza ---
    // Libera toda a memória alocada antes de sair
    free(ponto_buffer);
    liberarKdtree(arvore);

    return 0;
}