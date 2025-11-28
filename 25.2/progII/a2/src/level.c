#include "../include/level.h"
#include "../include/game.h"
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>

#define GROUND_LEVEL 330.0f

// Inicializa a fase
Level* level_init(void) {
    Level *level = (Level*)malloc(sizeof(Level));
    if (!level) return NULL;
    
    level->camera_x = 0;
    level->level_width = 3000;
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
    
    // Adiciona obstáculos de exemplo na fase
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
}

// Renderiza a fase
void level_render(Level *level, float camera_x) {
    // Desenha background
    if (level->background) {
        // Desenha o background considerando a posição da câmera
        
        float bg_width = al_get_bitmap_width(level->background);
        float bg_x = -camera_x;
        
        // Desenha o background
        al_draw_bitmap(level->background, bg_x, 0, 0);
    } else {
        // Background placeholder
        al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgb(135, 206, 235));
        al_draw_filled_rectangle(0, GROUND_LEVEL, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgb(139, 69, 19));
    }
    
    // Renderiza obstáculos
    obstacles_render(level->obstacles, camera_x);
}

// Verifica colisões entre jogador e obstáculos
void level_check_collisions(Level *level, Player *player) {
    Obstacle *current = level->obstacles->head;
    
    while (current != NULL) {
        if (current->active && 
            obstacle_check_collision(current, player->x, player->y, player->width, player->height)) {
            // Jogador colidiu com obstáculo
            player_take_damage(player, current->damage);
        }
        current = current->next;
    }
}

// Atualiza a posição da câmera
void level_update_camera(Level *level, Player *player) {
    // Câmera segue o jogador
    float center = SCREEN_WIDTH / 2;
    level->camera_x = player->x - center;
    
    // Limita a câmera aos limites da fase
    if (level->camera_x < 0) {
        level->camera_x = 0;
    }
    if (level->camera_x > level->level_width - SCREEN_WIDTH) {
        level->camera_x = level->level_width - SCREEN_WIDTH;
    }
}

