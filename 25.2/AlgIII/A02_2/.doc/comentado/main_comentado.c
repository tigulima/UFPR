/*
 * ============================================================================
 * PROGRAMA PRINCIPAL - INTERFACE COM KD-TREE
 * ============================================================================
 * 
 * OBJETIVO:
 * --------
 * Este programa demonstra o uso de uma KD-Tree para:
 * 1. Armazenar pontos multidimensionais classificados
 * 2. Buscar pontos específicos
 * 3. Encontrar vizinhos mais próximos (algoritmo k-NN)
 * 
 * FLUXO DO PROGRAMA:
 * -----------------
 * 1. Lê N (número de pontos) e K (número de dimensões)
 * 2. Constrói a KD-Tree inserindo N pontos
 * 3. Entra em loop de comandos interativos:
 *    - 'b': Buscar um ponto específico
 *    - 'z': Encontrar Z vizinhos mais próximos
 *    - 'f': Finalizar programa
 * 4. Libera toda a memória antes de encerrar
 * 
 * EXEMPLO DE USO:
 * --------------
 * Entrada:
 *   3 2          <- N=3 pontos, K=2 dimensões (2D)
 *   1.0 2.0 1    <- ponto (1.0, 2.0) da classe 1
 *   3.0 4.0 2    <- ponto (3.0, 4.0) da classe 2
 *   5.0 1.0 1    <- ponto (5.0, 1.0) da classe 1
 *   b            <- comando buscar
 *   3.0 4.0      <- buscar ponto (3.0, 4.0)
 *   z            <- comando vizinhos
 *   2            <- buscar 2 vizinhos
 *   2.0 3.0      <- vizinhos de (2.0, 3.0)
 *   f            <- finalizar
 * 
 * ESTRUTURA DE DADOS:
 * ------------------
 * Veja kdtree.h para detalhes das estruturas:
 * - struct kdtree: árvore principal
 * - struct nodo: nodo da árvore (armazena ponto + classe)
 * - struct lista_vizinhos: resultado da busca k-NN
 */

#include "kdtree.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * matarProgramaErroLeitura()
 * --------------------------
 * Função auxiliar chamada quando scanf() falha.
 * 
 * QUANDO ISSO ACONTECE?
 * - Entrada malformada (texto em vez de número)
 * - EOF (end-of-file) inesperado
 * - Erro de I/O
 * 
 * IMPORTANTE:
 * scanf() retorna o número de itens lidos com sucesso.
 * - scanf("%d", &x) retorna 1 se sucesso, 0 se falha
 * - Sempre verificar o valor de retorno!
 * 
 * O QUE FAZER EM CASO DE ERRO?
 * 1. Reportar ao usuário via stderr
 * 2. Encerrar com código de erro (1)
 * 
 * NOTA: Em produção, poderíamos:
 * - Pedir ao usuário para tentar novamente
 * - Logar o erro em arquivo
 * - Enviar telemetria
 */
static void matarProgramaErroLeitura() {
    fprintf(stderr, "Erro na leitura dos dados.");
    exit(1);  // Código 1 indica erro
}

/*
 * lerPontos()
 * -----------
 * Lê K coordenadas (floats) da entrada padrão e armazena no array.
 * 
 * FORMATO ESPERADO:
 * x1 x2 x3 ... xK  (números separados por espaço/newline)
 * 
 * EXEMPLO (K=3):
 * Entrada: 1.5 2.7 3.2
 * Resultado: ponto[0]=1.5, ponto[1]=2.7, ponto[2]=3.2
 * 
 * PARÂMETROS:
 * - K: número de coordenadas a ler
 * - ponto: array pré-alocado onde armazenar as coordenadas
 * 
 * TRATAMENTO DE ERROS:
 * Se scanf() falhar em qualquer coordenada:
 * 1. Libera a memória do ponto (evita leak)
 * 2. Encerra o programa com erro
 * 
 * POR QUE LIBERAR ANTES DE ENCERRAR?
 * Mesmo que o programa vá terminar, é boa prática:
 * - Demonstra código correto
 * - Facilita refatoração futura (pode mudar exit para return)
 * - Ferramentas de análise (Valgrind) ficam felizes
 * 
 * COMPLEXIDADE: O(K) - lê K valores
 */
