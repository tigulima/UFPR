#include <stdio.h>
#include <stdlib.h>

#define TAM_VET 10

void escreve_vetor(int *v, int tam) {
	printf("vetor: ");

	for (int i = 0; i < tam; i++)
		printf("%d ", v[i]);

	printf("\n");
}

void troca(int *v, int a, int b) {
	int aux = v[a];

	v[a] = v[b];
	v[b] = aux;
} 

int busca_menor(int *v, int a, int b) {
	int menor = 0;

	for (int i = a; i < b; i++) {
		if (v[menor] > v[i])
			menor = i;
	}

	printf("m: %d\n", v[menor]);

	return menor;
}

int *selection(int *v, int a, int b) {
	
	if (a >= b)
		return v;

	int menor = busca_menor(v, a, b);

	troca(v, a, menor);
	escreve_vetor(v, TAM_VET);
	return selection(v, a + 1, b);
}

int main() {
	int v[TAM_VET] = {23,56,1,5,13,8,12,3,67,2};

	escreve_vetor(v, TAM_VET);
	selection(v, 0, TAM_VET);
	escreve_vetor(v, TAM_VET);

	return 0;
}
