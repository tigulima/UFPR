#include "../include/game.h"
#include "../include/menu.h"
#include "../include/player.h"
#include "../include/level.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>

Menu *menu = NULL;
Player *player = NULL;
Level *level = NULL;

Game* game_init(void) {
    Game *game = (Game*)malloc(sizeof(Game));
    if (!game) return NULL;
    
    if (!init_allegro()) {
        free(game);
        return NULL;
    }
    
    game->display = create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!game->display) {
        free(game);
        return NULL;
    }
    
    game->timer = create_timer(1.0 / FPS);
    if (!game->timer) {
        al_destroy_display(game->display);
        free(game);
        return NULL;
    }
    
    game->event_queue = create_event_queue();
    if (!game->event_queue) {
        al_destroy_timer(game->timer);
        al_destroy_display(game->display);
        free(game);
        return NULL;
    }
    
    game->font = al_create_builtin_font();
    if (!game->font) {
        al_destroy_event_queue(game->event_queue);
        al_destroy_timer(game->timer);
        al_destroy_display(game->display);
        free(game);
        return NULL;
    }
    
    al_register_event_source(game->event_queue, al_get_display_event_source(game->display));
    al_register_event_source(game->event_queue, al_get_timer_event_source(game->timer));
    al_register_event_source(game->event_queue, al_get_keyboard_event_source());
    
    game->state = STATE_MENU;
    game->running = true;
    game->redraw = false; // Para evitar renderização excessiva
    
    menu = menu_init(game->font);
    
    al_start_timer(game->timer);
    
    return game;
}

void game_run(Game *game) {
    ALLEGRO_EVENT event;
    
    while (game->running) {
        al_wait_for_event(game->event_queue, &event);
        
        if (!game_handle_events(game, &event)) {
            continue;
        }
        
        if (game->redraw && al_is_event_queue_empty(game->event_queue)) {
            game->redraw = false;
            game_update(game);
            game_render(game);
        }
    }
}

bool game_handle_events(Game *game, ALLEGRO_EVENT *event) {
    if (event->type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        game->running = false;
        return false;
    }
    
    if (event->type == ALLEGRO_EVENT_TIMER) {
        game->redraw = true;
    }
    
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

void game_update(Game *game) {
    switch (game->state) {
        case STATE_MENU:
            break;
            
        case STATE_PLAYING:
            if (player && level) {
                ALLEGRO_KEYBOARD_STATE key_state;
                al_get_keyboard_state(&key_state);
                
                // Atualizar jogador
                player_handle_input(player, &key_state);
                player_update(player);
                
                // Atualizar fase
                level_update(level, player);
                level_check_collisions(level, player);
                level_update_camera(level, player);
                
                // Verificar condições de vitória/derrota
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
                
                // Renderiza a vida do jogador
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

