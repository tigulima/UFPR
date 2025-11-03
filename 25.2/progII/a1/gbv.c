#include "gbv.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int doc_count;
    long directory_offset;
} Superblock;

// Declarações das funções de comparação
int compare_by_name(const void *a, const void *b);
int compare_by_date(const void *a, const void *b);
int compare_by_size(const void *a, const void *b);

int gbv_create(const char *filename) {
    // Abre o arquivo em modo "write binary". Se o arquivo já existe, ele será sobrescrito.
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("gbv_create: Erro ao criar biblioteca");
        return -1;
    }

    Superblock sb;
    sb.doc_count = 0;
    sb.directory_offset = sizeof(Superblock);

    // Escreve o superbloco no início do arquivo
    // fwrite(ponteiro_para_dados, tamanho_de_cada_bloco, quantos_blocos, arquivo);
    fwrite(&sb, sizeof(Superblock), 1, fp);
    fclose(fp);

    printf("Biblioteca %s criada. \n", filename);
    return 0;
}

int gbv_open(Library *lib, const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Biblioteca %s não encontrada. Criando nova biblioteca.\n", filename);
        if (gbv_create(filename) != 0) {
            perror("gbv_add: Erro ao criar a nova biblioteca");
            return -1;
        }
        fp = fopen(filename, "r+b");
        if (fp == NULL) {
            perror("gbv_add: Erro ao abrir a nova biblioteca");
            return -1;
        }
    }

    // Carrega o Superbloco para a RAM
    Superblock sb;
    fread(&sb, sizeof(Superblock), 1, fp);

    // Se não há documentos, inicializamos a biblioteca como vazia e terminamos.
    if (sb.doc_count == 0) {
        lib->docs = NULL;
        lib->count = 0;
        fclose(fp);
        return 0;
    }

    // Posiciona o curser de leitura no início da Area de Diretorio
    fseek(fp, sb.directory_offset, SEEK_SET);

    // Aloca espaço para os documentos do arquivo serem carregados na RAM
    lib->docs = (Document *) malloc(sb.doc_count * sizeof(Document));
    if(lib->docs == NULL) {
        perror("gbv_open: Falha ao alocar memória para o diretório");
        fclose(fp);
        return -1;
    }

    // Carrega os documentos na RAM
    fread(lib->docs, sizeof(Document), sb.doc_count, fp);
    lib->count = sb.doc_count;

    fclose(fp);
    return 0;
}

