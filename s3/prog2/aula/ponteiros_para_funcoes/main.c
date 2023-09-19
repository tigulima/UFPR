#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAM_VET 10

void escreve_vetor(float *v) {
	printf("vetor: ");

	for(int i = 0; v[i]; i++)
		printf("%.2f ", v[i]);
	
	printf("\n");
}

void sqrt_op(float *v) {}
void cbrt_op(float *v) {}
void ceil_op(float *v) {}

void floor_op(float *v) {
	for(int i = 0; v[i]; i++)
		v[i] = floor(v[i]);
}

int menu() {
	int op = -1;
	printf("\n====================\n");
	printf("Selecione a operação\n\n");
	printf("1: sqrt\n");
	printf("2: cbrt\n");
	printf("3: ceil\n");
	printf("4: floot\n\n");
	printf("op: ");

	scanf("%d", &op);

	return op;
}

void aplica(float *v, int op) {

	switch(op){
		case 1:
			printf("selected sqrt\n");
			break;
		case 2:
			printf("selected cbrt\n");
			break;
		case 3:
			printf("selected ceil\n");
			break;
		case 4:
			printf("selected floor\n");
			floor_op(v);
			break;
	}
}

int main() {
	float v[TAM_VET] = {54.3, 34.2, 65.2, 5.7, 12.45, 65.3, 23.9, 87.94, 74, 12};
	int op = menu();

	aplica(v, op);
	escreve_vetor(v);
}
