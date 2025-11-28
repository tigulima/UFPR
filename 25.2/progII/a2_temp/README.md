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

### Linux (Ubuntu/Debian)
```bash
sudo apt-get install liballegro5-dev
```

### Linux (Fedora)
```bash
sudo dnf install allegro5-devel
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

- **Setas/WASD**: Movimentar o personagem
- **Espaço**: Pular
- **S/Seta para baixo**: Agachar
- **ESC**: Voltar ao menu (durante o jogo)
- **Enter**: Selecionar opção no menu

## Estrutura do Projeto

```
.
├── bin/              # Executável compilado
├── obj/              # Arquivos objeto (.o)
├── src/              # Código fonte (.c)
│   ├── main.c
│   ├── game.c
│   ├── menu.c
│   ├── player.c
│   ├── level.c
│   ├── obstacles.c
│   └── utils.c
├── include/          # Headers (.h)
│   ├── game.h
│   ├── menu.h
│   ├── player.h
│   ├── level.h
│   ├── obstacles.h
│   └── utils.h
├── assets/           # Recursos (sprites, sons, etc) - CRIAR CONFORME NECESSÁRIO
│   ├── sprites/
│   ├── backgrounds/
│   └── sounds/
├── Makefile
└── README.md
```

## Estado Atual (Boilerplate)

Este é um boilerplate funcional que implementa:
- ✅ Estrutura básica do jogo
- ✅ Sistema de estados (menu, jogo, game over)
- ✅ Sistema de física básico (gravidade, movimento)
- ✅ Sistema de colisão
- ✅ Rolling background (câmera que segue jogador)
- ✅ Sistema de obstáculos
- ✅ Sistema de vida do jogador

## Próximos Passos

Para completar os requisitos mínimos, você deve:

1. **Adicionar Sprites**: Substituir retângulos coloridos por sprites reais
   - Carregar imagens usando `al_load_bitmap()`
   - Implementar em `player.c`, `obstacles.c` e `level.c`

2. **Implementar Ação de Interação**: Adicionar mecânica especial
   - Exemplo: Balanço em cipó (funcionalidade extra [1])
   - Implementar em `player.c` e `player_handle_input()`

3. **Adicionar Background Rolante**: Implementar paralaxe
   - Modificar `level_render()` em `level.c`
   - Usar `camera_x` para movimento do background

4. **Completar Fase**: Adicionar mais obstáculos e ajustar design
   - Modificar `level_init()` em `level.c`
   - Garantir pelo menos 6 elementos de perigo

## Funcionalidades Extras (Opcional)

Para implementar funcionalidades extras, consulte os comentários TODO no código:
- [1] Mecânica de Balanço em Cipó (10 pts)
- [2] Segundo tipo de obstáculo dinâmico (15 pts)
- [3] Botão de pausa (5 pts)
- [4] Função de rastejar (10 pts)
- [5] Segunda fase (20 pts)
- [6] Sistema de salvar/carregar (20 pts)
- [7] Sistema de Stamina (10 pts)
- [8] Remapeamento de teclas (10 pts)
- [9] Dificuldade ajustável (5 pts)
- [10] Trilha sonora (7 pts)
- [11] Item que aumenta vida (5 pts)
- [12] Item de pulo duplo (5 pts)

## Notas

- O código está comentado com TODOs indicando onde implementar cada funcionalidade
- Use `GROUND_LEVEL` em `player.c` como referência de chão (temporário)
- Para testes, os obstáculos aparecem como retângulos coloridos
- O sistema de colisão usa AABB (Axis-Aligned Bounding Box)