int gbv_add(Library *lib, const char *archive, const char *docname) {
    Superblock sb;

    // Abrindo o arquivo que vamos ler e o arquivo que vamos escrever
    FILE *archive_fp = fopen(archive, "r+b");
    if (archive_fp == NULL) {
        perror("gbv_add: Não foi possível abrir o arquivo");
        return -1;
    }

    FILE *doc_fp = fopen(docname, "rb");
    if (doc_fp == NULL) {
        perror("gbv_add: Não foi possível abrir o documeto para adição");
        fclose(archive_fp);
        return -1;
    }

    // Leio o Superbloco, já que ele não é chamado nos parâmetros da func
    fread(&sb, sizeof(Superblock), 1, archive_fp);

    // Verifica se já existe um documento com o mesmo nome (para substituir)
    int index_existente = -1;
    for (int i = 0; i < lib->count; i++) {
        if (strcmp(lib->docs[i].name, docname) == 0) {
            index_existente = i;
            break;
        }
    }

    // Se não existe, aloca espaço para um novo documento
    Document *novo_doc;
    if (index_existente == -1) {
        Document *novo_ponteiro = realloc(lib->docs, (lib->count + 1) * sizeof(Document));
        if (novo_ponteiro == NULL) {
            perror("gbv_add: Erro ao realocar memória para o novo documento");
            fclose(archive_fp);
            fclose(doc_fp);
            return -1;
        }
        lib->docs = novo_ponteiro;
        novo_doc = &lib->docs[lib->count];
    } else {
        // Se existe, apenas atualiza o documento existente
        novo_doc = &lib->docs[index_existente];
    }

    //  --- Descobrindo o tamanho do arquivo ---
    // O arquivo doc_fp já está aberto
    fseek(doc_fp, 0, SEEK_END);        // Mando o cursor de leitura pro final do arquivo
    long doc_size = ftell(doc_fp);     // Vejo quantos bytes ele andou e salvo na var
    rewind(doc_fp);                    // Volta o cursor para o início do doc

    // --- Atualizando o novo documento ---
    // Usamos strncpy aqui pq docname é string e novo_doc->name é um Array de 256b
    strncpy(novo_doc->name, docname, MAX_NAME);
    novo_doc->name[MAX_NAME - 1] = '\0';
    novo_doc->size = doc_size;
    novo_doc->date = time(NULL);
    novo_doc->offset = sb.directory_offset;

    // --- Escrevendo os dados do doc no arquivo ---
    // Coloca o cursor no local onde devemos escrever os dados do doc no aquivo
    fseek(archive_fp, novo_doc->offset, SEEK_SET);

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    // Enquanto consigo ler bytes do doc, escreve no arquivo
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, doc_fp)) > 0) {
        fwrite(buffer, 1, bytes_read, archive_fp);
    }

    fclose(doc_fp);

    // --- Atualizar metadados ---
    // Atualizando o diretório os os dados do docs
    long new_directory_offset = ftell(archive_fp);
    
    // Se foi adição, incrementa o count; se foi substituição, mantém
    int new_count = (index_existente == -1) ? lib->count + 1 : lib->count;
    fwrite(lib->docs, sizeof(Document), new_count, archive_fp);

    // Atualizando o superbloco
    sb.doc_count = new_count;
    sb.directory_offset = new_directory_offset;
    fseek(archive_fp, 0, SEEK_SET);
    fwrite(&sb, sizeof(Superblock), 1, archive_fp);

    fclose(archive_fp);
    
    if (index_existente == -1) {
        lib->count++;
        printf("Documento %s adicionado.\n", docname);
    } else {
        printf("Documento %s substituído.\n", docname);
    }
    return 0;
}

int gbv_remove(Library *lib, const char *archive, const char *docname) {
    FILE *archive_fp = fopen(archive, "r+b");
    if (archive_fp == NULL) {
        perror("gbv_remove: Não foi possível abrir o arquivo");
        return -1;
    }

    // Encontra o índice do elemento que deve ser excluído
    int index_to_remove = -1;
    for (int i = 0; i < lib->count; i++) {
        if (strcmp(lib->docs[i].name, docname) == 0) {
            index_to_remove = i;
            break;
        }
    }

    if (index_to_remove == -1) {
        printf("Documento %s não encontrado na biblioteca.\n", docname);
        return -1;
    }

    for (int i = index_to_remove; i < lib->count; i++) {
        lib->docs[i] = lib->docs[i + 1];
    }

    lib->count--;


    Superblock sb;
    fread(&sb, sizeof(Superblock), 1, archive_fp);

    // Escreve novo diretório
    fseek(archive_fp, sb.directory_offset, SEEK_SET);
    fwrite(lib->docs, sizeof(Document), lib->count, archive_fp);

    // Escreve novo superbloco
    sb.doc_count = lib->count;
    fseek(archive_fp, 0, SEEK_SET);
    fwrite(&sb, sizeof(Superblock), 1, archive_fp);

    fclose(archive_fp);

    printf("Documento %s foi removido.\n", docname);
    return 0;
}

int gbv_list(const Library *lib) {
    if (lib->count == 0) {
        printf("A biblioteca está vazia.\n");
        return 0;
    }

    // Imprime o cabeçalho
    printf("%-30s %-12s %-22s %-10s\n", "NOME", "TAMANHO (B)", "DATA DE INSERÇÃO", "POSIÇÃO");
    printf("--------------------------------------------------------------------------------\n");

    char date_buffer[100];

    for (int i = 0; i < lib->count; i++) {
        Document doc = lib->docs[i];

        format_date(doc.date, date_buffer, sizeof(date_buffer));

        printf("%-30s %-12ld %-22s %-10ld\n",
               doc.name,
               doc.size,
               date_buffer,
               doc.offset);
    }
    return 0;
}

