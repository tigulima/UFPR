CC = gcc
HOMEBREW_PREFIX = $(shell brew --prefix 2>/dev/null || echo /usr/local)
CFLAGS = -Wall -Wextra -std=c11 -I./include -I$(HOMEBREW_PREFIX)/include
LDFLAGS = -L$(HOMEBREW_PREFIX)/lib -lallegro -lallegro_main -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf

# LDFLAGS += -lallegro_audio -lallegro_acodec

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

# Arquivos fonte e objeto
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Nome do executável
TARGET = $(BIN_DIR)/game

# Regra padrão
all: $(TARGET)

# Cria o executável
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Compilação concluída! Execute com: ./$(TARGET)"

# Compila arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria diretórios necessários
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Arquivos compilados removidos"

rebuild: clean all

run: $(TARGET)
	./$(TARGET)

info:
	@echo "Fontes: $(SOURCES)"
	@echo "Objetos: $(OBJECTS)"
	@echo "Executável: $(TARGET)"

check-allegro:
	@echo "Verificando instalação do Allegro..."
	@pkg-config --modversion allegro-5 || echo "Allegro 5 não encontrado!"
	@pkg-config --libs allegro-5 allegro_primitives-5 allegro_image-5 allegro_font-5 allegro_ttf-5

.PHONY: all clean rebuild run info check-allegro

