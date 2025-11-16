/*
 * ============================================================================
 * IMPLEMENTAÇÃO DE KD-TREE (K-Dimensional Tree)
 * ============================================================================
 * 
 * O QUE É UMA KD-TREE?
 * -------------------
 * Uma KD-Tree é uma estrutura de dados de árvore binária que organiza pontos
 * em um espaço k-dimensional. Ela é usada para:
 * - Busca espacial eficiente
 * - Busca de vizinhos mais próximos (k-NN)
 * - Consultas de alcance
 * 
 * CONCEITO PRINCIPAL:
 * ------------------
 * Em cada nível da árvore, os pontos são divididos por um eixo diferente:
 * - Nível 0: divide pelo eixo X (dimensão 0)
 * - Nível 1: divide pelo eixo Y (dimensão 1)
 * - Nível 2: divide pelo eixo Z (dimensão 2) [se k >= 3]
 * - E assim ciclicamente: nível % k
 * 
 * EXEMPLO (2D):
 * ------------
 *        (5,4)          <- raiz, divide por X (nível 0)
 *       /     \
 *    (2,3)   (9,6)      <- divide por Y (nível 1)
 *    /   \     /   \
 * (1,2) (3,5)(7,2)(10,8) <- divide por X (nível 2)
 * 
 * Se um ponto tem X < 5, vai para esquerda; se X >= 5, vai para direita.
 * No próximo nível, compara Y; depois X novamente, e assim por diante.
 */

#include "kdtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * EPSILON: Tolerância para comparação de números de ponto flutuante
 * -----------------------------------------------------------------
 * Devido a erros de precisão de ponto flutuante, nunca devemos comparar
 * floats diretamente com ==. Por exemplo:
 * 
 * 0.1 + 0.2 == 0.3 pode ser FALSE devido a representação binária!
 * 
 * Solução: Considerar dois números iguais se |a - b| < EPSILON
 */
#define EPSILON 1e-6

/*
 * matarProgramaFaltaMemoria()
 * ---------------------------
 * Função auxiliar chamada quando malloc() falha.
 * 
 * POR QUE ISSO ACONTECE?
 * - Sistema sem memória disponível
 * - Limite de memória do processo atingido
 * 
 * O QUE FAZER?
 * - Reportar erro ao usuário via stderr (erro padrão)
 * - Encerrar programa com código de erro (1)
 */
void matarProgramaFaltaMemoria() {
    fprintf(stderr, "Falha ao alocar memoria.");
    exit(1);  // Encerra o programa com código de erro
}

/* ==========================================================================
 *                          SEÇÃO: CRIAÇÃO
 * ==========================================================================
 */

/*
 * criarArvore()
 * -------------
 * Aloca e inicializa uma nova KD-Tree vazia.
 * 
 * PARÂMETROS:
 * - k: número de dimensões (ex: 2 para 2D, 3 para 3D, etc.)
 * 
 * RETORNO:
 * - Ponteiro para a estrutura kdtree criada
 * 
 * COMPLEXIDADE: O(1) - tempo constante
 * 
 * ESTRUTURA CRIADA:
 * struct kdtree {
 *     struct nodo *raiz;  <- inicialmente NULL (árvore vazia)
 *     unsigned int k;     <- número de dimensões
 * };
 */
struct kdtree* criarArvore(unsigned int k) {
    // Aloca memória para a estrutura kdtree
    struct kdtree *arvore = (struct kdtree *)malloc(sizeof(struct kdtree));
    
    // SEMPRE verificar se malloc teve sucesso!
    if (arvore == NULL) {
        matarProgramaFaltaMemoria();
    }

    // Inicializa árvore vazia
    arvore->raiz = NULL;  // Nenhum nodo ainda
    arvore->k = k;        // Armazena o número de dimensões
    
    return arvore;
}

/*
 * criarNodo()
 * -----------
 * Cria um novo nodo da KD-Tree com o ponto e classe especificados.
 * 
 * PARÂMETROS:
 * - ponto: array de floats com k dimensões (ex: [x, y, z])
 * - classe: rótulo/categoria do ponto (para classificação)
 * - k: número de dimensões
 * 
 * RETORNO:
 * - Ponteiro para o novo nodo criado
 * 
 * COMPLEXIDADE: O(k) - precisa copiar k coordenadas
 * 
 * IMPORTANTE:
 * - O ponto é COPIADO (não compartilha memória com o original)
 * - Isso permite que o chamador libere seu ponto sem afetar a árvore
 */
