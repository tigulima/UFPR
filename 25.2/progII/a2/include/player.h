#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro.h>
#include <stdbool.h>

// Estados do jogador
typedef enum {
    PLAYER_IDLE,      // Em pé
    PLAYER_WALKING,   // Andando
    PLAYER_JUMPING,   // Pulando
    PLAYER_CROUCHING, // Abaixado
    PLAYER_SWINGING   // Balançando (ação de interação/desvio)
} PlayerState;

// Estrutura do jogador
typedef struct {
    float x, y;              // Posição (da hitbox)
    float vx, vy;            // Velocidade
    float width, height;     // Dimensões da hitbox (para colisão)
    float sprite_width;      // Largura do sprite (visual)
    float sprite_height;     // Altura do sprite (visual)
    float sprite_offset_x;   // Offset X para centralizar sprite
    float sprite_offset_y;   // Offset Y para alinhar sprite
    int health;              // Pontos de vida
    int max_health;          // Vida máxima
    PlayerState state;       // Estado atual
    bool on_ground;          // Está no chão?
    bool facing_right;       // Direção que está olhando
    
    // Sprites do jogador
    ALLEGRO_BITMAP *sprite_idle;           // Sprite em pé
    ALLEGRO_BITMAP *sprite_walk[10];       // Sprites de caminhada (0-9)
    ALLEGRO_BITMAP *sprite_jump;           // Sprite pulando (subindo)
    ALLEGRO_BITMAP *sprite_fall;           // Sprite caindo
    int walk_frame;                        // Frame atual da animação de caminhada
    int walk_frame_counter;                // Contador para controlar velocidade da animação
    // TODO: Adicionar outros sprites (crouch, swing)
} Player;

// Funções do jogador
Player* player_init(float x, float y);
void player_cleanup(Player *player);
void player_update(Player *player);
void player_render(Player *player);
void player_handle_input(Player *player, ALLEGRO_KEYBOARD_STATE *key_state);
void player_take_damage(Player *player, int damage);
bool player_is_alive(Player *player);

// Ações do jogador
void player_move_left(Player *player);
void player_move_right(Player *player);
void player_jump(Player *player);
void player_crouch(Player *player);

#endif

