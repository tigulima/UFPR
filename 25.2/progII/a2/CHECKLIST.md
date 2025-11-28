# Checklist de Implementação

## ✅ Já Implementado (Boilerplate)

### Estrutura Geral
- ✅ Menu inicial com opções de Iniciar e Sair
- ✅ Sistema de estados do jogo (Menu, Playing, Game Over, Victory)
- ✅ Loop principal do jogo (eventos → update → render)
- ✅ Tela de fim de jogo (vitória e derrota)

### Personagem
- ✅ Estrutura do jogador com posição, velocidade e estado
- ✅ Sistema de vida (health/max_health)
- ✅ Física básica (gravidade, movimento horizontal)
- ✅ Estados: idle, walking, jumping, crouching, swinging
- ✅ Controles: andar (setas/WASD), pular (espaço), agachar (S/↓)
- ✅ Função para receber dano
- ✅ Verificação se está vivo

### Cenário
- ✅ Sistema de câmera (rolling background)
- ✅ Estrutura para background da fase
- ✅ Largura da fase configurável (3000px por padrão)

### Obstáculos
- ✅ Sistema de lista ligada de obstáculos
- ✅ 3 tipos: estático, móvel, plataforma
- ✅ Pelo menos 7 obstáculos criados na fase
- ✅ Movimento automático para obstáculos dinâmicos
- ✅ Sistema de dano por colisão
- ✅ Detecção de colisão AABB

### Sistema
- ✅ Makefile com make, make clean, make run
- ✅ Estrutura modular organizada
- ✅ Tratamento de erros
- ✅ HUD mostrando vida do jogador

## ⚠️ A Implementar (Requisitos Mínimos - 80 pontos)

### Sprites do Personagem (Crítico)
- ✅ Sprite em pé (idle) - IMPLEMENTADO
- ✅ Sprites andando (walk animation)
- ❌ Sprite pulando (jump)
- ❌ Sprite abaixado (crouch)
- ❌ Sprite de interação/desvio (swing/climb)
- **Onde**: `player.c` → `player_init()` e `player_render()`

### Sprites dos Obstáculos (Crítico)
- ❌ Sprites para obstáculos estáticos
- ❌ Sprites para obstáculos móveis
- ❌ Sprites para plataformas
- **Onde**: `obstacles.c` → `obstacle_add()` e `obstacles_render()`

### Background (Crítico)
- ❌ Imagem de background da fase
- ❌ Implementar paralaxe (background rola em velocidade diferente)
- **Onde**: `level.c` → `level_init()` e `level_render()`

### Ação de Interação/Desvio (Crítico)
- ❌ Implementar mecânica especial (ex: balanço em cipó, escalada)
- ❌ Sprites e animação da ação
- ❌ Lógica de ativação (tecla específica)
- **Onde**: `player.c` → `player_handle_input()` e `player_update()`

### Ajustes Finais
- ❌ Testar e ajustar física (velocidades, gravidade, altura do pulo)
- ❌ Ajustar posicionamento dos obstáculos na fase
- ❌ Adicionar invulnerabilidade temporária após dano
- ❌ Melhorar feedback visual de dano

## 🎁 Funcionalidades Extras (até 30 pontos)

| ID | Pts | Status | Descrição |
|----|-----|--------|-----------|
| [1] | 10 | ❌ | Mecânica de Balanço em Cipó com timing |
| [2] | 15 | ❌ | Segundo tipo de obstáculo dinâmico (plataformas que caem) |
| [3] | 5 | ❌ | Botão de pausa |
| [4] | 10 | ❌ | Rastejar (movimentar-se abaixado) |
| [5] | 20 | ❌ | Segunda fase com background diferente |
| [6] | 20 | ❌ | Sistema de salvar/carregar progresso |
| [7] | 10 | ❌ | Sistema de Stamina/Fôlego |
| [8] | 10 | ❌ | Remapeamento de teclas |
| [9] | 5 | ❌ | Dificuldade ajustável |
| [10] | 7 | ❌ | Trilha sonora e ajuste de volume |
| [11] | 5 | ❌ | Item coletável que aumenta vida |
| [12] | 5 | ❌ | Item de pulo duplo |

**Total possível**: 122 pontos (100 pontos base + 22 extras)

## 🎯 Prioridades

### Alta Prioridade (Requisitos Mínimos)
1. **Adicionar sprites** - Sem sprites, o jogo não atende aos requisitos visuais
2. **Implementar ação de interação** - Requisito explícito (balanço, escalada, etc)
3. **Background com imagem** - Requisito explícito
4. **Testar e ajustar** - Garantir que o jogo seja jogável

### Média Prioridade (Polimento)
5. Melhorar feedback visual
6. Ajustar dificuldade/balanceamento
7. Adicionar efeitos sonoros básicos

### Baixa Prioridade (Extras)
8. Implementar funcionalidades extras conforme tempo disponível

## 📝 Notas de Implementação

### Onde encontrar TODOs no código:
- `player.c`: Linha ~26 (carregar sprites), ~91 (animações), ~160 (interação)
- `obstacles.c`: Linha ~78 (carregar sprites), ~115 (renderizar sprites), ~139 (novo tipo)
- `level.c`: Linha ~22 (carregar background), ~52 (paralaxe)
- `game.c`: Linha ~118 (pausa)
- `utils.c`: Linha ~57 (áudio)

### Recursos Necessários:
- Criar ou baixar sprites (formato PNG recomendado)
- Criar ou baixar background (formato PNG/JPG, tamanho 3000x600 ou maior)
- Opcional: Sons e músicas (formato OGG/WAV)

### Teste Rápido:
```bash
./setup.sh          # Verifica dependências
make                # Compila
./bin/game          # Executa
```

O jogo atualmente renderiza retângulos coloridos no lugar dos sprites - isso é intencional para permitir testes da lógica antes de ter os assets gráficos prontos.

