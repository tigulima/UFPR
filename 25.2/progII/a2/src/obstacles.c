#include "../include/obstacles.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>
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
        
        // Destrói sprites se existirem
        for (int i = 0; i < 8; i++) {
            if (current->sprites_moving[i]) {
                al_destroy_bitmap(current->sprites_moving[i]);
            }
            if (current->sprites_static[i]) {
                al_destroy_bitmap(current->sprites_static[i]);
            }
        }
        
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
    
    // Inicializa variáveis de animação
    obstacle->frame_current = 0;
    obstacle->frame_counter = 0;
    for (int i = 0; i < 8; i++) {
        obstacle->sprites_moving[i] = NULL;
        obstacle->sprites_static[i] = NULL;
    }

    // Define velocidade para obstáculos móveis
    switch (type) {
        case OBSTACLE_MOVING:
            obstacle->vx = 2.0f;  // Move horizontalmente
            obstacle->vy = 0;
            
            // Carrega sprites
            char filename[128];
            for (int i = 0; i < 8; i++) {
                snprintf(filename, sizeof(filename), "assets/sprites/obstacle/moving/obstacle_moving_%d.png", i);
                obstacle->sprites_moving[i] = al_load_bitmap(filename);
                if (!obstacle->sprites_moving[i]) {
                    fprintf(stderr, "AVISO: Falha ao carregar %s\n", filename);
                }
            }
            break;
        case OBSTACLE_STATIC:
            obstacle->vx = 0;
            obstacle->vy = 0;
            
            // Carrega sprites
            char filename_static[128];
            for (int i = 0; i < 8; i++) {
                snprintf(filename_static, sizeof(filename_static), "assets/sprites/obstacle/static/obstacle_static_%d.png", i);
                obstacle->sprites_static[i] = al_load_bitmap(filename_static);
                if (!obstacle->sprites_static[i]) {
                    fprintf(stderr, "AVISO: Falha ao carregar %s\n", filename_static);
                }
            }
            break;
        case OBSTACLE_PLATFORM:
            obstacle->vx = 0;
            obstacle->vy = 1.5f;  // Move verticalmente
            break;
        default:
            obstacle->vx = 0;
            obstacle->vy = 0;
    }
    
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
            // Atualiza animação
            if (current->type == OBSTACLE_MOVING || current->type == OBSTACLE_STATIC) {
                current->frame_counter++;
                if (current->frame_counter >= 5) { // Velocidade da animação
                    current->frame_current = (current->frame_current + 1) % 8;
                    current->frame_counter = 0;
                }
            }

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
            if (current->type == OBSTACLE_MOVING && current->sprites_moving[current->frame_current]) {
                // Renderiza sprite animado móvel
                ALLEGRO_BITMAP *sprite = current->sprites_moving[current->frame_current];
                
                // Se o sprite existir, desenha ele
                // Assume que a hitbox e o sprite tem tamanhos compatíveis ou ajusta o offset
                // Centraliza o sprite na hitbox
                float sprite_w = al_get_bitmap_width(sprite);
                float sprite_h = al_get_bitmap_height(sprite);
                float offset_x = (sprite_w - current->width) / 2.0f;
                float offset_y = (sprite_h - current->height) / 2.0f;
                
                int flags = 0;
                // Se o sprite olha para a direita por padrão:
                // Quando vx > 0 (move p/ direita): deve olhar p/ direita -> SEM FLIP
                // Quando vx < 0 (move p/ esquerda): deve olhar p/ esquerda -> COM FLIP
                if (current->vx < 0) flags = ALLEGRO_FLIP_HORIZONTAL;
                
                al_draw_bitmap(sprite, current->x - camera_x - offset_x, current->y - offset_y, flags);
            } else if (current->type == OBSTACLE_STATIC && current->sprites_static[current->frame_current]) {
                // Renderiza sprite animado estático
                ALLEGRO_BITMAP *sprite = current->sprites_static[current->frame_current];
                
                float sprite_w = al_get_bitmap_width(sprite);
                float sprite_h = al_get_bitmap_height(sprite);
                float offset_x = (sprite_w - current->width) / 2.0f;
                float offset_y = (sprite_h - current->height) / 2.0f;
                
                al_draw_bitmap(sprite, current->x - camera_x - offset_x, current->y - offset_y, 0);
            } else {
                // Fallback para retângulo
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
                
                al_draw_filled_rectangle(current->x - camera_x, current->y, 
                                        current->x - camera_x + current->width, 
                                        current->y + current->height, 
                                        color);
            }
            
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

