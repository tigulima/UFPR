#include "../include/level.h"
#include "../include/game.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>

#define GROUND_LEVEL 330.0f

// Inicializa a fase
Level* level_init(void) {
    Level *level = (Level*)malloc(sizeof(Level));
    if (!level) return NULL;
    
    level->camera_x = 0;
    level->level_width = 3000;  // Fase com 3000 pixels de largura
    level->level_height = SCREEN_HEIGHT;
    level->background = NULL;
    level->completed = false;
    
    // Carrega background
    level->background = al_load_bitmap("assets/backgrounds/level1.png");
    if (!level->background) {
        fprintf(stderr, "AVISO: Falha ao carregar background level1.png\n");
    }
    
    // Inicializa lista de obstáculos
    level->obstacles = obstacles_list_init();
    
    // Adiciona obstáculos de exemplo na fase (posições ajustadas para GROUND_LEVEL=520)
    obstacle_add(level->obstacles, 300, 330, 40, 20, OBSTACLE_STATIC, 10);    // Espinho estático
    obstacle_add(level->obstacles, 600, 330, 40, 20, OBSTACLE_MOVING, 15);    // Obstáculo móvel
    obstacle_add(level->obstacles, 900, 330, 40, 20, OBSTACLE_STATIC, 10);    // Buraco/armadilha
    obstacle_add(level->obstacles, 1200, 330, 40, 20, OBSTACLE_MOVING, 20);   // Animal em movimento
    obstacle_add(level->obstacles, 1500, 330, 40, 20, OBSTACLE_STATIC, 10);   // Espinho
    obstacle_add(level->obstacles, 2100, 330, 40, 20, OBSTACLE_MOVING, 15);   // Tronco rolando
    
    return level;
}

// Limpa recursos da fase
void level_cleanup(Level *level) {
    if (!level) return;
    
    if (level->background) {
        al_destroy_bitmap(level->background);
    }
    
    if (level->obstacles) {
        obstacles_list_cleanup(level->obstacles);
    }
    
    free(level);
}

// Atualiza a fase
void level_update(Level *level, Player *player) {
    // Limita o jogador aos limites da fase
    if (player->x < 0) player->x = 0;
    if (player->x + player->width > level->level_width) {
        player->x = level->level_width - player->width;
    }

    // Atualiza obstáculos
    obstacles_update(level->obstacles);
    
    // Verifica se o jogador chegou ao final da fase
    if (player->x >= level->level_width - 200) {
        level->completed = true;
    }
    
    // TODO: Atualizar outros elementos da fase (plataformas, itens coletáveis, etc)
}

// Renderiza a fase
void level_render(Level *level, float camera_x) {
    // Desenha background
    if (level->background) {
        // Desenha o background considerando a posição da câmera
        // Para efeito de paralaxe simples, podemos mover o background mais devagar que a câmera
        // mas aqui vamos desenhar fixo em relação ao mundo (rolling background padrão)
        
        // Se o background for menor que a fase, pode ser necessário repetir ou esticar
        // Vamos assumir que o background cobre toda a fase ou desenhar repetido
        
        float bg_width = al_get_bitmap_width(level->background);
        float bg_x = -camera_x;
        
        // Desenha o background
        // Se quiser paralaxe: float bg_x = -(camera_x * 0.5); // Move a 50% da velocidade
        
        al_draw_bitmap(level->background, bg_x, 0, 0);
        
        // Se o background for menor que a tela/fase e precisarmos repetir:
        if (bg_width < level->level_width) {
             while (bg_x + bg_width < SCREEN_WIDTH) {
                 bg_x += bg_width;
                 al_draw_bitmap(level->background, bg_x, 0, 0);
             }
        }
    } else {
        // Background placeholder (céu azul e chão)
        al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgb(135, 206, 235));
        al_draw_filled_rectangle(0, GROUND_LEVEL, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgb(139, 69, 19));
    }
    
    // Renderiza obstáculos
    obstacles_render(level->obstacles, camera_x);
    
    // TODO: Renderizar outros elementos (plataformas, itens coletáveis, etc)
}

// Verifica colisões entre jogador e obstáculos
void level_check_collisions(Level *level, Player *player) {
    Obstacle *current = level->obstacles->head;
    
    while (current != NULL) {
        if (current->active && 
            obstacle_check_collision(current, player->x, player->y, 
                                    player->width, player->height)) {
            // Jogador colidiu com obstáculo
            player_take_damage(player, current->damage);
            
            // TODO: Adicionar invulnerabilidade temporária para evitar dano múltiplo
            // TODO: Adicionar knockback ao jogador
        }
        current = current->next;
    }
    
    // TODO: Verificar colisões com itens coletáveis
    // Funcionalidade extra [11]: Item que aumenta vida
    // Funcionalidade extra [12]: Item que desbloqueia pulo duplo
}

// Atualiza a posição da câmera (rolling background)
void level_update_camera(Level *level, Player *player) {
    // Câmera segue o jogador horizontalmente
    float center = SCREEN_WIDTH / 2;
    level->camera_x = player->x - center;
    
    // Limita a câmera aos limites da fase
    if (level->camera_x < 0) {
        level->camera_x = 0;
    }
    if (level->camera_x > level->level_width - SCREEN_WIDTH) {
        level->camera_x = level->level_width - SCREEN_WIDTH;
    }
    
    // TODO: Implementar rolling background usando camera_x
    // O background deve se mover em paralaxe para criar profundidade
}