struct nodo* criarNodo(float *ponto, int classe, unsigned int k) {
    // PASSO 1: Alocar memória para a estrutura do nodo
    struct nodo *novoNodo = (struct nodo *)malloc(sizeof(struct nodo));
    if (novoNodo == NULL) {
        matarProgramaFaltaMemoria();
    }

    // PASSO 2: Alocar memória para o array de coordenadas do ponto
    // Por que separado? Porque k pode ser diferente para cada árvore
    novoNodo->ponto = (float *)malloc(k * sizeof(float));
    if (novoNodo->ponto == NULL) {
        // IMPORTANTE: Se segunda alocação falhar, liberar a primeira!
        // Isso evita memory leak
        free(novoNodo);
        matarProgramaFaltaMemoria();
    }

    // PASSO 3: Copiar as coordenadas do ponto (deep copy)
    for (unsigned int i = 0; i < k; i++) {
        novoNodo->ponto[i] = ponto[i];
    }
    
    // PASSO 4: Inicializar outros campos
    novoNodo->classe = classe;  // Armazena a classificação do ponto
    novoNodo->esq = NULL;       // Sem filho esquerdo ainda
    novoNodo->dir = NULL;       // Sem filho direito ainda

    return novoNodo;
}

/* ==========================================================================
 *                          SEÇÃO: INSERÇÃO
 * ==========================================================================
 */

/*
 * inserirRecursivo()
 * ------------------
 * Insere um ponto na KD-Tree de forma recursiva.
 * 
 * ALGORITMO:
 * 1. Se chegou em NULL (árvore vazia ou folha), cria novo nodo aqui
 * 2. Determina eixo atual: nivel % k
 * 3. Compara ponto[eixo] com raiz->ponto[eixo]
 * 4. Se menor: insere na subárvore esquerda
 *    Se maior ou igual: insere na subárvore direita
 * 5. Retorna a raiz (inalterada ou recém-criada)
 * 
 * PARÂMETROS:
 * - raiz: raiz da subárvore atual
 * - ponto: coordenadas do ponto a inserir
 * - classe: classificação do ponto
 * - k: número de dimensões
 * - nivel: profundidade atual (0 = raiz, 1 = filhos da raiz, etc.)
 * 
 * RETORNO:
 * - Ponteiro para a raiz da subárvore (pode ser modificada se era NULL)
 * 
 * COMPLEXIDADE:
 * - Melhor caso: O(log n) - árvore balanceada
 * - Pior caso: O(n) - árvore degenerada (como lista encadeada)
 * 
 * EXEMPLO (k=2):
 * Inserindo (7,2) em uma árvore com raiz (5,4):
 * - Nível 0: compara X: 7 >= 5 → vai para direita
 * - Nível 1: compara Y com próximo nodo
 * - E assim por diante...
 */
static struct nodo* inserirRecursivo(struct nodo *raiz, float *ponto, int classe, 
                                     unsigned int k, unsigned int nivel) {
    // CASO BASE: Se chegou em NULL, este é o lugar para inserir
    if (raiz == NULL) {
        return criarNodo(ponto, classe, k);
    }

    // Determina qual eixo/dimensão usar neste nível
    // nivel % k garante ciclo: 0, 1, 2, ..., k-1, 0, 1, 2, ...
    // Exemplo: k=2 → eixos alternam entre X (0) e Y (1)
    unsigned int eixo = nivel % k;

    // Decide se vai para esquerda ou direita baseado no eixo atual
    if (ponto[eixo] < raiz->ponto[eixo]) {
        // Ponto é "menor" neste eixo → subárvore esquerda
        raiz->esq = inserirRecursivo(raiz->esq, ponto, classe, k, nivel + 1);
    } else {
        // Ponto é "maior ou igual" neste eixo → subárvore direita
        // Nota: >= (não <) permite pontos duplicados na mesma coordenada
        raiz->dir = inserirRecursivo(raiz->dir, ponto, classe, k, nivel + 1);
    }

    // Retorna a raiz (inalterada neste nível)
    return raiz;
}

/*
 * inserir()
 * ---------
 * Interface pública para inserir um ponto na KD-Tree.
 * 
 * Função wrapper que:
 * 1. Chama a versão recursiva começando da raiz
 * 2. Inicializa nível como 0
 * 3. Atualiza a raiz da árvore (pode mudar se estava vazia)
 * 
 * PARÂMETROS:
 * - arvore: ponteiro para a KD-Tree
 * - ponto: array com k coordenadas
 * - classe: classificação do ponto
 * 
 * RETORNO:
 * - Ponteiro para a árvore (para permitir encadeamento)
 */
