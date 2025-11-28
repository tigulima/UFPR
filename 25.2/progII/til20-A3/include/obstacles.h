#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <allegro5/allegro.h>
#include <stdbool.h>

typedef enum {
    OBSTACLE_STATIC,
    OBSTACLE_MOVING,
    OBSTACLE_PLATFORM
} ObstacleType;

typedef struct Obstacle {
    float x, y;
    float width, height;
    float vx, vy;
    int damage;
    ObstacleType type;
    bool active;
    
    ALLEGRO_BITMAP *sprites_moving[8];
    ALLEGRO_BITMAP *sprites_static[8];
    int frame_current;
    int frame_counter;
    
    struct Obstacle *next;
} Obstacle;

typedef struct {
    Obstacle *head;
    int count;
} ObstacleList;

ObstacleList* obstacles_list_init(void);
void obstacles_list_cleanup(ObstacleList *list);
void obstacle_add(ObstacleList *list, float x, float y, float width, float height, ObstacleType type, int damage);
void obstacles_update(ObstacleList *list);
void obstacles_render(ObstacleList *list, float camera_x);
bool obstacle_check_collision(Obstacle *obstacle, float x, float y, float width, float height);

#endif

