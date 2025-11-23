#include "../include/obstacles.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <allegro5/allegro_primitives.h>

// Debug: mostrar hitbox dos obstáculos
#define SHOW_OBSTACLE_HITBOX true

// Inicializa lista de obstáculos
ObstacleList* obstacles_list_init(void) {
    ObstacleList *list = (ObstacleList*)malloc(sizeof(ObstacleList));
    if (!list) return NULL;
    
    list->head = NULL;
    list->count = 0;
    
    return list;
}

// Limpa lista de obstáculos
void obstacles_list_cleanup(ObstacleList *list) {
    if (!list) return;
    
    Obstacle *current = list->head;
    while (current != NULL) {
        Obstacle *next = current->next;
        // TODO: Destruir sprites aqui usando al_destroy_bitmap()
        free(current);
        current = next;
    }
    
    free(list);
}

// Adiciona um obstáculo à lista
void obstacle_add(ObstacleList *list, float x, float y, float width, float height, 
                  ObstacleType type, int damage) {
    if (!list) return;
    
    Obstacle *obstacle = (Obstacle*)malloc(sizeof(Obstacle));
    if (!obstacle) return;
    
    obstacle->x = x;
    obstacle->y = y;
    obstacle->width = width;
    obstacle->height = height;
    obstacle->damage = damage;
    obstacle->type = type;
    obstacle->active = true;
    
    // Define velocidade para obstáculos móveis
    switch (type) {
        case OBSTACLE_MOVING:
            obstacle->vx = 2.0f;  // Move horizontalmente
            obstacle->vy = 0;
            break;
        case OBSTACLE_PLATFORM:
            obstacle->vx = 0;
            obstacle->vy = 1.5f;  // Move verticalmente
            break;
        default:
            obstacle->vx = 0;
            obstacle->vy = 0;
    }
    
    // TODO: Carregar sprite apropriado baseado no tipo
    
    // Insere no início da lista
    obstacle->next = list->head;
    list->head = obstacle;
    list->count++;
}

// Atualiza todos os obstáculos
void obstacles_update(ObstacleList *list) {
    if (!list) return;
    
    Obstacle *current = list->head;
    
    while (current != NULL) {
        if (current->active) {
            // Atualiza posição de obstáculos móveis
            switch (current->type) {
                case OBSTACLE_MOVING:
                    current->x += current->vx;
                    // Inverte direção ao atingir limites
                    if (current->x < 0 || current->x > 2800) {
                        current->vx = -current->vx;
                    }
                    break;
                    
                case OBSTACLE_PLATFORM:
                    current->y += current->vy;
                    // Inverte direção vertical
                    if (current->y < 200 || current->y > 450) {
                        current->vy = -current->vy;
                    }
                    break;
                    
                case OBSTACLE_STATIC:
                default:
                    // Obstáculos estáticos não se movem
                    break;
            }
            
            // TODO: Funcionalidade extra [2]: Implementar segundo tipo de obstáculo dinâmico
            // Exemplo: plataformas que caem/desmoronam quando o jogador pisa
        }
        
        current = current->next;
    }
}

// Renderiza todos os obstáculos
void obstacles_render(ObstacleList *list, float camera_x) {
    if (!list) return;
    
    Obstacle *current = list->head;
    
    while (current != NULL) {
        if (current->active) {
            // TODO: Renderizar sprite apropriado para cada obstáculo
            // Por enquanto, desenha retângulos coloridos baseados no tipo
            
            ALLEGRO_COLOR color;
            switch (current->type) {
                case OBSTACLE_STATIC:
                    color = al_map_rgb(255, 0, 0);  // Vermelho para estáticos
                    break;
                case OBSTACLE_MOVING:
                    color = al_map_rgb(255, 100, 0);  // Laranja para móveis
                    break;
                case OBSTACLE_PLATFORM:
                    color = al_map_rgb(100, 100, 100);  // Cinza para plataformas
                    break;
                default:
                    color = al_map_rgb(255, 255, 255);
            }
            
            // Desenha considerando a posição da câmera
            al_draw_filled_rectangle(current->x - camera_x, current->y, 
                                    current->x - camera_x + current->width, 
                                    current->y + current->height, 
                                    color);
            
            // Debug: desenha hitbox
            if (SHOW_OBSTACLE_HITBOX) {
                al_draw_rectangle(current->x - camera_x, current->y,
                                 current->x - camera_x + current->width,
                                 current->y + current->height,
                                 al_map_rgb(255, 255, 0), 2.0f);
            }
        }
        
        current = current->next;
    }
}

// Verifica colisão entre obstáculo e retângulo (jogador)
bool obstacle_check_collision(Obstacle *obstacle, float x, float y, float width, float height) {
    if (!obstacle || !obstacle->active) return false;
    
    return check_collision_aabb(obstacle->x, obstacle->y, obstacle->width, obstacle->height,
                               x, y, width, height);
}

