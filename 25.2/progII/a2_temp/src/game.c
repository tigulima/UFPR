#include "../include/game.h"
#include "../include/menu.h"
#include "../include/player.h"
#include "../include/level.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>

// Variáveis globais do jogo (podem ser movidas para a estrutura Game se preferir)
Menu *menu = NULL;
Player *player = NULL;
Level *level = NULL;

// Inicializa o jogo e todos os componentes do Allegro
Game* game_init(void) {
    Game *game = (Game*)malloc(sizeof(Game));
    if (!game) return NULL;
    
    // Inicializa Allegro
    if (!init_allegro()) {
        free(game);
        return NULL;
    }
    
    // Cria display
    game->display = create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!game->display) {
        free(game);
        return NULL;
    }
    
    // Cria timer
    game->timer = create_timer(1.0 / FPS);
    if (!game->timer) {
        al_destroy_display(game->display);
        free(game);
        return NULL;
    }
    
    // Cria fila de eventos
    game->event_queue = create_event_queue();
    if (!game->event_queue) {
        al_destroy_timer(game->timer);
        al_destroy_display(game->display);
        free(game);
        return NULL;
    }
    
    // Carrega fonte
    game->font = al_create_builtin_font();
    if (!game->font) {
        al_destroy_event_queue(game->event_queue);
        al_destroy_timer(game->timer);
        al_destroy_display(game->display);
        free(game);
        return NULL;
    }
    
    // Registra fontes de eventos
    al_register_event_source(game->event_queue, al_get_display_event_source(game->display));
    al_register_event_source(game->event_queue, al_get_timer_event_source(game->timer));
    al_register_event_source(game->event_queue, al_get_keyboard_event_source());
    
    // Estado inicial
    game->state = STATE_MENU;
    game->running = true;
    game->redraw = false;
    
    // Inicializa menu
    menu = menu_init(game->font);
    
    // Inicia o timer
    al_start_timer(game->timer);
    
    return game;
}

// Loop principal do jogo
void game_run(Game *game) {
    ALLEGRO_EVENT event;
    
    while (game->running) {
        al_wait_for_event(game->event_queue, &event);
        
        // Processa eventos
        if (!game_handle_events(game, &event)) {
            continue;
        }
        
        // Atualiza lógica do jogo
        if (game->redraw && al_is_event_queue_empty(game->event_queue)) {
            game->redraw = false;
            game_update(game);
            game_render(game);
        }
    }
}

// Processa eventos do jogo
bool game_handle_events(Game *game, ALLEGRO_EVENT *event) {
    if (event->type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        game->running = false;
        return false;
    }
    
    if (event->type == ALLEGRO_EVENT_TIMER) {
        game->redraw = true;
    }
    
    // Processa input baseado no estado atual
    switch (game->state) {
        case STATE_MENU:
            menu_handle_input(menu, event, game);
            break;
            
        case STATE_PLAYING:
            // Input do jogador será processado no update
            if (event->type == ALLEGRO_EVENT_KEY_DOWN && event->keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                // Pausa o jogo
                menu->show_resume = true;
                menu->selected = MENU_RESUME;
                game->state = STATE_MENU;
            }
            break;
            
        case STATE_GAME_OVER:
        case STATE_VICTORY:
            // Qualquer tecla volta ao menu
            if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
                game->state = STATE_MENU;
            }
            break;
            
        case STATE_EXIT:
            game->running = false;
            return false;
    }
    
    return true;
}

// Atualiza a lógica do jogo
void game_update(Game *game) {
    switch (game->state) {
        case STATE_MENU:
            // Menu não precisa de update
            break;
            
        case STATE_PLAYING:
            if (player && level) {
                ALLEGRO_KEYBOARD_STATE key_state;
                al_get_keyboard_state(&key_state);
                
                // Atualiza jogador
                player_handle_input(player, &key_state);
                player_update(player);
                
                // Atualiza fase
                level_update(level, player);
                level_check_collisions(level, player);
                level_update_camera(level, player);
                
                // Verifica condições de vitória/derrota
                if (!player_is_alive(player)) {
                    game->state = STATE_GAME_OVER;
                } else if (level->completed) {
                    game->state = STATE_VICTORY;
                }
            }
            break;
            
        case STATE_GAME_OVER:
        case STATE_VICTORY:
        case STATE_EXIT:
            // Não há lógica para atualizar
            break;
    }
}

// Renderiza o jogo
void game_render(Game *game) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    switch (game->state) {
        case STATE_MENU:
            menu_render(menu);
            break;
            
        case STATE_PLAYING:
            if (level && player) {
                level_render(level, level->camera_x);
                player_render(player, level->camera_x);
                
                // Renderiza HUD (vida do jogador)
                al_draw_textf(game->font, al_map_rgb(255, 255, 255), 10, 10, 0, 
                             "Vida: %d/%d", player->health, player->max_health);
            }
            break;
            
        case STATE_GAME_OVER:
            game_over_screen_render(game->font, false);
            break;
            
        case STATE_VICTORY:
            game_over_screen_render(game->font, true);
            break;
            
        case STATE_EXIT:
            break;
    }
    
    al_flip_display();
}

// Limpa recursos do jogo
void game_cleanup(Game *game) {
    if (!game) return;
    
    // Limpa componentes do jogo
    if (menu) {
        menu_cleanup(menu);
        menu = NULL;
    }
    if (player) {
        player_cleanup(player);
        player = NULL;
    }
    if (level) {
        level_cleanup(level);
        level = NULL;
    }
    
    // Limpa recursos do Allegro
    if (game->font) al_destroy_font(game->font);
    if (game->event_queue) al_destroy_event_queue(game->event_queue);
    if (game->timer) al_destroy_timer(game->timer);
    if (game->display) al_destroy_display(game->display);
    
    free(game);
}