int gbv_view(const Library *lib, const char *archive, const char *docname) {
    // Acha o documento na biblioteca em memória
    Document *doc_to_view = NULL;
    for (int i = 0; i < lib->count; i++) {
        if (strcmp(lib->docs[i].name, docname) == 0) {
            doc_to_view = &lib->docs[i];
            break;
        }
    }

    // Se não achou, retorna erro
    if (doc_to_view == NULL) {
        printf("Documento '%s' não encontrado.\n", docname);
        return -1;
    }

    FILE *archive_fp = fopen(archive, "rb");
    if (archive_fp == NULL) {
        perror("gbv_view: Não foi possível abrir o arquivo");
        return -1;
    }

    long total_blocks = (doc_to_view->size + BUFFER_SIZE) / BUFFER_SIZE;
    if (doc_to_view->size == 0) total_blocks = 0;
    int current_block = 0;
    char buffer[BUFFER_SIZE];

    while(1) {
        // Calcula a posição atual no arquivo
        long position = doc_to_view->offset + (current_block * BUFFER_SIZE);
        fseek(archive_fp, position, SEEK_SET);

        size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, archive_fp);
        if (bytes_read > 0) {
            fwrite(buffer, 1, bytes_read, stdout);
        }

        printf("\n-- Bloco %d/%ld -- (n: próximo, p: anterior, q: sair) --\n", current_block + 1, total_blocks);

        char command = getchar();
        while (getchar() != '\n'); // Limpa o buffer de entrada

        if (command == 'q') {
                break; // Sai do laço   
        } else if (command == 'n') {
            if (current_block < total_blocks - 1) {
                current_block++;
            } else {
                printf("Já está no último bloco.\n");
            }
        } else if (command == 'p') {
            if (current_block > 0) {
                current_block--;
            } else {
                printf("Já está no primeiro bloco.\n");
            }
        }
    }

    fclose(archive_fp);
    return 0;
}

int compare_by_name(const void *a, const void *b) {
    Document *docA = (Document *)a;
    Document *docB = (Document *)b;
    return strcmp(docA->name, docB->name);
}

int compare_by_date(const void *a, const void *b) {
    Document *docA = (Document *)a;
    Document *docB = (Document *)b;
    if (docA->date < docB->date) return -1;
    if (docA->date > docB->date) return 1;
    return 0;
}

int compare_by_size(const void *a, const void *b) {
    Document *docA = (Document *)a;
    Document *docB = (Document *)b;
    if (docA->size < docB->size) return -1;
    if (docA->size > docB->size) return 1;
    return 0;
}

int gbv_order(Library *lib, const char *archive, const char *criteria) {
    FILE *archive_fp = fopen(archive, "r+b");
    if (archive_fp == NULL) {
        perror("gbv_order: Não foi possível abrir o arquivo");
        return -1;
    }

    // Seleciona a função de comparação baseada no critério
    int (*compare_func)(const void *, const void *);
    const char *criterio_nome;
    
    if (strcmp(criteria, "nome") == 0) {
        compare_func = compare_by_name;
        criterio_nome = "nome (ordem alfabética)";
    } else if (strcmp(criteria, "data") == 0) {
        compare_func = compare_by_date;
        criterio_nome = "data (ordem cronológica)";
    } else if (strcmp(criteria, "tamanho") == 0) {
        compare_func = compare_by_size;
        criterio_nome = "tamanho (ordem crescente)";
    } else {
        printf("Critério inválido. Use: nome, data ou tamanho.\n");
        fclose(archive_fp);
        return -1;
    }

    qsort(lib->docs, lib->count, sizeof(Document), compare_func);

    Superblock sb;
    fread(&sb, sizeof(Superblock), 1, archive_fp);

    fseek(archive_fp, sb.directory_offset, SEEK_SET);
    fwrite(lib->docs, sizeof(Document), lib->count, archive_fp);

    fclose(archive_fp);

    printf("Biblioteca ordenada por %s.\n", criterio_nome);
    return 0;
}

char* gbv_derivacao(Library *lib, const char *archive) {
    // apaga .gbv do archive
    char *base_name = strndup(archive, strlen(archive) - 4);
    char *archive_z = strncat(strdup(base_name), "_z.gbv", 10);


    if (gbv_create(archive_z) != 0) {
        perror("gbv_add: Erro ao criar a nova biblioteca");
        return NULL;
    }
    
    return archive_z;
}