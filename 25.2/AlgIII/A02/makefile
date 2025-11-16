# parametrosCompilacao=-Wall #-Wshadow
# nomePrograma=prova4_20204397

# all: $(nomePrograma)

# $(nomePrograma): main.o kdtree.o
# 	gcc -o $(nomePrograma) main.o kdtree.o $(parametrosCompilacao) -lm

# main.o: main.c
# 	gcc -c main.c $(parametrosCompilacao)

# ordenacao.o: kdtree.h kdtree.c
# 	gcc -c kdtree.c $(parametrosCompilacao)

# clean:
# 	rm -f *.o *.gch $(nomePrograma)







CC = gcc

# Flags de Compilação (MUITO ESTRITAS, como o PDF exige)
# -Wall -Wextra: Ativa quase todos os avisos
# -pedantic: Exige conformidade estrita com o padrão C
# -std=c99: Usa o padrão C99 (ou c11)
# -g: Inclui símbolos de depuração (útil para o GDB)
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g

# Flags do Linker
# -lm: Linka a biblioteca matemática (para sqrt, pow, fabs)
LDFLAGS = -lm

GRR = 20204397
TARGET = prova4_$(GRR)

SOURCES = main.c kdtree.c
OBJECTS = $(SOURCES:.c=.o)

# --- Regras de Compilação ---

# Regra principal (default): o que 'make' faz
# Cria o binário final (TARGET)
all: $(TARGET)

# Regra para linkar o programa final a partir dos .o
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Regra genérica para compilar .c em .o
# "Para fazer um .o, pegue o .c correspondente"
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Regras de Limpeza ---

# 'make clean' remove os arquivos compilados 
clean:
	rm -f $(OBJECTS) $(TARGET)

# 'make spotless' é mais agressivo (se você tiver outros arquivos)
spotless: clean
	# Adicione outros arquivos para limpar aqui, se necessário

.PHONY: all clean spotless