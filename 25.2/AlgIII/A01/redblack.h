#ifndef REDBLACK_H_
#define REDBLACK_H_

// O enum usa 8 bytes (4 bytes para cada nó) ao invés
// de 1 byte que seria usado se fosse unsigned char
// (ou char mesmo). Mas preferi alterar por conta de 
// boas práticas. Na minha pesquisa, essa foi a
// implementação mais recomendada, considerando a
// segurança de funcionamento e leitura.
enum cor {
    VERMELHO,
    PRETO
};

struct nodo {
    int chave;
    enum cor cor;
    struct nodo *pai;
    struct nodo *esq;
    struct nodo *dir;
};

struct fila{
    struct fila_nodo* inicio;
    struct fila_nodo* fim;
    unsigned int tamanho;
};

struct fila_nodo{
    struct nodo* nodo;
    struct fila_nodo* prox; 
};

struct aluno{
    char* nome;//nome completo
    char* nomeDinf;//nome de usuário nas servidoras do dinf
    unsigned int grr;
};

struct aluno* getAluno();

void imprimirDadosAluno();

//retorna SENTINELA se não foi possível inserir
struct nodo* inserir(struct nodo** raiz, int chave);

// retorna o número de nodos excluídos
int excluir(struct nodo** raiz, int chave);

//retorna SENTINELA se não existe
struct nodo* buscar(struct nodo* raiz, int chave);

void imprimirEmOrdem(struct nodo* nodo);

void imprimirEmLargura(struct nodo* raiz);

// FUNÇÕES AUXILIARES
int ehSentinela(struct nodo* nodo);
struct nodo* criarArvore();
struct nodo* criarNodo(int chave);

// FUNÇÕES PARA EXCLUIR
struct nodo* buscarSucessor(struct nodo* nodo);
void transplantar(struct nodo** raiz, struct nodo* nodo, struct nodo* nodo_filho);

// FUNÇÕES DE FILA
struct fila* criarFila();
void enfileirar(struct fila** fila, struct nodo* nodo);
struct nodo* desenfileirar(struct fila** fila);

// FUNÇÕES DE FIXUP
void inserirFixup(struct nodo** raiz, struct nodo* novo_nodo);
void excluirFixup(struct nodo** raiz, struct nodo* nodo);
void rotacaoEsquerda(struct nodo** raiz, struct nodo* nodo_pivo);
void rotacaoDireita(struct nodo** raiz, struct nodo* nodo_pivo);

#endif//REDBLACK_H