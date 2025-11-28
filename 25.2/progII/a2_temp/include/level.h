#ifndef LEVEL_H
#define LEVEL_H

#include "player.h"
#include "obstacles.h"
#include <allegro5/allegro.h>

// Estrutura da fase
typedef struct {
    float camera_x;          // Posição da câmera para rolling background
    float level_width;       // Largura total da fase
    float level_height;      // Altura da fase
    ALLEGRO_BITMAP *background; // Background da fase
    ObstacleList *obstacles; // Lista de obstáculos
    bool completed;          // Fase completada?
    // TODO: Adicionar mais elementos conforme necessário (plataformas, itens coletáveis, etc)
} Level;

// Funções da fase
Level* level_init(void);
void level_cleanup(Level *level);
void level_update(Level *level, Player *player);
void level_render(Level *level, float camera_x);
void level_check_collisions(Level *level, Player *player);
void level_update_camera(Level *level, Player *player);

#endif