struct kdtree* inserir(struct kdtree *arvore, float *ponto, int classe) {
    // Chama função recursiva e atualiza raiz
    // A raiz pode mudar se a árvore estava vazia (raiz == NULL)
    arvore->raiz = inserirRecursivo(arvore->raiz, ponto, classe, arvore->k, 0);
    return arvore;
}

/* ==========================================================================
 *                          SEÇÃO: BUSCA
 * ==========================================================================
 */

/*
 * pontosIguais()
 * --------------
 * Verifica se dois pontos são iguais em todas as dimensões.
 * 
 * IMPORTANTE: Usa EPSILON para comparação de floats!
 * 
 * POR QUE EPSILON?
 * Devido a erros de arredondamento, um cálculo pode resultar em:
 * - 1.999999999 em vez de 2.0
 * - 0.30000000004 em vez de 0.3
 * 
 * Considerar iguais se diferença < EPSILON (ex: 0.000001)
 * 
 * PARÂMETROS:
 * - p1, p2: pontos a comparar (arrays de k floats)
 * - k: número de dimensões
 * 
 * RETORNO:
 * - 1 (true) se iguais em todas as dimensões
 * - 0 (false) se diferentes em pelo menos uma dimensão
 * 
 * COMPLEXIDADE: O(k) - verifica todas as k dimensões
 */
static int pontosIguais(float *p1, float *p2, unsigned int k) {
    // Verifica cada dimensão
    for (unsigned int i = 0; i < k; i++) {
        // fabs() retorna o valor absoluto de um float
        // |p1[i] - p2[i]| > EPSILON significa que são diferentes
        if (fabs(p1[i] - p2[i]) > EPSILON) {
            return 0;  // Encontrou diferença → pontos diferentes
        }
    }
    // Todas as dimensões são iguais (dentro da tolerância)
    return 1;
}

/*
 * buscarRecursivo()
 * -----------------
 * Busca um ponto específico na KD-Tree.
 * 
 * ALGORITMO:
 * 1. Se nodo é NULL → ponto não existe
 * 2. Se nodo atual tem o ponto → encontrou!
 * 3. Determina eixo atual (nivel % k)
 * 4. Compara ponto[eixo] com nodo->ponto[eixo]
 * 5. Busca recursivamente na subárvore apropriada
 * 
 * IMPORTANTE: Esta busca é EXATA (não busca aproximada)
 * - Só encontra se o ponto exato existir na árvore
 * - Para "vizinhos mais próximos", usar zVizinhos()
 * 
 * PARÂMETROS:
 * - nodo: raiz da subárvore atual
 * - ponto: ponto a buscar
 * - k: número de dimensões
 * - nivel: profundidade atual
 * 
 * RETORNO:
 * - Ponteiro para o nodo se encontrado
 * - NULL se não encontrado
 * 
 * COMPLEXIDADE:
 * - Melhor caso: O(log n) - árvore balanceada
 * - Pior caso: O(n) - árvore degenerada
 */
static struct nodo* buscarRecursivo(struct nodo *nodo, float *ponto, 
                                    unsigned int k, unsigned int nivel) {
    // CASO BASE 1: Chegou em NULL → ponto não existe
    if (nodo == NULL) {
        return NULL;
    }
    
    // CASO BASE 2: Encontrou o ponto!
    if (pontosIguais(nodo->ponto, ponto, k)) {
        return nodo;
    }

    // Determina eixo atual para navegação
    unsigned int eixo = nivel % k;

    // Decide qual subárvore explorar (mesma lógica da inserção)
    if (ponto[eixo] < nodo->ponto[eixo]) {
        // Ponto deve estar na subárvore esquerda
        return buscarRecursivo(nodo->esq, ponto, k, nivel + 1);
    } else {
        // Ponto deve estar na subárvore direita
        return buscarRecursivo(nodo->dir, ponto, k, nivel + 1);
    }
}

/*
 * buscar()
 * --------
 * Interface pública para buscar um ponto exato na KD-Tree.
 * 
 * Função wrapper que chama a versão recursiva.
 * 
 * PARÂMETROS:
 * - arvore: KD-Tree onde buscar
 * - ponto: ponto a buscar
 * 
 * RETORNO:
 * - Ponteiro para o nodo se encontrado
 * - NULL se não encontrado
 */
