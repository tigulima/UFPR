#include "kdtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void matarProgramaFaltaMemoria() {
    fprintf(stderr, "Falha ao alocar memoria.\n");
    exit(1);
}

/**
 * @brief (Privada) Cria um novo nodo, alocando sua própria memória para o ponto.
 */
static struct kd_nodo* criarNodo(float *ponto, int classe, int k) {
    
    // 1. Aloca a struct do nodo
    struct kd_nodo* novo_nodo = (struct kd_nodo*)malloc(sizeof(struct kd_nodo));
    if (novo_nodo == NULL) {
        matarProgramaFaltaMemoria();
    }

    // 2. Aloca memória *DENTRO* do nodo para sua cópia do ponto
    novo_nodo->ponto = (float*)malloc(k * sizeof(float));
    if (novo_nodo->ponto == NULL) {
        free(novo_nodo); // Limpa o que já alocou
        matarProgramaFaltaMemoria();
    }

    // 3. Copia os dados do buffer temporário (ponto) para o nodo
    memcpy(novo_nodo->ponto, ponto, k * sizeof(float));
    
    novo_nodo->classe = classe;
    novo_nodo->esq = NULL;
    novo_nodo->dir = NULL;

    return novo_nodo;
}

/**
 * @brief (Privada) Insere recursivamente um novo ponto.
 * Retorna a raiz da sub-árvore modificada.
 */
static struct kd_nodo* inserir(struct kd_nodo *nodo_atual, float *ponto, int classe, int k, int nivel) {
    
    if (nodo_atual == NULL) {
        return criarNodo(ponto, classe, k);
    }
    
    // Calcula qual dimensão comparar (0, 1, ..., k-1, 0, 1, ...)
    int dim_atual = nivel % k;

    // Compara na dimensão correta
    if (ponto[dim_atual] < nodo_atual->ponto[dim_atual]) {
        // Vai para a esquerda e atualiza o ponteiro esquerdo
        nodo_atual->esq = inserir(nodo_atual->esq, ponto, classe, k, nivel + 1);
    } else {
        // Vai para a direita e atualiza o ponteiro direito
        // (Nota: k-d trees podem ter duplicatas. Esta implementação
        // as joga para a direita, o que é um comportamento aceitável.)
        nodo_atual->dir = inserir(nodo_atual->dir, ponto, classe, k, nivel + 1);
    }

    return nodo_atual;
}


/**
 * @brief Cria e carrega a k-d tree lendo N e K da entrada padrão.
 * Retorna a árvore criada.
 */
struct kdtree* criarKdtree() {
    int n, k;
    
    printf("Insira N e K.\n");
    if (scanf("%d %d", &n, &k) != 2) {
        fprintf(stderr, "Erro ao ler N e K.\n");
        exit(1); 
    }

    struct kdtree *arvore = (struct kdtree *)malloc(sizeof(struct kdtree));
    if(arvore == NULL) {
        matarProgramaFaltaMemoria();
    }

    arvore->raiz = NULL;
    arvore->k = k;

    float *ponto_buffer = (float *)malloc(k * sizeof(float));
    if(ponto_buffer == NULL) {
        matarProgramaFaltaMemoria();
    }

    printf("Insira os pontos.\n");
    for(int i = 0; i < n; i++) {

        for(int j = 0; j < k; j++) {
            if (scanf("%f", &ponto_buffer[j]) != 1) {
                 fprintf(stderr, "Erro ao ler ponto.\n");
                 exit(1);
            }
        }

        int classe;
        if (scanf("%d", &classe) != 1) {
             fprintf(stderr, "Erro ao ler classe.\n");
             exit(1);
        }

        arvore->raiz = inserir(arvore->raiz, ponto_buffer, classe, k, 0);
    }

    // *** CORREÇÃO 2: Liberar o buffer temporário *depois* do loop ***
    free(ponto_buffer);

    return arvore;
}

/**
 * @brief Calcula a distância Euclidiana entre dois pontos de dimensão k.
 * Retorna a distância calculada.
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
 * @brief Verifica se dois pontos são exatamente iguais em todas as dimensões.
 * Retorna 1 se iguais, 0 caso contrário.
 */
static int pontosIguais(float *p1, float *p2, int k) {
    for (int i = 0; i < k; i++) {
        // Comparação direta de floats é perigosa em cálculos complexos, 
        // mas para "busca exata" de valores inseridos, é o padrão.
        if (p1[i] != p2[i]) {
            return 0;
        }
    }
    return 1;
}

static struct kd_nodo* buscarRecursivo(struct kd_nodo *nodo, float *ponto, int k, int nivel) {
    if (nodo == NULL) {
        return NULL;
    }

    if (pontosIguais(nodo->ponto, ponto, k)) {
        return nodo;
    }

    int dim = nivel % k;

    if (ponto[dim] < nodo->ponto[dim]) {
        return buscarRecursivo(nodo->esq, ponto, k, nivel + 1);
    } else {
        return buscarRecursivo(nodo->dir, ponto, k, nivel + 1);
    }
}

