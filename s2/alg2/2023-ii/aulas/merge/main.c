#include <stdio.h>
#include <stdlib.h>

#define TAM_VET 10

void escreve_vetor(int *v) {
	printf("Vetor: ");

	for(int i = 0; v[i]; i++)
		printf("%d ", v[i]);

	printf("\n");
}

void merge(int *v, int a, int b) {
	int meio = (a + b) / 2;

	merge(v, a, meio - 1);
	merge(v, meio, b);

	escreve_vetor(v);

	printf("Meio: %d\n", meio);
}

int main() {
	int v[TAM_VET] = {7, 3, 4, 1, 4, 6, 3, 56, 23, 1};

	merge(v, 0, TAM_VET);
	escreve_vetor(v);

	return 0;
}
