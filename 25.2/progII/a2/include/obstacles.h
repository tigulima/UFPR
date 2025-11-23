#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <allegro5/allegro.h>
#include <stdbool.h>

// Tipos de obstáculos/perigos
typedef enum {
    OBSTACLE_STATIC,    // Obstáculo estático (ex: buraco, espinho)
    OBSTACLE_MOVING,    // Obstáculo em movimento (ex: tronco rolando, animal)
    OBSTACLE_PLATFORM   // Plataforma móvel
} ObstacleType;

// Estrutura de um obstáculo
typedef struct Obstacle {
    float x, y;              // Posição
    float width, height;     // Dimensões
    float vx, vy;            // Velocidade (para obstáculos móveis)
    int damage;              // Dano causado ao jogador
    ObstacleType type;       // Tipo do obstáculo
    bool active;             // Obstáculo está ativo?
    // TODO: Adicionar ALLEGRO_BITMAP* sprite para cada obstáculo
    struct Obstacle *next;   // Próximo obstáculo na lista
} Obstacle;

// Lista de obstáculos
typedef struct {
    Obstacle *head;
    int count;
} ObstacleList;

// Funções de gerenciamento de obstáculos
ObstacleList* obstacles_list_init(void);
void obstacles_list_cleanup(ObstacleList *list);
void obstacle_add(ObstacleList *list, float x, float y, float width, float height, 
                  ObstacleType type, int damage);
void obstacles_update(ObstacleList *list);
void obstacles_render(ObstacleList *list, float camera_x);
bool obstacle_check_collision(Obstacle *obstacle, float x, float y, float width, float height);

#endif

