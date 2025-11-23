#ifndef MENU_H
#define MENU_H

#include "game.h"

// Opções do menu
typedef enum {
    MENU_RESUME,
    MENU_START,
    MENU_EXIT,
    MENU_OPTION_COUNT
} MenuOption;

// Estrutura do menu
typedef struct {
    MenuOption selected;
    ALLEGRO_FONT *font;
    bool show_resume; // Mostra opção "Resume" apenas quando em pausa
} Menu;

// Funções do menu
Menu* menu_init(ALLEGRO_FONT *font);
void menu_cleanup(Menu *menu);
void menu_handle_input(Menu *menu, ALLEGRO_EVENT *event, Game *game);
void menu_render(Menu *menu);

// Tela de fim de jogo
void game_over_screen_render(ALLEGRO_FONT *font, bool victory);

#endif