struct nodo* buscar(struct kdtree *arvore, float *ponto) {
    return buscarRecursivo(arvore->raiz, ponto, arvore->k, 0);
}

/* ==========================================================================
 *                    SEÇÃO: K-VIZINHOS MAIS PRÓXIMOS
 * ==========================================================================
 */

/*
 * calcularDistancia()
 * -------------------
 * Calcula a distância Euclidiana entre dois pontos em k dimensões.
 * 
 * FÓRMULA:
 * dist(p1, p2) = sqrt((p1[0]-p2[0])² + (p1[1]-p2[1])² + ... + (p1[k-1]-p2[k-1])²)
 * 
 * EXEMPLO (2D):
 * p1 = (3, 4), p2 = (0, 0)
 * dist = sqrt((3-0)² + (4-0)²) = sqrt(9 + 16) = sqrt(25) = 5
 * 
 * PARÂMETROS:
 * - p1, p2: pontos a calcular distância
 * - k: número de dimensões
 * 
 * RETORNO:
 * - Distância Euclidiana (float)
 * 
 * COMPLEXIDADE: O(k) - soma sobre k dimensões + sqrt()
 * 
 * NOTA: Para comparações, poderíamos usar distância² (sem sqrt)
 *       para economizar processamento, mas aqui retornamos a distância
 *       real para facilitar visualização.
 */
static float calcularDistancia(float *p1, float *p2, unsigned int k) {
    float soma = 0.0;
    
    // Soma dos quadrados das diferenças em cada dimensão
    for (int i = 0; i < k; i++) {
        float diff = p1[i] - p2[i];
        soma += diff * diff;  // Eleva ao quadrado
    }
    
    // Raiz quadrada para obter distância Euclidiana
    return sqrt(soma);
}

/*
 * insereCandidato()
 * -----------------
 * Insere um candidato (nodo + distância) em uma posição específica da lista.
 * 
 * Esta é uma operação simples de atribuição.
 * 
 * PARÂMETROS:
 * - lista: lista de vizinhos
 * - nodo: nodo a inserir
 * - dist: distância até o ponto alvo
 * - pos: posição onde inserir
 * 
 * COMPLEXIDADE: O(1) - acesso direto por índice
 */
static void insereCandidato(struct lista_vizinhos *lista, struct nodo *nodo, 
                           float dist, int pos) {
    lista->candidatos[pos].nodo = nodo;
    lista->candidatos[pos].dist = dist;
}

/*
 * posicaoCandidato()
 * ------------------
 * Encontra a posição correta para inserir um candidato mantendo a lista ordenada.
 * 
 * A lista é mantida ORDENADA por distância (menor → maior).
 * Esta função faz uma busca linear para encontrar onde inserir.
 * 
 * EXEMPLO:
 * Lista atual: [1.5, 3.2, 4.8] (distâncias)
 * Inserindo: 2.7
 * Resultado: posição 1 (entre 1.5 e 3.2)
 * 
 * PARÂMETROS:
 * - lista: lista de vizinhos
 * - dist: distância do novo candidato
 * 
 * RETORNO:
 * - Índice onde o candidato deve ser inserido
 * 
 * COMPLEXIDADE: O(z) onde z é o número de vizinhos
 */
static int posicaoCandidato(struct lista_vizinhos *lista, float dist) {
    int i = 0;
    // Avança enquanto as distâncias forem menores
    while (i < lista->tam && lista->candidatos[i].dist < dist) {
        i++;
    }
    return i;  // Posição de inserção
}

/*
 * abreEspacoNaLista()
 * -------------------
 * Desloca elementos para a direita para abrir espaço para nova inserção.
 * 
 * EXEMPLO:
 * Antes:  [A, B, C, D, _] (tam=4, z=5, pos=1)
 * Depois: [A, _, B, C, D] (pronto para inserir em pos 1)
 * 
 * IMPORTANTE: Move de trás para frente para não sobrescrever dados!
 * 
 * PARÂMETROS:
 * - lista: lista de vizinhos
 * - pos: posição onde será inserido o novo elemento
 * 
 * COMPLEXIDADE: O(z) - pode precisar mover z elementos
 */