static void lerPontos(unsigned int K, float *ponto) {
    // Lê cada coordenada do ponto
    for (unsigned int j = 0; j < K; j++) {
        // scanf retorna número de itens lidos com sucesso
        // %f lê um float
        if (scanf("%f", &ponto[j]) != 1) {
            // Falhou! Libera memória e encerra
            free(ponto);
            matarProgramaErroLeitura();
        }
    }
    // Se chegou aqui, sucesso! Todas as K coordenadas foram lidas
}

/*
 * carregarPontosNaArvore()
 * ------------------------
 * Lê N pontos da entrada padrão e os insere na KD-Tree.
 * 
 * FORMATO ESPERADO PARA CADA PONTO:
 * x1 x2 ... xK classe
 * 
 * Onde:
 * - x1...xK são as K coordenadas (floats)
 * - classe é um inteiro identificando a categoria do ponto
 * 
 * EXEMPLO (N=2, K=2):
 * Entrada:
 *   1.0 2.0 1    <- ponto (1.0, 2.0) classe 1
 *   3.0 4.0 2    <- ponto (3.0, 4.0) classe 2
 * 
 * ESTRATÉGIA DE MEMÓRIA:
 * Para cada ponto:
 * 1. Aloca memória temporária para o ponto
 * 2. Lê as coordenadas
 * 3. Lê a classe
 * 4. Insere na árvore (que faz uma CÓPIA interna)
 * 5. Libera memória temporária
 * 
 * POR QUE ALOCAR E LIBERAR A CADA ITERAÇÃO?
 * - A função inserir() faz cópia interna do ponto
 * - Não precisamos manter o ponto original
 * - Reaproveitar memória seria possível mas este design é mais claro
 * - Para N grande, poderia otimizar usando um único buffer
 * 
 * PARÂMETROS:
 * - arvore: KD-Tree onde inserir os pontos
 * - N: número de pontos a ler
 * - K: número de dimensões de cada ponto
 * 
 * COMPLEXIDADE: O(N * log N) típico
 * - O(N) iterações
 * - Cada inserção é O(log N) em média
 */
static void carregarPontosNaArvore(struct kdtree *arvore, unsigned int N, unsigned int K) {
    // Para cada ponto...
    for (unsigned int i = 0; i < N; i++) {
        // PASSO 1: Alocar memória temporária para o ponto
        float *ponto = (float *)malloc(K * sizeof(float));
        if (ponto == NULL) {
            // Falha crítica: sem memória disponível
            matarProgramaFaltaMemoria();
        }
        
        // PASSO 2: Ler as K coordenadas
        lerPontos(K, ponto);
        
        // PASSO 3: Ler a classe do ponto
        int classe;
        if (scanf("%d", &classe) != 1) {
            // Erro de leitura! Liberar ponto antes de encerrar
            free(ponto);
            matarProgramaErroLeitura();
        }

        // PASSO 4: Inserir na árvore
        // IMPORTANTE: inserir() faz uma cópia interna do ponto
        // Então após esta chamada, ponto pode ser liberado
        inserir(arvore, ponto, classe);
        
        // PASSO 5: Liberar memória temporária
        free(ponto);
    }
}

/*
 * main()
 * ------
 * Função principal do programa.
 * 
 * ESTRUTURA:
 * 1. INICIALIZAÇÃO: Ler parâmetros e construir árvore
 * 2. LOOP INTERATIVO: Processar comandos do usuário
 * 3. FINALIZAÇÃO: Liberar memória
 * 
 * COMANDOS SUPORTADOS:
 * - 'b' (buscar): Busca um ponto exato na árvore
 * - 'z' (z-vizinhos): Encontra Z vizinhos mais próximos
 * - 'f' (finalizar): Encerra o programa
 * 
 * RETORNO:
 * - 0: sucesso
 * - 1: erro (via exit() nas funções auxiliares)
 */
