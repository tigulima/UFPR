
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
    testes/a.txt         ~58B   - Muito pequeno (1 linha)
    testes/b.txt         ~235B  - Pequeno (3 linhas)
    testes/c.txt         ~451B  - Médio (6 linhas)
    testes/d.txt         ~827B  - Grande (12 linhas)
    testes/e.txt         ~1.2KB - Muito grande (18 linhas)
    testes/f.txt         ~1.8KB - Extra grande (27 linhas)
    testes/grande.txt    ~2.4KB - Múltiplos blocos (para testar visualização)


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
        $ ./gbv -a test.gbv testes/a.txt testes/b.txt testes/c.txt
        $ ./gbv -l test.gbv
        $ ./gbv -o test.gbv tamanho
        $ ./gbv -l test.gbv


DIFICULDADES ENFRENTADAS
------------------------
    • Entender a estrutura [Superbloco, doc1, doc2, Area de Dados] do arquivo binário e como os componentes se relacionam.

    • Compreender por que superbloco.directory_offset é long e não ponteiro, já que estamos trabalhando com endereçamento de arquivo.

    • Como carregar os ponteiros para os documentos na estrutura Library no gbv_open, especialmente entender porque os dados não precisam ser passados item por item para a lib->docs[i].

    • Entender por que usar strncpy(novo_doc->name, docname, MAX_NAME) em vez de novo_doc->name = docname, devido à natureza de arrays vs ponteiros.


MUDANÇAS FUTURAS
----------------

    • Adicionar uma função BuscarDocumento para reutilizar no View e no Remove, evitando código duplicado.

