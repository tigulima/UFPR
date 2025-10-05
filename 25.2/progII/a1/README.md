
GBV - Gerenciador de Biblioteca Virtual
=======================================

AUTORIA
-------
    GRR20204397 - Thiago Imai Lima


ARQUIVOS
--------
    gbv.c       Implementação das funções principais do gerenciador
    gbv.h       Declarações de estruturas e funções
    main.c      Programa principal e interface de linha de comando
    util.c      Funções utilitárias (formatação de data)
    util.h      Declarações das funções utilitárias
    Makefile    Arquivo de compilação
    README      Este arquivo


ARQUIVOS DE TESTE
-----------------
    Os arquivos estão propositalmente com tamanhos NÃO ordenados para
    facilitar o teste da funcionalidade de ordenação por tamanho.

    testes/a.txt         ~450B  - Médio (6 linhas)
    testes/b.txt         ~1.2KB - Grande (18 linhas)
    testes/c.txt         ~57B   - Muito pequeno (1 linha)
    testes/d.txt         ~234B  - Pequeno (3 linhas)
    testes/e.txt         ~826B  - Médio-grande (12 linhas)
    testes/f.txt         ~1.8KB - Muito grande (27 linhas)
    testes/grande.txt    ~2.4KB - Extra grande - múltiplos blocos

    Ordem crescente de tamanho: c < d < a < e < b < f < grande


COMPILAÇÃO E USO
----------------
    Compilar:
        $ make

    Uso:
        $ ./gbv <opção> <biblioteca> [documentos...]

    Opções:
        -a <docs>       Adiciona ou substitui documentos
        -r <docs>       Remove documentos
        -l              Lista todos os documentos
        -v <doc>        Visualiza documento (navegação: n/p/q)
        -o <critério>   Ordena por: nome, data ou tamanho

    Exemplo de teste rápido:
        $ printf '\x00\x00\x00\x00\x10\x00\x00\x00\x00\x00\x00\x00' > test.gbv
        $ ./gbv -a test.gbv testes/a.txt testes/b.txt testes/c.txt testes/d.txt
        $ ./gbv -l test.gbv                  # Lista em ordem de inserção
        $ ./gbv -o test.gbv nome             # Ordena alfabeticamente
        $ ./gbv -l test.gbv                  # Exibe: a, b, c, d
        $ ./gbv -o test.gbv tamanho          # Ordena por tamanho
        $ ./gbv -l test.gbv                  # Exibe: c(57B), d(234B), a(450B), b(1.2K)


DIFICULDADES ENFRENTADAS
------------------------
    • Entender a estrutura [Superbloco, doc1, doc2, Area de Dados] do arquivo binário e como os componentes se relacionam.

    • Compreender por que superbloco.directory_offset é long e não ponteiro, já que estamos trabalhando com endereçamento de arquivo.

    • Como carregar os ponteiros para os documentos na estrutura Library no gbv_open, especialmente entender porque os dados não precisam ser passados item por item para a lib->docs[i].

    • Entender por que usar strncpy(novo_doc->name, docname, MAX_NAME) em vez de novo_doc->name = docname, devido à natureza de arrays vs ponteiros.


MUDANÇAS FUTURAS
----------------

    • Adicionar uma função BuscarDocumento para reutilizar no View e no Remove, evitando código duplicado.