int main() {
    unsigned int n, k;

    // ========================================================================
    // FASE 1: INICIALIZAÇÃO
    // ========================================================================
    
    /*
     * Ler parâmetros iniciais:
     * - n: número de pontos a inserir
     * - k: número de dimensões (2D, 3D, etc.)
     */
    printf("Insira N e K.\n");
    if (scanf("%u %u", &n, &k) != 2) {
        // scanf retorna 2 se leu ambos os valores com sucesso
        matarProgramaErroLeitura();
    }

    /*
     * Criar árvore vazia com k dimensões
     * 
     * IMPORTANTE: k deve ser consistente em toda a árvore
     * Todos os pontos devem ter exatamente k coordenadas
     */
    struct kdtree *arvore = criarArvore(k);

    /*
     * Carregar todos os n pontos na árvore
     * 
     * Esta é a fase de "treinamento" para algoritmos de classificação
     * Estamos construindo a base de conhecimento
     */
    printf("Insira os pontos.\n");
    carregarPontosNaArvore(arvore, n, k);
    printf("Árvore construída.\n");

    // ========================================================================
    // FASE 2: LOOP INTERATIVO DE COMANDOS
    // ========================================================================
    
    /*
     * Lê e processa comandos até receber 'f' (finalizar)
     * 
     * FORMATO DOS COMANDOS:
     * - 'b': seguido por K coordenadas
     * - 'z': seguido por Z (int) e K coordenadas
     * - 'f': sem parâmetros adicionais
     * 
     * NOTA: " %c" (com espaço) no scanf ignora whitespace antes do char
     * Isso é importante para consumir newlines deixados por scanf anteriores
     */
    char op;
    scanf(" %c", &op);  // Espaço antes de %c ignora whitespace
    
    while (op != 'f') {  // Loop até comando 'f' (finalizar)
        switch (op) {
            
            // ================================================================
            // COMANDO 'b': BUSCAR PONTO EXATO
            // ================================================================
            case 'b':
                {
                    /*
                     * Busca um ponto específico na árvore.
                     * 
                     * APLICAÇÃO:
                     * - Verificar se um ponto já existe
                     * - Obter classificação de um ponto conhecido
                     * 
                     * IMPORTANTE: Esta é busca EXATA
                     * - Só encontra se o ponto exato existir
                     * - Para "ponto mais próximo", usar comando 'z'
                     */
                    
                    // PASSO 1: Alocar memória para o ponto de busca
                    float *ponto = (float *)malloc(k * sizeof(float));
                    if (ponto == NULL) {
                        matarProgramaFaltaMemoria();
                    }
                    
                    // PASSO 2: Ler as k coordenadas
                    lerPontos(k, ponto);

                    // PASSO 3: Buscar na árvore
                    struct nodo *resultado = buscar(arvore, ponto);

                    // PASSO 4: Mostrar resultado
                    if (resultado != NULL) {
                        // Encontrou! Mostrar classe
                        printf("Encontrado. Classe %d.\n", resultado->classe);
                    } else {
                        // Não encontrou ponto exato
                        printf("Não encontrado.\n");
                    }

                    // PASSO 5: Liberar memória temporária
                    free(ponto);
                    break;
                }
            
            // ================================================================
            // COMANDO 'z': Z VIZINHOS MAIS PRÓXIMOS (k-NN)
            // ================================================================
            case 'z':
                {
                    /*
                     * Encontra os Z vizinhos mais próximos de um ponto.
                     * 
                     * APLICAÇÕES:
                     * - Algoritmo k-NN para classificação
                     *   Exemplo: Se k=3 e 2 vizinhos são classe A e 1 é classe B,
                     *            classifica como A (maioria)
                     * 
                     * - Sistemas de recomendação
                     *   Exemplo: Usuário similar → recomendar itens similares
                     * 
                     * - Interpolação espacial
                     *   Exemplo: Estimar temperatura em local sem sensor
                     *            baseado em sensores próximos
                     * 
                     * - Detecção de outliers
                     *   Exemplo: Se vizinhos estão muito longe, é anomalia
                     */
                    
                    // PASSO 1: Ler quantos vizinhos procurar
                    unsigned int z;
                    if (scanf("%u", &z) != 1) {
                        matarProgramaErroLeitura();
                    }

                    // PASSO 2: Alocar memória para o ponto de referência
                    float *ponto = (float *)malloc(k * sizeof(float));
                    if (ponto == NULL) {
                        matarProgramaFaltaMemoria();
                    }
                    
                    // PASSO 3: Ler as k coordenadas do ponto de referência
                    lerPontos(k, ponto);

                    // PASSO 4: Buscar os Z vizinhos mais próximos
                    /*
                     * IMPORTANTE: zVizinhos() retorna uma lista alocada dinamicamente
                     * A lista contém:
                     * - candidatos: array de Z candidatos (nodo + distância)
                     * - tam: número real de vizinhos encontrados (pode ser < z)
                     * 
                     * RESPONSABILIDADE: Devemos liberar lista->candidatos e lista!
                     */
                    struct lista_vizinhos *vizinhos = zVizinhos(arvore, ponto, z);

                    // PASSO 5: Exibir resultados
                    printf("Vizinhos mais próximos:\n");
                    
                    // Itera sobre os vizinhos encontrados
                    // NOTA: tam pode ser menor que z se árvore tem poucos pontos
                    for (int i = 0; i < vizinhos->tam; i++) {
                        // Obtém referência ao nodo vizinho
                        struct nodo *v = vizinhos->candidatos[i].nodo;
                        
                        // Imprime as coordenadas do ponto
                        for (int j = 0; j < k; j++) {
                            // %.1f = um dígito decimal
                            // Imprime vírgula entre coordenadas, exceto no último
                            printf("%.1f%s", v->ponto[j], (j == k - 1) ? "" : ", ");
                        }
                        
                        // Imprime classe e distância
                        // %.4f = quatro dígitos decimais para distância
                        printf(" (classe %d), dist = %.4f\n", 
                               v->classe, 
                               vizinhos->candidatos[i].dist);
                    }
                    
                    /*
                     * ANÁLISE DO RESULTADO:
                     * 
                     * Lista está ordenada por distância (menor → maior):
                     * - vizinhos->candidatos[0] é o MAIS PRÓXIMO
                     * - vizinhos->candidatos[tam-1] é o MAIS DISTANTE dos Z
                     * 
                     * PARA k-NN CLASSIFICAÇÃO:
                     * Implementar votação por maioria:
                     * 
                     * int votos[NUM_CLASSES] = {0};
                     * for (int i = 0; i < vizinhos->tam; i++) {
                     *     int classe = vizinhos->candidatos[i].nodo->classe;
                     *     votos[classe]++;
                     * }
                     * int classe_predita = argmax(votos);
                     * 
                     * VARIAÇÃO: Votação ponderada por distância
                     * Vizinhos mais próximos têm mais "peso":
                     * 
                     * peso = 1.0 / (dist + epsilon);
                     * votos[classe] += peso;
                     */

                    // PASSO 6: Liberar memória
                    // ORDEM IMPORTANTE: Liberar array antes da estrutura
                    free(vizinhos->candidatos);  // Array de candidatos
                    free(vizinhos);               // Estrutura lista_vizinhos
                    free(ponto);                  // Ponto de referência
                    break;
                }
            
            // ================================================================
            // COMANDO INVÁLIDO
            // ================================================================
            default:
                /*
                 * Comando não reconhecido.
                 * 
                 * MELHORIA POSSÍVEL:
                 * - Adicionar comando 'h' (help) para mostrar ajuda
                 * - Adicionar comando 'i' para inserir novo ponto
                 * - Adicionar comando 's' para estatísticas da árvore
                 */
                printf("Operação inválida.\n");
                break;
        }
        
        // Lê próximo comando
        // NOTA: Espaço antes de %c consome whitespace (newlines, espaços)
        scanf(" %c", &op);
    }

    // ========================================================================
    // FASE 3: FINALIZAÇÃO E LIMPEZA
    // ========================================================================
    
    /*
     * Destruir árvore e liberar TODA a memória alocada.
     * 
     * IMPORTANTE: Sempre chamar antes de encerrar!
     * 
     * Esta função libera:
     * - Todos os N nodos
     * - Todos os N arrays de pontos (k floats cada)
     * - A estrutura kdtree
     * 
     * VERIFICAÇÃO:
     * Execute com Valgrind para verificar memory leaks:
     * 
     * $ valgrind --leak-check=full ./programa
     * 
     * Resultado esperado:
     * "All heap blocks were freed -- no leaks are possible"
     * 
     * No macOS, use a ferramenta 'leaks':
     * 
     * $ leaks --atExit -- ./programa
     */
    destruirArvore(arvore);
    
    /*
     * Retorna 0 indicando sucesso
     * 
     * CONVENÇÕES:
     * - 0: programa executou sem erros
     * - 1-255: código de erro (usado em matarPrograma...)
     * 
     * Em scripts shell, pode-se verificar:
     * $ ./programa
     * $ echo $?  # Mostra código de retorno
     */
    return 0;
}

