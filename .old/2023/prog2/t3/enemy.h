#ifndef __ENEMY__
#define __ENEMY__

#include "space.h"

typedef struct shot shot;
struct shot{
	int position_x;
	int position_y;
	int trajectory;
	shot *next;
} ;

typedef struct shot_sentinel{
	shot *first;
	shot *last;
} shot_sentinel;

typedef struct enemy{
	int position_x;
	int position_y;
} enemy;

shot_sentinel* create_shotlist(void);
void clean_shots(shot_sentinel *list);
shot* remove_shot(shot* current, shot* previous, shot_sentinel *list);
shot_sentinel* straight_shoot(space *board, shot_sentinel *list, enemy *shooter);
void update_shots(space *board, shot_sentinel *list);

int add_enemy(space *board, int position_y, int position_x);
int remove_enemy(space *board, int position_y, int position_x);

#endif
