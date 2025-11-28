# Arquitetura do Projeto

## Visão Geral

O projeto está organizado em módulos independentes seguindo o padrão MVC adaptado para jogos.

## Módulos Principais

### 1. **main.c**
- Ponto de entrada do programa
- Inicializa e executa o loop principal do jogo

### 2. **game.c/h**
- Controlador principal do jogo
- Gerencia estados (Menu, Jogando, Game Over, Vitória)
- Coordena interações entre todos os módulos
- Implementa o game loop (eventos → update → render)

### 3. **menu.c/h**
- Interface do menu inicial
- Tela de game over/vitória
- Navegação entre opções

### 4. **player.c/h**
- Lógica do personagem
- Física (movimento, gravidade, pulo)
- Estados (idle, walking, jumping, crouching, swinging)
- Sistema de vida
- **TODO**: Adicionar sprites e animações

### 5. **level.c/h**
- Gerenciamento da fase
- Rolling background (câmera segue jogador)
- Lista de obstáculos
- Detecção de colisões
- Condições de vitória
- **TODO**: Implementar paralaxe no background

### 6. **obstacles.c/h**
- Sistema de obstáculos/perigos
- Tipos: estático, móvel, plataforma
- Lista ligada de obstáculos
- Lógica de movimento dos obstáculos dinâmicos
- **TODO**: Adicionar sprites e mais tipos

### 7. **utils.c/h**
- Funções auxiliares
- Inicialização do Allegro e addons
- Detecção de colisão AABB
- Tratamento de erros

## Fluxo de Execução

```
main()
  ↓
game_init() → Inicializa Allegro, display, timer, eventos
  ↓
game_run() → Loop principal
  ↓
┌─────────────────────────┐
│  LOOP PRINCIPAL         │
│  ┌──────────────────┐   │
│  │ Handle Events    │   │ ← Teclado, timer, display
│  └──────────────────┘   │
│           ↓             │
│  ┌──────────────────┐   │
│  │ Update Logic     │   │ ← Física, colisões, IA
│  └──────────────────┘   │
│           ↓             │
│  ┌──────────────────┐   │
│  │ Render           │   │ ← Desenha tudo na tela
│  └──────────────────┘   │
└─────────────────────────┘
  ↓
game_cleanup() → Libera recursos
```

## Estados do Jogo

```
┌────────┐  Start  ┌─────────┐
│  MENU  │────────→│ PLAYING │
└────────┘         └─────────┘
    ↑                  │
    │                  ├─→ Player morreu ──→ GAME OVER
    │                  │
    └──────────────────┴─→ Fase completa ──→ VICTORY
```

## Sistema de Colisão

- **AABB** (Axis-Aligned Bounding Box): Colisão entre retângulos alinhados aos eixos
- Usado em: player × obstáculos, player × itens coletáveis

## Modificações Necessárias

### Para Requisitos Mínimos:
1. **Sprites**: Adicionar em `assets/sprites/` e carregar em cada módulo
2. **Background**: Adicionar em `assets/backgrounds/` e implementar paralaxe
3. **Ação de Interação**: Implementar mecânica especial (ex: balanço)

### Para Funcionalidades Extras:
Consulte comentários `TODO` no código, especialmente:
- `game.c`: Pausa [3], segunda fase [5]
- `player.c`: Rastejar [4], pulo duplo [12], stamina [7]
- `obstacles.c`: Novo tipo de obstáculo [2]
- `utils.c`: Sistema de áudio [10]
- `level.c`: Sistema de save/load [6], itens coletáveis [11][12]

## Convenções de Código

- **Nomenclatura**: `modulo_funcao()` (snake_case)
- **Estruturas**: `typedef struct { ... } NomeStruct;`
- **Ponteiros**: Sempre verificar NULL antes de usar
- **Memória**: Toda alocação deve ter free correspondente
- **Headers**: Include guards em todos os .h

