#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#include "enemy.h"

char is_nat(char *string){
	for (int i = 0; string[i]; i++) 
		if (!isdigit(string[i])) 
			return 0;
	return 1; 
}

void update_report(FILE *report, space *board, shot_sentinel *list, int r){
	fprintf(report, "============= ROUND %d =============\n=> MAP:\n", r);
	for (int i = 1; i <= board->max_y; i++){
		for (int j = 1; j <= board->max_x; j++){
			if (board->map[i][j].entity)
				fprintf(report, "| E ");
			else
				fprintf(report, "| 0 ");
		}
		fprintf(report, "|\n");
	}
	fprintf(report, "\n=> SHOTS:\n");
	for (shot *i = (shot*) list->first; i; i = (shot*) i->next) 
		fprintf(report, " - x: %u, y: %u\n", i->position_x, i->position_y);
	fprintf(report, "\n====================================\n\n");
}

void execute_event(space *board, shot_sentinel *list){
//IMPLEMENTAR!
//A cada evento:
//  Os tiros que não acertaram o alvo, ou não sairam do tabuleiro devem ser atualizados (movidos para frente no tabuleiro)
//  Os inimigos que não tem outros inimigos em sua frente devem atirar

	update_shots(board, list);
}

int main(int argc, char** argv){
	int opt;
	int x = -1;
	int y = -1;
	int e = -1;
	int r = -1;
	char *o = 0; 

	opt = getopt(argc, argv, "x:y:e:r:o:");
	if (opt == -1){
		fprintf(stderr, "Forma de uso: ./space_enemies -x map_x_limit -y map_y_limit -e map_enemy_lines -r rounds -o output\n");
		return 1;
	}	

	do {
		switch (opt) {
		case 'x':
			if (is_nat(optarg)) x = atoi(optarg);
			else {fprintf(stderr, "ERRO: o número de colunas é inválido !\n"); return 2;}
			break;
		case 'y':
			if (is_nat(optarg)) y = atoi(optarg);
			else {fprintf(stderr, "ERRO: o número de colunas é inválido!\n"); return 3;}
			break;
		case 'e':
			if (is_nat(optarg)) e = atoi(optarg);
			else {fprintf(stderr, "ERRO: o número de linhas de inimigos é inválido!\n"); return 4;}
			break;
		case 'r':
			if (is_nat(optarg)) r = atoi(optarg);
			else {fprintf(stderr, "ERRO: o número de rodadas é inválido!\n"); return 5;}
			break;
		case 'o':
			o = strdup(optarg);
			break;
		default:
			fprintf(stderr, "Forma de uso: ./space_enemies -x map_x_limit -y map_y_limit -e map_enemy_lines -r rounds -o output\n");
			return 1;
		}
	} while ((opt = getopt(argc, argv, "x:y:e:r:o:")) != -1);

	//NÃO ESQUEÇA DE TRATAR POSSÍVEIS ERROS!

	FILE *report = fopen(o, "w+");
	space *board = create_board(y, x, e);
	shot_sentinel* shot_list = create_shotlist();

	for (int t = 0; t < r; t++){
		execute_event(board, shot_list);
		update_report(report, board, shot_list, t);
	}

	clean_board(board);
	destroy_board(board);
	clean_shots(shot_list);
	free(shot_list);
	free(o);
	fclose(report);

	return 0;
}