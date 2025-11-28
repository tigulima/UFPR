# Plataforma de Sobrevivência

Jogo de plataforma 2D desenvolvido em C usando a biblioteca Allegro 5.

## Requisitos

- GCC (compilador C)
- Allegro 5 e seus addons:
  - allegro5
  - allegro_primitives
  - allegro_image
  - allegro_font
  - allegro_ttf

## Instalação do Allegro

### macOS
```bash
brew install allegro
```

### Dinf
```bash
sudo apt-get install liballegro5-dev
```

## Compilação

Para compilar o projeto, execute:
```bash
make
```

Para limpar arquivos compilados:
```bash
make clean
```

Para recompilar do zero:
```bash
make rebuild
```

## Execução

Após compilar, execute o jogo com:
```bash
./bin/game
```

Ou use:
```bash
make run
```

## Controles

- **Setas/AD**: Movimentar o personagem
- **Espaço**: Pular
- **ESC**: Voltar ao menu (durante o jogo)
- **Enter**: Selecionar opção no menu