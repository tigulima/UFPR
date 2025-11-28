#ifndef LEVEL_H
#define LEVEL_H

#include "player.h"
#include "obstacles.h"
#include <allegro5/allegro.h>

typedef struct {
    float camera_x;
    float level_width;  
    float level_height;
    ALLEGRO_BITMAP *background;
    ObstacleList *obstacles;
    bool completed;
} Level;

Level* level_init(void);
void level_cleanup(Level *level);
void level_update(Level *level, Player *player);
void level_render(Level *level, float camera_x);
void level_check_collisions(Level *level, Player *player);
void level_update_camera(Level *level, Player *player);

#endif

