#ifndef __SPACE__
#define __SPACE__

typedef struct {
	void *entity;
	enum {ENEMY, OBSTACLE, SHIP} type;
} sqm;

typedef struct {
	sqm **map;
	int max_x;
	int max_y;
} space;

space* create_board(int max_y, int max_x, int enemy_lines);
void clean_board(space *board);
void destroy_board(space *board);


#endif
