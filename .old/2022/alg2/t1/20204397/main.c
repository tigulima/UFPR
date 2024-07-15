#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ordenacao.h"

////////////////////////
// FUNCOES AUXILIARES //
////////////////////////

void header()
{
	char nome[MAX_CHAR_NOME];

	getNome(nome);
	printf("Trabalho de %s\n", nome);
	printf("GRR %u\n", getGRR());
	printf("\n");
}

int lerVetor()
{
	int tamVetor;

	printf("Insira o tamanho do vetor: ");
	scanf("%d", &tamVetor);
	printf("\n");

	return tamVetor;
}

int *alocaVetor(int tamVetor)
{
	int *vetor = malloc(tamVetor * sizeof(int));
	if (vetor == NULL)
	{
		printf("Falha fatal. Impossível alocar memoria.");
		return NULL;
	}

	return vetor;
}

void criaVetorRand(int vetor[], int tamVetor)
{
	srand(time(NULL));
	for (int i = 0; i < tamVetor; i++)
		vetor[i] = rand() % 100;
}

void copiaVetor(int vetor[], int vetorAux[], int tamVetor)
{
	for (int i = 0; i < tamVetor; i++)
		vetorAux[i] = vetor[i];
}

void imprimeVetor(int vetor[], int tamVetor)
{
	// printf("Vetor: ");
	// for (int i = 0; i < tamVetor; i++)
	// 	printf("%d ", vetor[i]);
	// printf("\n");
}

void imprimeAnalise(int numComp, int start, int end)
{
	double tempo = ((double)end - start) / CLOCKS_PER_SEC;
	printf("Tempo total: %f\n", tempo);
	printf("Comparacoes: %d\n", numComp);
}

void resetaVetor(int vetor[], int vetorAux[], int tamVetor)
{
	for (int i = 0; i < tamVetor; i++)
		vetor[i] = vetorAux[i];
}

//////////
// MAIN //
//////////

int main()
{
	header();

	int idxBusca;
	int numComp;

	int tamVetor = lerVetor();

	int *vetor = alocaVetor(tamVetor);
	int *vetorAux = alocaVetor(tamVetor);

	criaVetorRand(vetor, tamVetor);
	imprimeVetor(vetor, tamVetor);

	copiaVetor(vetor, vetorAux, tamVetor);

	// Para medir o tempo, inclua time.h, e siga o exemplo:
	clock_t start, end; // variáveis do tipo clock_t

	printf("\n");

	// INSERTION SORT //

	printf(" --- Insertion Sort --- \n");
	start = clock();
	numComp = insertionSort(vetor, tamVetor);
	end = clock();

	imprimeAnalise(numComp, start, end);

	resetaVetor(vetor, vetorAux, tamVetor);
	printf("\n");

	// SELECTION SORT //

	printf(" --- Selection Sort --- \n");
	start = clock();
	numComp = selectionSort(vetor, tamVetor);
	end = clock();

	imprimeAnalise(numComp, start, end);

	resetaVetor(vetor, vetorAux, tamVetor);
	printf("\n");

	// MERGE SORT //

	printf(" --- Merge Sort --- \n");
	start = clock();
	numComp = mergeSort(vetor, tamVetor);
	end = clock();

	imprimeAnalise(numComp, start, end);

	resetaVetor(vetor, vetorAux, tamVetor);
	printf("\n");

	// QUICK SORT //

	printf(" --- Quick Sort --- \n");
	start = clock();
	numComp = quickSort(vetor, tamVetor);
	end = clock();

	imprimeAnalise(numComp, start, end);

	resetaVetor(vetor, vetorAux, tamVetor);
	printf("\n");

	// HEAP SORT //

	printf(" --- Heap Sort --- \n");
	start = clock();
	numComp = heapSort(vetor, tamVetor);
	end = clock();

	imprimeAnalise(numComp, start, end);

	printf("\n");

	imprimeVetor(vetor, tamVetor);

	////////////
	// BUSCAS //
	////////////

	int busca;
	printf("\nInsira um valor para busca-lo: ");
	scanf("%d", &busca);

	printf("\n --- Buscas --- \n");

	double tempo;
	numComp = 0;

	// BUSCA SEQUENCIAL //

	printf("Sequencial:\n");
	start = clock();
	idxBusca = buscaSequencial(vetor, tamVetor, busca, &numComp);
	end = clock();
	tempo = ((double)end - start) / CLOCKS_PER_SEC;

	printf("Tempo total: %f\n", tempo);
	printf("Busca: %d, Comp: %d\n", idxBusca, numComp);

	idxBusca = 0;
	numComp = 0;

	// BUSCA BINARIA //

	printf("\nBinario:\n");

	start = clock();
	idxBusca = buscaBinaria(vetor, tamVetor, busca, &numComp);
	end = clock();

	tempo = ((double)end - start) / CLOCKS_PER_SEC;
	printf("Tempo total: %f\n", tempo);
	printf("Busca: %d, Comp: %d\n", idxBusca, numComp);

	/////////
	// FIM //
	/////////

	free(vetor);
	free(vetorAux);

	return 0;
}
