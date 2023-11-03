//Compilação: gcc AggressiveSquares.c Square.c -o AS $(pkg-config allegro-5 allegro_main-5 allegro_font-5 --libs --cflags)

#include <allegro5/allegro5.h>														//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>													//Biblioteca de fontes do Allegro

int main(){
	al_init();																		//Faz a preparação de requisitos da biblioteca Allegro
	al_install_keyboard();															//Habilita a entrada via teclado (eventos de teclado), no programa

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);								//Cria o relógio do jogo; isso indica quantas atualizações serão realizadas por segundo (30, neste caso)
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();							//Cria a fila de eventos; todos os eventos (programação orientada a eventos) 
	ALLEGRO_FONT* font = al_create_builtin_font();									//Carrega uma fonte padrão para escrever na tela (é bitmap, mas também suporta adicionar fontes ttf)
	ALLEGRO_DISPLAY* disp = al_create_display(320, 320);							//Cria uma janela para o programa, define a largura (x) e a altura (y) da tela em píxeis (320x320, neste caso)

	al_register_event_source(queue, al_get_keyboard_event_source());				//Indica que eventos de teclado serão inseridos na nossa fila de eventos
	al_register_event_source(queue, al_get_display_event_source(disp));				//Indica que eventos de tela serão inseridos na nossa fila de eventos
	al_register_event_source(queue, al_get_timer_event_source(timer));				//Indica que eventos de relógio serão inseridos na nossa fila de eventos

	ALLEGRO_EVENT event;															//Variável que guarda um evento capturado, sua estrutura é definida em: https://www.allegro.cc/manual/5/ALLEGRO_EVENT
	al_start_timer(timer);															//Função que inicializa o relógio do programa
	while(1){																		//Laço principal do programa
		al_wait_for_event(queue, &event);											//Função que captura eventos da fila, inserindo os mesmos na variável de eventos
		
		if (event.type == 30){														//O evento tipo 30 indica um evento de relógio, ou seja, verificação se a tela deve ser atualizada (conceito de FPS)
			al_clear_to_color(al_map_rgb(0, 0, 0));									//Substitui tudo que estava desenhado na tela por um fundo preto
    		al_flip_display();														//Insere as modificações realizadas nos buffers de tela
		}
		else if (event.type == 42) break;											//Evento de clique no "X" de fechamento da tela. Encerra o programa graciosamente.
	}

	al_destroy_font(font);															//Destrutor da fonte padrão
	al_destroy_display(disp);														//Destrutor da tela
	al_destroy_timer(timer);														//Destrutor do relógio
	al_destroy_event_queue(queue);													//Destrutor da fila

	return 0;
}