/**
 * @brief Busca um ponto exato na k-d tree.
 * Retorna o nodo encontrado ou NULL se não existir.
 */
struct kd_nodo* buscar(struct kdtree *arvore, float *ponto) {
    if (arvore == NULL || arvore->raiz == NULL) {
        return NULL;
    }
    return buscarRecursivo(arvore->raiz, ponto, arvore->k, 0);
}










// --- Estruturas para zVizinhos (Privadas) ---

// Struct auxiliar para armazenar um candidato e sua distância
struct candidato {
    struct kd_nodo *nodo;
    float dist;
};

// Struct para gerenciar a lista dos 'z' melhores
struct lista_vizinhos {
    struct candidato *candidatos; // Vetor de candidatos
    int capacidade;               // Z (quantos queremos)
    int tamanho;                  // Quantos achamos até agora
    float *ponto_alvo;            // O ponto que estamos buscando (referência)
};

/**
 * @brief Tenta adicionar um nodo à lista de melhores vizinhos.
 * Mantém a lista ordenada por distância (menor para maior).
 */
static void adicionarCandidato(struct lista_vizinhos *lista, struct kd_nodo *nodo, int k) {
    float dist = calcularDistancia(nodo->ponto, lista->ponto_alvo, k);
    
    // 1. Se a lista não está cheia, adicionamos direto
    if (lista->tamanho < lista->capacidade) {
        lista->candidatos[lista->tamanho].nodo = nodo;
        lista->candidatos[lista->tamanho].dist = dist;
        lista->tamanho++;
    } 
    // 2. Se está cheia, verificamos se esse novo é melhor que o PIOR da lista
    else {
        // O vetor está ordenado, então o último é o pior (maior distância)
        int ultimo = lista->capacidade - 1;
        if (dist >= lista->candidatos[ultimo].dist) {
            return; // O novo ponto é pior que todos que já temos. Ignora.
        }
        // Substitui o pior pelo novo
        lista->candidatos[ultimo].nodo = nodo;
        lista->candidatos[ultimo].dist = dist;
    }

    // 3. Ordena a lista (Insertion Sort simples, pois Z costuma ser pequeno e lista está quase ordenada)
    // Move o novo elemento "para cima" até achar seu lugar.
    for (int i = lista->tamanho - 1; i > 0; i--) {
        if (lista->candidatos[i].dist < lista->candidatos[i-1].dist) {
            // Swap
            struct candidato temp = lista->candidatos[i];
            lista->candidatos[i] = lista->candidatos[i-1];
            lista->candidatos[i-1] = temp;
        } else {
            break; 
        }
    }
}

/**
 * @brief Função recursiva principal do Nearest Neighbor
 */
static void buscarVizinhosRecursivo(struct kd_nodo *nodo, struct lista_vizinhos *lista, int k, int nivel) {
    if (nodo == NULL) return;

    int dim = nivel % k;
    float diff = lista->ponto_alvo[dim] - nodo->ponto[dim];
    
    struct kd_nodo *lado_perto = NULL;
    struct kd_nodo *lado_longe = NULL;

    // Decide qual lado visitar primeiro (como na inserção)
    if (diff < 0) {
        lado_perto = nodo->esq;
        lado_longe = nodo->dir;
    } else {
        lado_perto = nodo->dir;
        lado_longe = nodo->esq;
    }

    // 1. Visita o lado promissor primeiro
    buscarVizinhosRecursivo(lado_perto, lista, k, nivel + 1);

    // 2. Processa o nodo atual (tenta adicionar à lista)
    adicionarCandidato(lista, nodo, k);

    // 3. Verifica se precisa visitar o lado "longe" (Poda)
    // Se a lista ainda não está cheia, TEM que visitar.
    // Se a distância do plano divisor (abs(diff)) for MENOR que a pior distância da lista,
    // pode haver algo mais perto do outro lado.
    float pior_dist = lista->candidatos[lista->tamanho - 1].dist;
    
    // fabs é valor absoluto para float (include math.h)
    if (lista->tamanho < lista->capacidade || fabs(diff) < pior_dist) {
        buscarVizinhosRecursivo(lado_longe, lista, k, nivel + 1);
    }
}

// --- Implementação da API Pública Z-Vizinhos ---

struct kd_nodo** zVizinhos(struct kdtree *arvore, float *ponto, int z, int *num_encontrados) {
    if (arvore == NULL || z <= 0) return NULL;

    // Configura a lista auxiliar
    struct lista_vizinhos lista;
    lista.capacidade = z;
    lista.tamanho = 0;
    lista.ponto_alvo = ponto;
    
    // Aloca vetor temporário para os structs candidatos
    lista.candidatos = (struct candidato*)malloc(z * sizeof(struct candidato));
    if (!lista.candidatos) matarProgramaFaltaMemoria();

    // Dispara a busca
    buscarVizinhosRecursivo(arvore->raiz, &lista, arvore->k, 0);

