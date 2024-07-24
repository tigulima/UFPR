#include <stdlib.h>
#include <stdio.h>

void maxHeadpfy() {
	return;
}

void readArray(int *v) {
	int tam;

	printf("Tamanho do vetor: ");
	scanf("%d", &tam);

	printf("Vetor: ");
	for(int i = 0; i < tam; i++)
		scanf("%d", &v[i]);
	v[tam] = NULL;
	printf("\n");	

	return;		 
}

void writeArray(int *v) {
	printf("Vetor: ");
	for(int i = 0; v[i]; i++)
		printf("%d ", v[i]);
	printf("\n");
}

int main() {

	int v[100];

	readArray(v);
	writeArray(v);
}