static void abreEspacoNaLista(struct lista_vizinhos *lista, int pos) {
    // Move elementos da direita para a esquerda
    // Começa do final para não sobrescrever
    for (int j = lista->z - 1; j > pos; j--) {
        lista->candidatos[j] = lista->candidatos[j - 1];
    }
}

/*
 * insereListaVizinhos()
 * ---------------------
 * Insere um novo vizinho na lista mantendo ordem por distância.
 * 
 * FUNCIONAMENTO:
 * 1. Encontra posição correta (mantém ordenação)
 * 2. Abre espaço na lista
 * 3. Insere o candidato
 * 4. Atualiza tamanho (se ainda não está cheio)
 * 
 * A lista tem capacidade Z mas pode ter menos elementos no início.
 * 
 * PARÂMETROS:
 * - lista: lista de vizinhos
 * - nodo: nodo a adicionar
 * - dist: distância até o ponto alvo
 * - k: número de dimensões (não usado, pode ser removido)
 * 
 * RETORNO:
 * - Posição onde foi inserido
 * 
 * COMPLEXIDADE: O(z) - buscar posição + abrir espaço
 */
static int insereListaVizinhos(struct lista_vizinhos *lista, struct nodo *nodo, 
                               float dist, unsigned int k) {
    // PASSO 1: Encontrar onde inserir
    int pos = posicaoCandidato(lista, dist);
    
    // PASSO 2: Abrir espaço na lista
    abreEspacoNaLista(lista, pos);
    
    // PASSO 3: Inserir o candidato
    insereCandidato(lista, nodo, dist, pos);

    // PASSO 4: Atualizar tamanho se ainda não chegou no limite
    if (lista->tam < lista->z) {
        lista->tam++;
    }
    // Se já está cheio (tam == z), o último elemento foi "empurrado para fora"

    return pos;
}

/*
 * zVizinhosRecursivo()
 * --------------------
 * Percorre a KD-Tree para encontrar os Z vizinhos mais próximos de um ponto.
 * 
 * ALGORITMO (complexo mas elegante):
 * 
 * 1. VERIFICA NODO ATUAL:
 *    - Calcula distância até o ponto alvo
 *    - Se lista não está cheia OU distância < pior candidato atual:
 *      → Adiciona este nodo à lista
 * 
 * 2. DECIDE QUAIS SUBÁRVORES EXPLORAR:
 *    - Sempre explora o lado "mais provável" primeiro
 *    - Pode explorar o outro lado também se:
 *      a) Lista ainda não está cheia, OU
 *      b) Distância até o hiperplano de divisão < distância do pior candidato
 * 
 * POR QUE EXPLORAR O OUTRO LADO?
 * Imagine uma linha vertical (hiperplano) dividindo o espaço em X=5:
 * - Ponto alvo está em X=5.1 (lado direito)
 * - Mas pode haver pontos em X=4.9 (lado esquerdo) mais próximos!
 * - Se a distância do ponto alvo até a linha (|5.1-5| = 0.1) é menor que
 *   a distância do pior candidato atual, vale a pena verificar o outro lado.
 * 
 * EXEMPLO VISUAL (2D, k=2):
 * 
 *        |          Alvo *
 *    A   |   B       
 *        |     C
 *   -----+--------- (linha X=5)
 *    D   |   E
 *        |
 * 
 * Se alvo está em (5.1, 3) e procuramos 2 vizinhos:
 * - Vai primeiro para direita (B, C, E)
 * - Se encontrar B(6,3) e C(7,2)
 * - Verifica: |5.1-5| = 0.1 < dist(alvo, C)?
 * - Se sim, também verifica esquerda (pode achar A ou D mais próximos!)
 * 
 * PARÂMETROS:
 * - nodo: nodo atual sendo visitado
 * - lista: lista de melhores candidatos (atualizada durante busca)
 * - k: número de dimensões
 * - nivel: profundidade atual (determina eixo de divisão)
 * 
 * COMPLEXIDADE:
 * - Melhor caso: O(log n) - árvore balanceada, não precisa explorar muito
 * - Pior caso: O(n) - precisa visitar todos os nodos
 * - Típico: O(z log n) onde z é número de vizinhos procurados
 */