    // Prepara o retorno (apenas vetor de ponteiros para nodos)
    struct kd_nodo **resultado = (struct kd_nodo**)malloc(lista.tamanho * sizeof(struct kd_nodo*));
    if (!resultado) matarProgramaFaltaMemoria();

    for (int i = 0; i < lista.tamanho; i++) {
        resultado[i] = lista.candidatos[i].nodo;
        
        // O PDF pede para imprimir a distância na main. 
        // Como a função retorna só os nodos, o main terá que recalcular 
        // ou mudamos o retorno. Pelo protótipo padrão, retorna nodos.
        // (Dica: O main pode recalcular a distância facilmente para imprimir).
    }

    free(lista.candidatos); // Libera a lista auxiliar interna
    *num_encontrados = lista.tamanho;
    return resultado;
}
















// --- Estruturas Auxiliares para Fila (Impressão em Largura) ---

// Nodo da fila (armazena um ponteiro para um nodo da árvore)
struct fila_nodo {
    struct kd_nodo *nodo_arvore;
    struct fila_nodo *prox;
};

// A fila
struct fila {
    struct fila_nodo *inicio;
    struct fila_nodo *fim;
    unsigned int tamanho;
};

/**
 * @brief (Privado) Cria uma fila vazia.
 */
static struct fila* criarFila() {
    struct fila* fila = (struct fila*)malloc(sizeof(struct fila));
    if (!fila) {
        matarProgramaFaltaMemoria();
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

/**
 * @brief (Privado) Adiciona um nodo da árvore ao fim da fila.
 */
static void enfileirar(struct fila* fila, struct kd_nodo* nodo) {
    struct fila_nodo* novo_fila_nodo = (struct fila_nodo*)malloc(sizeof(struct fila_nodo));
    if (!novo_fila_nodo) {
        matarProgramaFaltaMemoria();
    }
    novo_fila_nodo->nodo_arvore = nodo;
    novo_fila_nodo->prox = NULL;

    if (fila->inicio != NULL) {
        fila->fim->prox = novo_fila_nodo;
        fila->fim = novo_fila_nodo;
    } else {
        fila->inicio = novo_fila_nodo;
        fila->fim = novo_fila_nodo;
    }
    fila->tamanho++;
}

/**
 * @brief (Privado) Remove e retorna um nodo da árvore do início da fila.
 */
static struct kd_nodo* desenfileirar(struct fila* fila) {
    if (fila->inicio == NULL) {
        return NULL; // Fila vazia
    }

    struct fila_nodo* inicio_fila_nodo = fila->inicio;
    fila->inicio = fila->inicio->prox;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    fila->tamanho--;
    struct kd_nodo* nodo_retorno = inicio_fila_nodo->nodo_arvore;
    free(inicio_fila_nodo);

    return nodo_retorno;
}

// --- API Pública de Impressão ---

/**
 * @brief Imprime a árvore em largura (nível por nível).
 */
void imprimirEmLargura(struct kdtree *arvore) {
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("Árvore vazia.\n");
        return;
    }

    struct fila* fila = criarFila();
    enfileirar(fila, arvore->raiz);
    
    unsigned int nivel_atual = 0;

    while (fila->tamanho > 0) {
        unsigned int tamanho_nivel = fila->tamanho;
        printf("Nivel %u: ", nivel_atual);

        for (unsigned int i = 0; i < tamanho_nivel; i++) {
            struct kd_nodo* nodo = desenfileirar(fila);
            
            // Imprime o ponto
            printf("[(");
            for (int d = 0; d < arvore->k; d++) {
                printf("%.2f%s", nodo->ponto[d], (d == arvore->k - 1) ? "" : ", ");
            }
            printf(") C:%d]  ", nodo->classe);

            // Adiciona os filhos na fila para o próximo nível
            if (nodo->esq != NULL) {
                enfileirar(fila, nodo->esq);
            }
            if (nodo->dir != NULL) {
                enfileirar(fila, nodo->dir);
            }
        }
        printf("\n"); // Quebra de linha ao final de cada nível
        nivel_atual++;
    }

    free(fila); // Libera a estrutura da fila
}












// --- Funções de Limpeza (Gerenciamento de Memória) ---

/**
 * @brief (Privado) Libera recursivamente os nodos da árvore.
 * (Pós-ordem: libera filhos, depois o ponto, depois o nodo).
 */
static void liberarNodosRecursivo(struct kd_nodo *nodo) {
    if (nodo == NULL) {
        return;
    }

    // 1. Libera sub-árvores
    liberarNodosRecursivo(nodo->esq);
    liberarNodosRecursivo(nodo->dir);

    // 2. Libera os dados do nodo atual
    free(nodo->ponto); // Libera o vetor de coordenadas
    free(nodo);       // Libera a struct do nodo
}

/**
 * @brief Libera toda a memória associada à árvore e seus nodos.
 */
void liberarKdtree(struct kdtree *arvore) {
    if (arvore == NULL) {
        return;
    }

    // Libera todos os nodos recursivamente
    liberarNodosRecursivo(arvore->raiz);

    // Libera a struct 'wrapper' da árvore
    free(arvore);
}