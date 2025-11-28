#include "../include/player.h"
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>

#define PLAYER_SPEED 3.0f
#define PLAYER_JUMP_FORCE -8.0f
#define GRAVITY 0.4f
#define GROUND_LEVEL 350.0f

#define SHOW_HITBOX false

// Inicializa o jogador
Player* player_init(float x, float y) {
    Player *player = (Player*)malloc(sizeof(Player));
    if (!player) return NULL;
    
    player->x = x;
    player->y = y;
    player->vx = 0;
    player->vy = 0;
    
    player->width = 12;
    player->height = 24;
    
    player->health = 100;
    player->max_health = 100;
    player->state = PLAYER_IDLE;
    player->on_ground = false;
    player->facing_right = true;
    player->walk_frame = 0;
    player->walk_frame_counter = 0;
    
    player->jump_count = 0;
    player->max_jumps = 2;
    player->can_jump = true;
    
    // Carrega sprite idle
    player->sprite_idle = al_load_bitmap("assets/sprites/player/player_idle.png");
    if (!player->sprite_idle) {
        fprintf(stderr, "AVISO: Falha ao carregar sprite player_idle.png\n");
        // Usa dimensões da hitbox como fallback
        player->sprite_width = player->width;
        player->sprite_height = player->height;
        player->sprite_offset_x = 0;
        player->sprite_offset_y = 0;
    } else {
        // Calcula dimensões do sprite
        player->sprite_width = al_get_bitmap_width(player->sprite_idle);
        player->sprite_height = al_get_bitmap_height(player->sprite_idle);
        
        // Calcula offset para centralizar hitbox no sprite
        player->sprite_offset_x = (player->sprite_width - player->width) / 2.0f;
        player->sprite_offset_y = (player->sprite_height - player->height) / 2.0f;
    }
    
    // Carrega sprites de caminhada
    char walk_filename[64];
    for (int i = 0; i < 10; i++) {
        snprintf(walk_filename, sizeof(walk_filename), "assets/sprites/player/player_walk_%d.png", i);
        player->sprite_walk[i] = al_load_bitmap(walk_filename);
        if (!player->sprite_walk[i]) {
            fprintf(stderr, "AVISO: Falha ao carregar %s\n", walk_filename);
        }
    }
    
    // Carrega sprite de pulo
    player->sprite_jump = al_load_bitmap("assets/sprites/player/player_jump.png");
    if (!player->sprite_jump) {
        fprintf(stderr, "AVISO: Falha ao carregar sprite player_jump.png\n");
    }
    
    // Carrega sprite de queda
    player->sprite_fall = al_load_bitmap("assets/sprites/player/player_fall.png");
    if (!player->sprite_fall) {
        fprintf(stderr, "AVISO: Falha ao carregar sprite player_fall.png\n");
    }
    
    return player;
}

// Limpa recursos do jogador
void player_cleanup(Player *player) {
    if (player) {
        // Destrói sprites
        if (player->sprite_idle) {
            al_destroy_bitmap(player->sprite_idle);
        }
        
        // Destrói sprites de caminhada
        for (int i = 0; i < 10; i++) {
            if (player->sprite_walk[i]) {
                al_destroy_bitmap(player->sprite_walk[i]);
            }
        }
        
        if (player->sprite_jump) {
            al_destroy_bitmap(player->sprite_jump);
        }
        
        if (player->sprite_fall) {
            al_destroy_bitmap(player->sprite_fall);
        }
        
        free(player);
    }
}

// Atualiza o jogador
void player_update(Player *player) {
    // Aplica gravidade
    if (!player->on_ground) {
        player->vy += GRAVITY;
    }
    
    // Atualiza posição
    player->x += player->vx;
    player->y += player->vy;
    
    // Verifica colisão com o chão
    if (player->y + player->height >= GROUND_LEVEL) {
        player->y = GROUND_LEVEL - player->height;
        player->vy = 0;
        player->on_ground = true;
        
        if (player->state == PLAYER_JUMPING) {
            player->state = PLAYER_IDLE;
        }
        
        // Reseta contador de pulos quando toca o chão
        player->jump_count = 0;
    } else {
        player->on_ground = false;
    }
    
    // Limita movimento horizontal na tela
    if (player->x < 0) player->x = 0;
    
    // Atualiza estado baseado em movimento
    if (player->on_ground && player->vx != 0) {
        player->state = PLAYER_WALKING;
        
        // Atualiza animação de caminhada
        player->walk_frame_counter++;
        if (player->walk_frame_counter >= 5) { // Muda frame a cada 5 updates
            player->walk_frame = (player->walk_frame + 1) % 10;
            player->walk_frame_counter = 0;
        }
    }
    
    // Reduz velocidade horizontal
    player->vx *= 0.85f;
    if (player->vx > -0.1f && player->vx < 0.1f) {
        player->vx = 0;
    }
}