static void zVizinhosRecursivo(struct nodo *nodo, struct lista_vizinhos *lista, 
                               unsigned int k, unsigned int nivel) {
    // CASO BASE: Chegou em NULL (fim de um ramo)
    if (nodo == NULL) {
        return;
    }

    // PASSO 1: AVALIAR NODO ATUAL
    // Calcula distância do nodo atual até o ponto alvo
    float dist = calcularDistancia(lista->ponto_alvo, nodo->ponto, k);
    
    // Decide se este nodo deve entrar na lista de candidatos
    // Condições para inserir:
    // - Lista ainda não está cheia (tam < z), OU
    // - Este nodo está mais próximo que o pior candidato atual
    if (lista->tam < lista->z || dist < lista->candidatos[lista->tam - 1].dist) {
        insereListaVizinhos(lista, nodo, dist, k);
    }

    // PASSO 2: DECIDIR QUAIS SUBÁRVORES EXPLORAR
    // Determina eixo de divisão neste nível
    unsigned int eixo = nivel % k;

    // Determina qual lado do hiperplano o ponto alvo está
    if (lista->ponto_alvo[eixo] < nodo->ponto[eixo]) {
        // CASO A: Ponto alvo está do lado ESQUERDO
        
        // Sempre explora o lado "correto" primeiro (onde o ponto está)
        zVizinhosRecursivo(nodo->esq, lista, k, nivel + 1);
        
        // Decide se vale a pena explorar o outro lado (direita)
        // Calcula distância até o hiperplano: |ponto_alvo[eixo] - nodo->ponto[eixo]|
        // Se essa distância < distância do pior candidato atual,
        // pode haver pontos melhores do outro lado!
        if (lista->tam < lista->z || 
            fabs(lista->ponto_alvo[eixo] - nodo->ponto[eixo]) < lista->candidatos[lista->tam - 1].dist) {
            zVizinhosRecursivo(nodo->dir, lista, k, nivel + 1);
        }
    } else {
        // CASO B: Ponto alvo está do lado DIREITO
        
        // Sempre explora o lado "correto" primeiro
        zVizinhosRecursivo(nodo->dir, lista, k, nivel + 1);
        
        // Decide se vale a pena explorar o outro lado (esquerda)
        if (lista->tam < lista->z || 
            fabs(lista->ponto_alvo[eixo] - nodo->ponto[eixo]) < lista->candidatos[lista->tam - 1].dist) {
            zVizinhosRecursivo(nodo->esq, lista, k, nivel + 1);
        }
    }
}

/*
 * zVizinhos()
 * -----------
 * Interface pública para encontrar Z vizinhos mais próximos de um ponto.
 * 
 * APLICAÇÕES:
 * - Algoritmo k-NN (k-Nearest Neighbors) para classificação
 * - Sistemas de recomendação
 * - Busca por similaridade
 * - Interpolação espacial
 * 
 * FUNCIONAMENTO:
 * 1. Aloca estrutura lista_vizinhos
 * 2. Aloca array para Z candidatos
 * 3. Inicializa lista vazia
 * 4. Chama busca recursiva
 * 5. Retorna lista ordenada por distância
 * 
 * PARÂMETROS:
 * - arvore: KD-Tree onde buscar
 * - ponto: ponto de referência
 * - z: número de vizinhos desejados
 * 
 * RETORNO:
 * - Ponteiro para lista_vizinhos contendo até Z vizinhos ordenados
 * 
 * IMPORTANTE: O chamador deve liberar:
 * - lista->candidatos (free)
 * - lista (free)
 * 
 * COMPLEXIDADE: O(z log n) típico, O(n) pior caso
 */
struct lista_vizinhos* zVizinhos(struct kdtree *arvore, float *ponto, unsigned int z) {
    struct lista_vizinhos *lista;

    // PASSO 1: Alocar estrutura da lista
    lista = (struct lista_vizinhos *)malloc(sizeof(struct lista_vizinhos));
    if (lista == NULL) {
        matarProgramaFaltaMemoria();
    }

    // PASSO 2: Alocar array de candidatos
    lista->candidatos = (struct candidato *)malloc(z * sizeof(struct candidato));
    if (lista->candidatos == NULL) {
        // IMPORTANTE: Liberar lista antes de sair!
        free(lista);
        matarProgramaFaltaMemoria();
    }

    // PASSO 3: Inicializar campos da lista
    lista->z = z;                // Capacidade máxima
    lista->tam = 0;              // Começa vazia
    lista->ponto_alvo = ponto;   // Referência (não copia, apenas aponta)

    // PASSO 4: Executar busca recursiva
    // Isso irá preencher lista->candidatos com os Z vizinhos mais próximos
    zVizinhosRecursivo(arvore->raiz, lista, arvore->k, 0);

