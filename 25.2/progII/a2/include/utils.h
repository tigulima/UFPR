#ifndef UTILS_H
#define UTILS_H

#include <allegro5/allegro.h>
#include <stdbool.h>

// Funções auxiliares para detecção de colisão
bool check_collision_aabb(float x1, float y1, float w1, float h1,
                          float x2, float y2, float w2, float h2);

// Funções auxiliares para inicialização do Allegro
bool init_allegro(void);
ALLEGRO_DISPLAY* create_display(int width, int height);
ALLEGRO_TIMER* create_timer(double fps);
ALLEGRO_EVENT_QUEUE* create_event_queue(void);

// Função de erro
void error_exit(const char *message);

#endif

