
#GBV - Gerenciador de Biblioteca Virtual

###AUTORIA
-------
    GRR20204397 - Thiago Imai Lima


###ARQUIVOS
--------
    gbv.c       Implementação das funções principais do gerenciador
    gbv.h       Declarações de estruturas e funções
    main.c      Programa principal e interface de linha de comando
    util.c      Funções utilitárias (formatação de data)
    util.h      Declarações das funções utilitárias
    Makefile    Arquivo de compilação
    README      Este arquivo


###COMPILAÇÃO E USO
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


###DIFICULDADES ENFRENTADAS
------------------------
    • Entender a estrutura [Superbloco, doc1, doc2, Area de Dados] do arquivo binário e como os componentes se relacionam.

    • Compreender por que superbloco.directory_offset é long e não ponteiro, já que estamos trabalhando com endereçamento de arquivo.

    • Como carregar os ponteiros para os documentos na estrutura Library no gbv_open, especialmente entender porque os dados não precisam ser passados item por item para a lib->docs[i].

    • Entender por que usar strncpy(novo_doc->name, docname, MAX_NAME) em vez de novo_doc->name = docname, devido à natureza de arrays vs ponteiros.


###MUDANÇAS FUTURAS
----------------

    • Adicionar uma função BuscarDocumento para reutilizar no View e no Remove, evitando código duplicado.


================================================================================

