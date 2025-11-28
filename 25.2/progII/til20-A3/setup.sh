#!/bin/bash
# Script de setup e verificação do ambiente

echo "=== Setup - Plataforma de Sobrevivência ==="
echo ""

# Detecta sistema operacional
if [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macOS"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="Linux"
else
    OS="Desconhecido"
fi

echo "Sistema detectado: $OS"
echo ""

# Verifica se o Allegro está instalado
echo "Verificando dependências..."
if pkg-config --exists allegro-5; then
    ALLEGRO_VERSION=$(pkg-config --modversion allegro-5)
    echo "✓ Allegro 5 instalado (versão $ALLEGRO_VERSION)"
    
    # Verifica addons necessários
    REQUIRED_ADDONS=("allegro_primitives-5" "allegro_image-5" "allegro_font-5" "allegro_ttf-5")
    ALL_OK=true
    
    for addon in "${REQUIRED_ADDONS[@]}"; do
        if pkg-config --exists "$addon"; then
            echo "  ✓ $addon"
        else
            echo "  ✗ $addon - NÃO ENCONTRADO"
            ALL_OK=false
        fi
    done
    
    if [ "$ALL_OK" = true ]; then
        echo ""
        echo "✓ Todas as dependências estão instaladas!"
        echo ""
        echo "Para compilar e executar:"
        echo "  make"
        echo "  ./bin/game"
        echo ""
        echo "Ou simplesmente:"
        echo "  make run"
    else
        echo ""
        echo "⚠ Alguns addons do Allegro não foram encontrados"
    fi
else
    echo "✗ Allegro 5 não está instalado!"
    echo ""
    echo "Para instalar:"
    
    if [[ "$OS" == "macOS" ]]; then
        echo "  brew install allegro"
    elif [[ "$OS" == "Linux" ]]; then
        if [ -f /etc/debian_version ]; then
            echo "  sudo apt-get install liballegro5-dev"
        elif [ -f /etc/fedora-release ]; then
            echo "  sudo dnf install allegro5-devel"
        else
            echo "  Consulte a documentação do Allegro para seu sistema"
        fi
    fi
fi

echo ""
echo "=== Estrutura do Projeto ==="
echo ""
echo "src/           - Código fonte (.c)"
echo "include/       - Headers (.h)"
echo "assets/        - Recursos (sprites, backgrounds, sons)"
echo "bin/           - Executável (criado após compilação)"
echo "obj/           - Arquivos objeto (criado após compilação)"
echo ""
echo "Para mais informações, consulte README.md"

