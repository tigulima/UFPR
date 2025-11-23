
# Plataforma de Sobrevivência

**Avaliação #03**
**Programação 02**
**Universidade Federal do Paraná**

## INTRODUÇÃO

Jogos do tipo plataforma são um subgênero dos jogos de ação, caracterizados por uma jogabilidade que exige precisão, timing e reflexos para atravessar terrenos perigosos. O jogador deve se movimentar e saltar entre plataformas e obstáculos.

O foco deste trabalho é a navegação, desafios de colisão e plataforma (e não o combate), com o personagem buscando sobreviver e progredir pelo cenário.

Um bom exemplo de jogo com foco em navegação e desvio é Pitfall, um clássico lançado para o console Atari em 1982. Nele, o jogador controla Pitfall Harry, um aventureiro que deve correr, pular e se balançar em cipós para atravessar uma selva cheia de buracos e animais perigosos. O desafio reside em superar os obstáculos no timing certo.

## O TRABALHO

O objetivo final é DESENVOLVER UM JOGO DE PLATAFORMA COM FOCO EM NAVEGAÇÃO, similar ao Pitfall em termos de jogabilidade e mecânicas de movimentação. O aspecto criativo e temático (cenário, personagem, obstáculos) é livre para implementação de ideias diferentes.

Porém, para referência, vamos estabelecer apenas um conjunto de requisitos mínimos para o jogo, sendo que a implementação destes equivale a 80% da nota total do trabalho. Funcionalidades extras só serão avaliadas dada a implementação dos requisitos mínimos. O restante da nota pode ser completada através da implementação de funcionalidades extras.

A nota do trabalho será, no máximo, 100 pontos (que valem 30 pontos na média da disciplina). Porém, você pode implementar funcionalidades extras que somem até 110 pontos. O programa deve ser bem modularizado, com uma estrutura lógica de diretórios, com uma separação organizada de funções e arquivos.

## REQUISITOS MÍNIMOS

**Em relação às características gerais do jogo, deve ser considerado o seguinte:**

* Implementação de um jogo singleplayer;
* Implementação de um menu inicial, permitindo iniciar ou sair do jogo;
* Implementação de uma tela de fim de jogo, indicando se o final foi alcançado com sucesso ou não (game over).

**Em relação ao personagem principal, deve existir, pelo menos:**

* Sprites 2D (imagem) para as seguintes ações:
* Em pé;
* Abaixado;
* Pulando;
* Andando em pé;
* Em ação de interação/desvio (ex: balançando ou escalando)
* Mobilidade geral: Andar, pular, e a ação de interação/desvio.
* Sistema de pontos de vida que reduz progressivamente conforme colisão recebida por perigos/armadilhas.

**Em relação aos cenários, espera-se, no mínimo:**

* Um cenário com background de imagem;
* Rolling background (o cenário muda conforme o jogador se movimenta).

**Em relação aos obstáculos (perigos), espera-se, no mínimo:**

* Pelo menos 6 elementos de perigo e armadilhas espalhados pela fase, que o jogador deve desviar/saltar. Estes devem incluir pelo menos um tipo de perigo em movimento (ex: plataformas móveis, troncos rolando, animais que causam dano por contato).
* Todos os perigos/obstáculos devem ter suas respectivas sprites e movimento (se aplicável).
* Ataque (dano) é causado por contato/colisão, não por projéteis ou combate.

**Em relação às fases, espera-se, no mínimo:**

* Pelo menos uma fase completa;
* Pelo menos 6 elementos de perigo/armadilhas espalhados pela fase.

## FUNCIONALIDADES EXTRAS

| Item | Pontos | Descrição |
| :--- | :--- | :--- |
| [1] | 10 pts | Implementar, pelo menos, a Mecânica de Balanço em Cipó/Cordas com animações (sprites) dedicadas, exigindo timing para o salto. |
| [2] | 15 pts | Implementar, pelo menos, um segundo tipo de obstáculo dinâmico inédito, diferente dos requisitos mínimos (ex: plataformas que caem ou desmoronam). |
| [3] | 5 pts | Implementar um botão de pausa para a fase. |
| [4] | 10 pts | Implementar a função de "rastejar" (movimentar-se abaixado) para passar por áreas baixas. |
| [5] | 20 pts | Implementar uma segunda fase, com background diferente e um conjunto inédito de obstáculos. |
| [6] | 20 pts | Implementar um mecanismo de salvar e carregar o progresso do jogo. |
| [7] | 10 pts | Implementar um sistema de Stamina/Fôlego (o jogador "cansa" ao correr ou ao se balançar e deve se recuperar). |
| [8] | 10 pts | Remapeamento livre de teclas de ação no menu de opções. |
| [9] | 5 pts | Dificuldade ajustável no menu de opções (Fácil, Médio e Díficil), ajustando a velocidade dos obstáculos/perigos. |
| [10] | 7 pts | Trilha sonora na tela principal e na fase, com ajustador de volume no menu de opções. |
| [11] | 5 pts | Item coletável que aumenta a barra de vida. |
| [12] | 5 pts | Item coletável que desbloqueia a habilidade do jogador fazer pulo duplo. |

## REQUISITOS TÉCNICOS E ENTREGA

Considere as seguintes informações para executar e entregar o trabalho:

* Você deve utilizar a linguagem C para a implementação do trabalho; E a biblioteca Allegro para a implementação da interface gráfica;
* Você deve preparar um makefile (pelo menos, com operações make e make clean) para a compilação do seu programa;
* Não esqueça de tratar possíveis erros.