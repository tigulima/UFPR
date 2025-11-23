#include "../include/menu.h"
#include "../include/player.h"
#include "../include/level.h"
#include <stdlib.h>

// Variáveis externas (declaradas em game.c)
extern Player *player;
extern Level *level;

// Inicializa o menu
Menu* menu_init(ALLEGRO_FONT *font) {
    Menu *menu = (Menu*)malloc(sizeof(Menu));
    if (!menu) return NULL;
    
    menu->selected = MENU_START;
    menu->font = font;
    menu->show_resume = false;
    
    return menu;
}

// Limpa recursos do menu
void menu_cleanup(Menu *menu) {
    if (menu) {
        free(menu);
    }
}

// Processa input do menu
void menu_handle_input(Menu *menu, ALLEGRO_EVENT *event, Game *game) {
    if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (event->keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                do {
                    menu->selected = (menu->selected == 0) ? MENU_OPTION_COUNT - 1 : menu->selected - 1;
                } while (menu->selected == MENU_RESUME && !menu->show_resume);
                break;
                
            case ALLEGRO_KEY_DOWN:
                do {
                    menu->selected = (menu->selected + 1) % MENU_OPTION_COUNT;
                } while (menu->selected == MENU_RESUME && !menu->show_resume);
                break;
                
            case ALLEGRO_KEY_ENTER:
                if (menu->selected == MENU_RESUME) {
                    // Retorna ao jogo (despause)
                    menu->show_resume = false;
                    game->state = STATE_PLAYING;
                } else if (menu->selected == MENU_START) {
                    // Limpa jogo anterior (se existir)
                    if (player) {
                        player_cleanup(player);
                        player = NULL;
                    }
                    if (level) {
                        level_cleanup(level);
                        level = NULL;
                    }
                    
                    // Cria novo jogo
                    player = player_init(100, 400);
                    level = level_init();
                    menu->show_resume = false;
                    game->state = STATE_PLAYING;
                } else if (menu->selected == MENU_EXIT) {
                    game->state = STATE_EXIT;
                }
                break;
        }
    }
}

// Renderiza o menu
void menu_render(Menu *menu) {
    const char *all_options[] = {"Retomar", "Iniciar Jogo", "Sair"};
    int y_start = 250;
    int y_spacing = 40;
    
    // Título
    al_draw_text(menu->font, al_map_rgb(255, 255, 255), 
                 SCREEN_WIDTH/2, 150, ALLEGRO_ALIGN_CENTER, 
                 menu->show_resume ? "PAUSADO" : "PLATAFORMA DE SOBREVIVENCIA");
    
    // Opções do menu
    int display_index = 0;
    for (int i = 0; i < MENU_OPTION_COUNT; i++) {
        // Pula "Resume" se não deve mostrar
        if (i == MENU_RESUME && !menu->show_resume) {
            continue;
        }
        
        ALLEGRO_COLOR color = (i == (int)menu->selected) ? 
            al_map_rgb(255, 255, 0) : al_map_rgb(200, 200, 200);
        
        al_draw_text(menu->font, color, 
                    SCREEN_WIDTH/2, y_start + display_index * y_spacing, 
                    ALLEGRO_ALIGN_CENTER, all_options[i]);
        display_index++;
    }
    
    // Instruções
    al_draw_text(menu->font, al_map_rgb(150, 150, 150), 
                SCREEN_WIDTH/2, 450, ALLEGRO_ALIGN_CENTER, 
                "Use SETAS para navegar, ENTER para selecionar");
}

// Renderiza tela de fim de jogo
void game_over_screen_render(ALLEGRO_FONT *font, bool victory) {
    const char *title = victory ? "VITORIA!" : "GAME OVER";
    ALLEGRO_COLOR color = victory ? al_map_rgb(0, 255, 0) : al_map_rgb(255, 0, 0);
    
    al_draw_text(font, color, 
                SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 50, 
                ALLEGRO_ALIGN_CENTER, title);
    
    al_draw_text(font, al_map_rgb(200, 200, 200), 
                SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 20, 
                ALLEGRO_ALIGN_CENTER, 
                "Pressione qualquer tecla para voltar ao menu");
}

