#ifndef REDBLACK_H_
#define REDBLACK_H_

// O enum usa 8 bytes (4 bytes para cada nó) ao invés
// de 1 byte que seria usado se fosse unsigned char
// (ou char mesmo). Mas preferi alterar por conta de 
// boas práticas. Na minha pesquisa, essa foi a
// implementação mais recomendada, considerando a
// segurança de funcionamento e leitura.
typedef enum {
    VERMELHO,
    PRETO
} Cor;

struct nodo {
    int chave;
    Cor cor;
    struct nodo *pai;
    struct nodo *esq;
    struct nodo *dir;
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

//funções complementares

struct nodo* criarNodo(int chave);

void insertFixup(struct nodo* raiz);

#endif//REDBLACK_H