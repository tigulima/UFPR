#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

// Detecção de colisão AABB (Axis-Aligned Bounding Box)
bool check_collision_aabb(float x1, float y1, float w1, float h1,
                          float x2, float y2, float w2, float h2) {
    return (x1 < x2 + w2 &&
            x1 + w1 > x2 &&
            y1 < y2 + h2 &&
            y1 + h1 > y2);
}

// Inicializa todos os addons do Allegro
bool init_allegro(void) {
    if (!al_init()) {
        fprintf(stderr, "Falha ao inicializar Allegro\n");
        return false;
    }
    
    if (!al_install_keyboard()) {
        fprintf(stderr, "Falha ao inicializar teclado\n");
        return false;
    }
    
    if (!al_init_image_addon()) {
        fprintf(stderr, "Falha ao inicializar addon de imagem\n");
        return false;
    }
    
    if (!al_init_font_addon()) {
        fprintf(stderr, "Falha ao inicializar addon de fonte\n");
        return false;
    }
    
    if (!al_init_ttf_addon()) {
        fprintf(stderr, "Falha ao inicializar addon TTF\n");
        return false;
    }
    
    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Falha ao inicializar addon de primitivas\n");
        return false;
    }
    
    // TODO: Inicializar addon de áudio para funcionalidade extra [10]
    // if (!al_install_audio()) { ... }
    // if (!al_init_acodec_addon()) { ... }
    
    return true;
}

// Cria display
ALLEGRO_DISPLAY* create_display(int width, int height) {
    ALLEGRO_DISPLAY *display = al_create_display(width, height);
    if (!display) {
        fprintf(stderr, "Falha ao criar display\n");
        return NULL;
    }
    
    al_set_window_title(display, "Plataforma de Sobrevivencia");
    return display;
}

// Cria timer
ALLEGRO_TIMER* create_timer(double fps) {
    ALLEGRO_TIMER *timer = al_create_timer(fps);
    if (!timer) {
        fprintf(stderr, "Falha ao criar timer\n");
        return NULL;
    }
    return timer;
}

// Cria fila de eventos
ALLEGRO_EVENT_QUEUE* create_event_queue(void) {
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if (!queue) {
        fprintf(stderr, "Falha ao criar fila de eventos\n");
        return NULL;
    }
    return queue;
}

// Exibe mensagem de erro e encerra
void error_exit(const char *message) {
    fprintf(stderr, "ERRO: %s\n", message);
    exit(EXIT_FAILURE);
}

