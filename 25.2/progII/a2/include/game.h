#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>

// Constantes do jogo
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60

// Estados do jogo
typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_GAME_OVER,
    STATE_VICTORY,
    STATE_EXIT
} GameState;

// Estrutura principal do jogo
typedef struct {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *font;
    GameState state;
    bool running;
    bool redraw;
} Game;

// Funções principais do jogo
Game* game_init(void);
void game_run(Game *game);
void game_cleanup(Game *game);
bool game_handle_events(Game *game, ALLEGRO_EVENT *event);
void game_update(Game *game);
void game_render(Game *game);

#endif