// Renderiza o jogador
void player_render(Player *player, float camera_x) {
    // Seleciona sprite baseado no estado
    ALLEGRO_BITMAP *current_sprite = NULL;
    
    switch (player->state) {
        case PLAYER_IDLE:
            current_sprite = player->sprite_idle;
            break;
        case PLAYER_WALKING:
            current_sprite = player->sprite_walk[player->walk_frame];
            if (!current_sprite) current_sprite = player->sprite_idle; // Fallback
            break;
        case PLAYER_JUMPING:
            // Usa sprite diferente se está subindo ou caindo
            if (player->vy < 0) {
                current_sprite = player->sprite_jump; // Subindo
            } else {
                current_sprite = player->sprite_fall; // Caindo
            }
            if (!current_sprite) current_sprite = player->sprite_idle; // Fallback
            break;
    }
    
    // Renderiza sprite se disponível
    if (current_sprite) {
        // Calcula centro da hitbox
        float center_x = (player->x - camera_x) + player->width / 2.0f;
        float center_y = player->y + player->height / 2.0f;
        
        // Posição do sprite centralizado na hitbox
        float sprite_x = center_x - player->sprite_width / 2.0f;
        float sprite_y = center_y - player->sprite_height / 2.0f;
        
        // Se está olhando para a esquerda, espelha o sprite
        if (!player->facing_right) {
            // Com FLIP_HORIZONTAL, o sprite é espelhado mas a posição x,y continua sendo o canto superior esquerdo
            al_draw_bitmap(current_sprite, sprite_x, sprite_y, ALLEGRO_FLIP_HORIZONTAL);
        } else {
            // Normal: x é a borda esquerda
            al_draw_bitmap(current_sprite, sprite_x, sprite_y, 0);
        }
    } else {
        // Fallback: desenha retângulo colorido se sprite não carregou
        ALLEGRO_COLOR color;
        switch (player->state) {
            case PLAYER_IDLE:
                color = al_map_rgb(0, 255, 0);
                break;
            case PLAYER_WALKING:
                color = al_map_rgb(0, 200, 255);
                break;
            case PLAYER_JUMPING:
                color = al_map_rgb(255, 200, 0);
                break;
            default:
                color = al_map_rgb(255, 255, 255);
        }
        
        al_draw_filled_rectangle(player->x - camera_x, player->y, 
                                player->x - camera_x + player->width, 
                                player->y + player->height, 
                                color);
    }
    
    // Debug: desenha hitbox para visualização (se habilitado)
    if (SHOW_HITBOX && current_sprite) {
        al_draw_rectangle(player->x - camera_x, player->y, 
                         player->x - camera_x + player->width, 
                         player->y + player->height, 
                         al_map_rgba(255, 0, 0, 180), 2.0f);
    }
}

// Processa input do jogador
void player_handle_input(Player *player, ALLEGRO_KEYBOARD_STATE *key_state) {
    // Movimento horizontal
    if (al_key_down(key_state, ALLEGRO_KEY_LEFT) || al_key_down(key_state, ALLEGRO_KEY_A)) {
        player_move_left(player);
    }
    if (al_key_down(key_state, ALLEGRO_KEY_RIGHT) || al_key_down(key_state, ALLEGRO_KEY_D)) {
        player_move_right(player);
    }
    
    // Pulo
    bool jump_key_pressed = al_key_down(key_state, ALLEGRO_KEY_SPACE) || al_key_down(key_state, ALLEGRO_KEY_W);
    
    if (jump_key_pressed) {
        if (player->can_jump) {
            player_jump(player);
            player->can_jump = false; // Evita spam, requer que solte a tecla
        }
    } else {
        player->can_jump = true; // Reseta flag quando tecla é solta
    }
}

// Move o jogador para a esquerda
void player_move_left(Player *player) {
    player->vx = -PLAYER_SPEED;
    player->facing_right = false;
}

// Move o jogador para a direita
void player_move_right(Player *player) {
    player->vx = PLAYER_SPEED;
    player->facing_right = true;
}

// Faz o jogador pular
void player_jump(Player *player) {
    if (player->jump_count < player->max_jumps) {
        player->vy = PLAYER_JUMP_FORCE;
        player->state = PLAYER_JUMPING;
        player->on_ground = false;
        player->jump_count++;
    }
}

// Aplica dano ao jogador
void player_take_damage(Player *player, int damage) {
    player->health -= damage;
    if (player->health < 0) {
        player->health = 0;
    }
}

// Verifica se o jogador está vivo
bool player_is_alive(Player *player) {
    return player->health > 0;
}

