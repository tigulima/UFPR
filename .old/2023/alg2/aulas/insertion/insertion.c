#include <stdio.h>
#include <stdlib.h>

#define TAM_VET 10

void le_vetor(int *v) {
	for(int i = 0; i < TAM_VET; i++)
		scanf("%d", &v[i]);
}

void escreve_vetor(int *v) {
	printf("Vetor: ");
	for(int i = 0; i < TAM_VET; i++)
		printf("%d ", v[i]);

	printf("\n");
}

void troca(int *v, int a, int b) {
	int aux;
	
	aux = v[b];

	for(int i = b; i > a; i--)
 		v[i] = v[i - 1];

	v[a] = aux;
}

int *insertion(int *v, int a, int b) {
	if (a > b)
		return 0;

	insertion(v, a, b-1);
	troca(v, a, b);
		
	return v;
}

int main() {
	int n;
	int v[TAM_VET]; 

	printf("v: ");
	le_vetor(v);

	insertion(v, 0, TAM_VET-1);

	escreve_vetor(v);

	return 0;
}