/*
 * ============================================================================
 * NOTAS FINAIS E MELHORIAS POSSÍVEIS
 * ============================================================================
 * 
 * TESTES SUGERIDOS:
 * ----------------
 * 
 * 1. Teste básico 2D:
 *    3 2          # 3 pontos, 2D
 *    0 0 1        # origem, classe 1
 *    1 0 1        # ponto à direita
 *    0 1 2        # ponto acima, classe 2
 *    z 2          # buscar 2 vizinhos
 *    0.5 0.5      # do ponto central
 *    # Espera: (0,1) e (1,0) ou (0,0) e (1,0) dependendo da ordem
 *    f
 * 
 * 2. Teste de busca exata:
 *    2 2
 *    1 1 5
 *    2 2 7
 *    b
 *    1 1          # Deve encontrar classe 5
 *    b
 *    1.5 1.5      # Não deve encontrar (busca exata)
 *    f
 * 
 * 3. Teste 3D:
 *    4 3
 *    0 0 0 1
 *    1 1 1 1
 *    2 2 2 2
 *    3 3 3 2
 *    z 3
 *    1.5 1.5 1.5  # Buscar 3 vizinhos mais próximos
 *    f
 * 
 * MELHORIAS POSSÍVEIS:
 * -------------------
 * 
 * 1. INTERFACE:
 *    - Menu interativo mais amigável
 *    - Validação de entrada mais robusta
 *    - Feedback de progresso para grandes datasets
 * 
 * 2. FUNCIONALIDADES:
 *    - Salvar/carregar árvore de arquivo
 *    - Inserção dinâmica durante operação
 *    - Remoção de pontos
 *    - Busca por range (todos os pontos em uma região)
 * 
 * 3. OTIMIZAÇÕES:
 *    - Construir árvore balanceada (ordenar por mediana)
 *    - Cache de distâncias calculadas
 *    - Paralelização (OpenMP/pthreads)
 *    - Versão iterativa em vez de recursiva (evita stack overflow)
 * 
 * 4. ANÁLISE E DEBUG:
 *    - Estatísticas da árvore (altura, balanceamento)
 *    - Visualização da árvore (GraphViz)
 *    - Modo verbose para debug
 *    - Benchmarking de performance
 * 
 * 5. ROBUSTEZ:
 *    - Tratamento de valores NaN/Inf
 *    - Limites de dimensão k
 *    - Proteção contra overflow em cálculos
 *    - Modo seguro (validações extras)
 * 
 * RECURSOS ADICIONAIS:
 * -------------------
 * 
 * Para aprender mais sobre KD-Trees:
 * - "Introduction to Algorithms" (CLRS) - Capítulo sobre estruturas espaciais
 * - Wikipedia: K-d tree
 * - Visualização: https://www.cs.usfca.edu/~galles/visualization/KDTree.html
 * 
 * Para algoritmo k-NN:
 * - "Pattern Recognition and Machine Learning" (Bishop)
 * - Scikit-learn documentation (Python)
 * 
 * COMPARAÇÃO COM ALTERNATIVAS:
 * ---------------------------
 * 
 * Estrutura      | Construção | Busca     | k-NN      | Uso de memória
 * ---------------|------------|-----------|-----------|----------------
 * Array linear   | O(1)       | O(n)      | O(n)      | Mínimo
 * KD-Tree        | O(n log n) | O(log n)  | O(log n)  | O(n)
 * Ball Tree      | O(n log n) | O(log n)  | O(log n)  | O(n)
 * VP-Tree        | O(n log n) | O(log n)  | O(log n)  | O(n)
 * 
 * ESCOLHA:
 * - KD-Tree: Melhor para k pequeno (2D, 3D)
 * - Ball/VP-Tree: Melhor para k grande (>10 dimensões)
 * - Array linear: Melhor para datasets muito pequenos (n < 100)
 */