    // PASSO 5: Retornar lista preenchida e ordenada
    return lista;
}

/* ==========================================================================
 *                          SEÇÃO: DESTRUIÇÃO
 * ==========================================================================
 */

/*
 * destruirArvoreRecursivo()
 * -------------------------
 * Libera recursivamente toda a memória alocada pela árvore.
 * 
 * ALGORITMO: Percurso em PÓS-ORDEM
 * 1. Destrói subárvore esquerda
 * 2. Destrói subárvore direita
 * 3. Libera ponto do nodo atual
 * 4. Libera nodo atual
 * 
 * POR QUE PÓS-ORDEM?
 * Precisamos processar os filhos ANTES do pai, porque:
 * - Se liberarmos o pai primeiro, perdemos os ponteiros para os filhos
 * - Isso causaria memory leak (filhos ficam órfãos na memória)
 * 
 * ANALOGIA: Demolir uma árvore real
 * - Não cortamos o tronco antes dos galhos!
 * - Cortamos folhas → galhos → tronco
 * 
 * PARÂMETROS:
 * - nodo: raiz da subárvore a destruir
 * 
 * COMPLEXIDADE: O(n) - visita cada nodo uma vez
 */
static void destruirArvoreRecursivo(struct nodo *nodo) {
    // CASO BASE: NULL (subárvore vazia ou folha sem filhos)
    if (nodo == NULL) {
        return;
    }
    
    // RECURSÃO: Destrói filhos primeiro (pós-ordem)
    destruirArvoreRecursivo(nodo->esq);
    destruirArvoreRecursivo(nodo->dir);
    
    // Agora sim podemos liberar este nodo
    // IMPORTANTE: Liberar na ordem inversa da alocação!
    free(nodo->ponto);  // Primeiro o array de coordenadas
    free(nodo);         // Depois o nodo
}

/*
 * destruirArvore()
 * ----------------
 * Interface pública para destruir completamente uma KD-Tree.
 * 
 * Libera TODA a memória alocada:
 * - Todos os nodos (via destruirArvoreRecursivo)
 * - Todos os arrays de pontos
 * - A estrutura kdtree
 * 
 * IMPORTANTE: Chamar SEMPRE antes de encerrar o programa!
 * - Evita memory leaks
 * - Ferramentas como Valgrind reportarão "no leaks are possible"
 * 
 * PARÂMETROS:
 * - arvore: KD-Tree a destruir
 * 
 * APÓS CHAMAR ESTA FUNÇÃO:
 * - O ponteiro arvore fica inválido (dangling pointer)
 * - Não deve ser usado novamente sem criar nova árvore
 * 
 * COMPLEXIDADE: O(n) onde n é o número de nodos
 */
void destruirArvore(struct kdtree *arvore) {
    // Libera todos os nodos recursivamente
    destruirArvoreRecursivo(arvore->raiz);
    
    // Libera a estrutura da árvore
    free(arvore);
}

/*
 * ============================================================================
 * FIM DA IMPLEMENTAÇÃO
 * ============================================================================
 * 
 * RESUMO DAS OPERAÇÕES E COMPLEXIDADES:
 * 
 * Operação              | Melhor Caso | Caso Médio  | Pior Caso
 * ----------------------|-------------|-------------|------------
 * Criar árvore          | O(1)        | O(1)        | O(1)
 * Inserir               | O(log n)    | O(log n)    | O(n)
 * Buscar                | O(log n)    | O(log n)    | O(n)
 * k-NN (Z vizinhos)     | O(log n)    | O(z log n)  | O(n)
 * Destruir              | O(n)        | O(n)        | O(n)
 * 
 * VANTAGENS DA KD-TREE:
 * - Busca espacial eficiente
 * - k-NN muito mais rápido que busca linear O(n)
 * - Escalável para grandes datasets
 * - Funciona em qualquer dimensão k
 * 
 * DESVANTAGENS:
 * - Degrada para O(n) em dimensões muito altas (curse of dimensionality)
 * - Não é balanceada (pode degenerar)
 * - Remoção de elementos é complexa (não implementada aqui)
 * 
 * MELHORIAS POSSÍVEIS:
 * - Balanceamento (construir árvore balanceada inicialmente)
 * - Usar mediana para dividir pontos (em vez de primeiro ponto)
 * - Implementar remoção
 * - Otimizar para cache (locality)
 */

