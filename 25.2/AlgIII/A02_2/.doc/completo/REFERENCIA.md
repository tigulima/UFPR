# Referencia Rapida - KD-Tree Completa

## Comandos Disponiveis

### Operacoes Basicas
| Comando | Descricao | Entrada Adicional |
|---------|-----------|-------------------|
| `b` | Buscar ponto exato | K coordenadas |
| `z` | K-vizinhos mais proximos | Z (int) + K coordenadas |
| `i` | Inserir novo ponto | K coordenadas + classe |
| `r` | Remover ponto | K coordenadas |

### Impressao da Arvore
| Comando | Descricao | Ordem de Percurso |
|---------|-----------|-------------------|
| `1` | Pre-ordem | Raiz -> Esquerda -> Direita |
| `2` | Em-ordem | Esquerda -> Raiz -> Direita |
| `3` | Pos-ordem | Esquerda -> Direita -> Raiz |
| `4` | Por nivel | BFS (largura) |

### Informacoes
| Comando | Descricao | Retorno |
|---------|-----------|---------|
| `h` | Altura da arvore | Inteiro (altura) |
| `n` | Numero de nodos | Inteiro (quantidade) |

### Consultas Avancadas
| Comando | Descricao | Entrada Adicional |
|---------|-----------|-------------------|
| `c` | Listar por classe | Classe (int) |
| `m` | Minimo em dimensao | Dimensao (0 a K-1) |

### Controle
| Comando | Descricao |
|---------|-----------|
| `f` | Finalizar programa |

## Funcoes da API (kdtree_completo.h)

### Estruturas de Dados

```c
struct kdtree {
    struct nodo *raiz;
    unsigned int k;
};

struct nodo {
    float *ponto;
    int classe;
    struct nodo *esq;
    struct nodo *dir;
};
```

### Funcoes Principais

#### Criacao e Destruicao
```c
struct kdtree* criarArvore(unsigned int k);
void destruirArvore(struct kdtree *arvore);
```

#### Manipulacao
```c
struct kdtree* inserir(struct kdtree *arvore, float *ponto, int classe);
struct kdtree* remover(struct kdtree *arvore, float *ponto);
```

#### Busca
```c
struct nodo* buscar(struct kdtree *arvore, float *ponto);
struct lista_vizinhos* zVizinhos(struct kdtree *arvore, float *ponto, unsigned int z);
```

#### Impressao
```c
void imprimirPreOrdem(struct kdtree *arvore);
void imprimirEmOrdem(struct kdtree *arvore);
void imprimirPosOrdem(struct kdtree *arvore);
void imprimirPorNivel(struct kdtree *arvore);
```

#### Informacoes
```c
int altura(struct kdtree *arvore);
int contarNodos(struct kdtree *arvore);
int estaVazia(struct kdtree *arvore);
```

#### Consultas
```c
void listarPorClasse(struct kdtree *arvore, int classe);
int contarPorClasse(struct kdtree *arvore, int classe);
struct nodo* encontrarMinimo(struct kdtree *arvore, unsigned int dimensao);
```

## Complexidade das Operacoes

| Operacao | Melhor Caso | Caso Medio | Pior Caso |
|----------|-------------|------------|-----------|
| Inserir | O(log n) | O(log n) | O(n) |
| Buscar | O(log n) | O(log n) | O(n) |
| Remover | O(log n) | O(log n) | O(n) |
| k-NN | O(log n) | O(k log n) | O(n) |
| Altura | O(n) | O(n) | O(n) |
| Contar | O(n) | O(n) | O(n) |
| Imprimir | O(n) | O(n) | O(n) |

## Notas de Implementacao

### Remocao
- Usa encontrarMinimo para manter propriedade da KD-Tree
- Substitui nodo removido pelo minimo adequado
- Complexidade adicional devido a reorganizacao

### Impressao por Nivel
- Implementa BFS com fila encadeada
- Memoria adicional O(largura maxima)
- Util para visualizacao da estrutura

### Encontrar Minimo
- Busca recursiva considerando eixo de divisao
- Otimizado quando eixo coincide com dimensao
- Essencial para operacao de remocao

## Uso em Codigo

### Exemplo Basico
```c
// Criar arvore 2D
struct kdtree *arvore = criarArvore(2);

// Inserir pontos
float p1[] = {1.0, 2.0};
inserir(arvore, p1, 1);

// Buscar
struct nodo *resultado = buscar(arvore, p1);

// Limpar
destruirArvore(arvore);
```

### Exemplo k-NN
```c
float alvo[] = {2.5, 3.5};
struct lista_vizinhos *vizinhos = zVizinhos(arvore, alvo, 5);

for (int i = 0; i < vizinhos->tam; i++) {
    printf("Dist: %.2f\n", vizinhos->candidatos[i].dist);
}

free(vizinhos->candidatos);
free(vizinhos);
```

### Exemplo Remocao
```c
float p[] = {1.0, 2.0};
struct nodo *existe = buscar(arvore, p);

if (existe != NULL) {
    remover(arvore, p);
    printf("Removido\n");
}
```

## Arquivo de Teste

Ver `exemplo_teste.txt` para um exemplo completo de entrada.

Para executar:
```bash
./kdtree_completo < exemplo_teste.txt
```

