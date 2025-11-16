# KD-Tree Completa - Versao Estendida

Versao estendida da implementacao de KD-Tree com funcionalidades adicionais.

## Arquivos

- `kdtree_completo.h` - Header com todas as funcoes
- `kdtree_completo.c` - Implementacao completa
- `main_completo.c` - Programa principal interativo
- `makefile` - Compilacao automatica

## Compilacao

```bash
make
```

## Execucao

```bash
./kdtree_completo
```

## Funcionalidades Originais

- Criar arvore KD-Tree
- Inserir pontos
- Buscar pontos exatos
- Encontrar k-vizinhos mais proximos
- Destruir arvore

## Novas Funcionalidades

### Remocao
- `r` - Remover ponto da arvore

### Impressao
- `1` - Imprimir em pre-ordem (raiz -> esq -> dir)
- `2` - Imprimir em ordem (esq -> raiz -> dir)
- `3` - Imprimir em pos-ordem (esq -> dir -> raiz)
- `4` - Imprimir por nivel (BFS/largura)

### Informacoes
- `h` - Mostrar altura da arvore
- `n` - Contar total de nodos

### Consultas
- `c` - Listar todos os pontos de uma classe
- `m` - Encontrar minimo em uma dimensao especifica

### Manipulacao
- `i` - Inserir novo ponto interativamente

## Formato de Entrada

### Inicial
```
N K
x1 y1 ... classe1
x2 y2 ... classe2
...
```

### Comandos
Apos construir a arvore, digite comandos seguidos de enter.

## Exemplo de Uso

```
Insira N e K.
3 2
Insira os pontos.
1.0 2.0 1
3.0 4.0 2
5.0 1.0 1
Arvore construida.

Opcao: 4
Por nivel:
(3.00, 4.00) classe=2
(1.00, 2.00) classe=1
(5.00, 1.00) classe=1

Opcao: h
Altura da arvore: 2

Opcao: n
Total de nodos: 3

Opcao: c
Digite a classe:
1
Total de pontos: 2
Pontos da classe 1:
(1.00, 2.00) classe=1
(5.00, 1.00) classe=1

Opcao: f
```

## Notas Tecnicas

### Remocao de Nodos
A remocao mantem a propriedade da KD-Tree encontrando um substituto adequado:
- Se tem filho direito: substitui pelo minimo da subarvore direita
- Se so tem filho esquerdo: move para direita e remove minimo
- Se e folha: remove diretamente

### Impressao por Nivel
Usa BFS (Breadth-First Search) com fila para percorrer por nivel.

### Encontrar Minimo
Busca o nodo com menor valor em uma dimensao especifica, essencial para remocao.

## Diferencias do Original

- Todos os arquivos originais permanecem intactos
- Esta versao e independente e autocontida
- Comentarios focados nas funcionalidades novas
- Interface mais rica e interativa

