#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro.h>
#include <stdbool.h>

typedef enum {
    PLAYER_IDLE,
    PLAYER_WALKING,
    PLAYER_JUMPING
} PlayerState;

typedef struct {
    float x, y;
    float vx, vy;
    float width, height;
    float sprite_width;
    float sprite_height;
    float sprite_offset_x;
    float sprite_offset_y;
    int health;
    int max_health;
    PlayerState state;
    bool on_ground;
    bool facing_right;
    
    ALLEGRO_BITMAP *sprite_idle;
    ALLEGRO_BITMAP *sprite_walk[10];
    ALLEGRO_BITMAP *sprite_jump;
    ALLEGRO_BITMAP *sprite_fall;
    int walk_frame;
    int walk_frame_counter;
    int jump_count;             // Contador de pulos
    int max_jumps;              // Máximo de pulos permitidos (2 para pulo duplo)
    bool can_jump;              // Flag para controle de input do pulo (evitar spam)
} Player;

Player* player_init(float x, float y);
void player_cleanup(Player *player);
void player_update(Player *player);
void player_render(Player *player, float camera_x);
void player_handle_input(Player *player, ALLEGRO_KEYBOARD_STATE *key_state);
void player_take_damage(Player *player, int damage);
bool player_is_alive(Player *player);

void player_move_left(Player *player);
void player_move_right(Player *player);
void player_jump(Player *player);
void player_crouch(Player *player);

#endif

