#include <stdlib.h>

#include "enemy.h"

shot_sentinel* create_shotlist(void){
	shot_sentinel *list = (shot_sentinel*) malloc (sizeof(shot_sentinel));
	if (list == NULL) return NULL;
	list->first = NULL;
	list->last  = NULL;
	return list;
}

shot* remove_shot(shot* current, shot* previous, shot_sentinel *list){
//IMPLEMENTAR!
//	Remove os tiros da lista

	if (previous == NULL)
		list->first = current->next;
	else
		previous->next = current->next;

	if (current->next == NULL)
		list->last = previous;

	free(current);

	return previous;
}

void clean_shots(shot_sentinel *list){
	shot *p = (shot*) list->first;
	shot *q = NULL;
	while (p != NULL)
		p = remove_shot(p, q, list);
}

void update_shots(space *board, shot_sentinel *list){
//IMPLEMENTAR!
//Os tiros presentes no tabuleiro devem ser atualizados
//  Se o tiro acertar um alvo, ou sair do tabuleiro, ele deve ser removido da lista
//  Caso contrário, ele deve "andar" uma casa (sqm) à frente

	shot *p = (shot*) list->first;
	shot *q = NULL;

		if (!p)
			return;

		if (p->position_y == 0 || p->position_y == board->max_y + 1)
			p = remove_shot(p, q, list);
		else if (board->map[p->position_y][p->position_x].entity != NULL){
			remove_enemy(board, p->position_y, p->position_x);
			p = remove_shot(p, q, list);
		}
		else {
			p->position_y += 1;
			q = p;
			p = p->next;
		}
}

shot* straight_shot(space *board, shot *list, enemy *shooter){
//IMPLEMENTAR!
//Adiciona um novo tiro à lista. Neste momento, todos os tiros se movem apenas para frente

	shot *new_shot = (shot*) malloc (sizeof(shot));
	if (!new_shot) return NULL;
		
	new_shot->position_x = shooter->position_x;
	new_shot->position_y = shooter->position_y;
	new_shot->next = NULL;

	if(list == NULL){
		list = new_shot;
		return list;
	}

	return new_shot;
}

int add_enemy(space *board, int position_y, int position_x){
//IMPLEMENTAR!
//Adiciona um inimigo no tabuleiro. Essa tarefa inclui a alocação do mesmo

	enemy *e;

	if (!(e = malloc(sizeof(enemy))))
		return 0;

	e->position_x = position_x;
	e->position_y = position_y;

	board->map[position_y][position_x].entity = e;

	return 1;
}

int remove_enemy(space *board, int position_y, int position_x){
//IMPLEMENTAR!
//Remove um inimigo do tabuleiro. Essa tarefa inclui a desalocação do mesmo

	enemy *e = board->map[position_y][position_x].entity;

	return 1;
}
