#include "ordenacao.h"
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

////////////
// HEADER //
////////////

void getNome(char nome[])
{
	// substitua por seu nome
	strncpy(nome, "Thiago Imai Lima - Carlos Alberto Teixeira Mutzenberg", MAX_CHAR_NOME);
	nome[MAX_CHAR_NOME - 1] = '\0'; // adicionada terminação manual para caso de overflow
}

// a função a seguir deve retornar o seu número de GRR
unsigned int getGRR()
{
	return 1234;
}

////////////
// BUSCAS //
////////////

int buscaSequencial(int vetor[], int tam, int valor, int *numComparacoes)
{
	if (tam - 1 < 0)
		return -1;

	(*numComparacoes)++;
	if (valor == vetor[tam - 1])
		return tam - 1;

	return buscaSequencial(vetor, tam - 1, valor, numComparacoes);
}

int buscaBinariaRecursivo(int vetor[], int a, int b, int valor, int *numComparacoes)
{
	if (a > b)
		return -1;

	int m = (a + b) / 2;

	(*numComparacoes)++;
	if (valor == vetor[m])
		return m;

	(*numComparacoes)++;
	if (valor < vetor[m])
		return buscaBinariaRecursivo(vetor, a, m - 1, valor, numComparacoes);

	return buscaBinariaRecursivo(vetor, m + 1, b, valor, numComparacoes);
}

int buscaBinaria(int vetor[], int tam, int valor, int *numComparacoes)
{
	return buscaBinariaRecursivo(vetor, 0, tam, valor, numComparacoes);
}

////////////////////////
// FUNCOES AUXILIARES //
////////////////////////

// Troca v[a] por v[b]
void troca(int vetor[], int a, int b)
{
	int aux;

	aux = vetor[a];
	vetor[a] = vetor[b];
	vetor[b] = aux;
}

// Encontra o maior valor dentro do vetor[a..b] e retorna seu indice
int maximoVetor(int vetor[], int a, int b, int *numComparacoes)
{
	int max = a;
	for (int i = a + 1; i < b; i++)
	{
		(*numComparacoes)++;
		if (vetor[i] > vetor[max])
			max = i;
	}

	return max;
}

// Move para o lado direito todos os valores maiores
// que o ultimo valor do vetor e insere este ultimo
// valor no lugar do primeiro valor menor encontrado
void insereVetor(int vetor[], int a, int b, int *numComparacoes)
{
	int valor = vetor[b];
	int i;

	(*numComparacoes)++;
	for (i = b - 1; i >= 0 && vetor[i] > valor; i--)
		vetor[i + 1] = vetor[i]; // Move os valores > v[ultimo]

	vetor[i + 1] = valor; // Insere o v[ulitmo] no lugar do primeiro valor <= v[ultimo] encontrado
}

// Junta os vetores menores criados pelo Merge Sort,
// ordenando-os do menor para o maior
int juntaVetor(int vetor[], int a, int m, int b, int *numComparacoes)
{
	if (a >= b)
		return *vetor;

	int i = a;
	int j = m + 1;
	int vetorAux[b - a]; // O vetor fragmentado sera ordenado aqui

	// Ordena e insere no vetorAux
	for (int k = 0; k <= b - a; k++)
	{
		(*numComparacoes)++;
		if (j > b || (i <= m && vetor[i] <= vetor[j]))
		{
			vetorAux[k] = vetor[i];
			i++;
		}
		else
		{
			vetorAux[k] = vetor[j];
			j++;
		}
	}

	for (int i = 0; i <= b - a; i++)
		vetor[a + i] = vetorAux[i]; // Passa o fragmento ordenado no vetor original

	return *vetor;
}

// Compara o ultimo valor do vetor fragmentado com os valores do vetor
// Se menor, troca com os menores indices não alterados e retorna o indice
int particionaVetor(int vetor[], int a, int b, int valor, int *numComparacoes)
{
	int m = a - 1;

	for (int i = a; i <= b; i++)
	{
		(*numComparacoes)++;
		if (vetor[i] <= valor)
		{
			m++;
			troca(vetor, m, i); // Troca o menor indice nao alterado (m)
		}						// pelos valores <= v[ulitmo]
	}

	return m;
}

//////////
// SORT //
//////////

int insertionSortRecursivo(int vetor[], int tam, int *numComparacoes)
{
	if (tam <= 0)
		return *vetor;

	insertionSortRecursivo(vetor, tam - 1, numComparacoes);
	insereVetor(vetor, 0, tam - 1, numComparacoes);

	return *vetor;
}

int insertionSort(int vetor[], int tam)
{
	int n = 0;
	insertionSortRecursivo(vetor, tam, &n);

	return n;
}

int selectionSortRecursivo(int vetor[], int tam, int *numComparacoes)
{
	int maior;

	if (tam <= 1)
		return 0;

	maior = maximoVetor(vetor, 0, tam, numComparacoes);

	troca(vetor, maior, tam - 1);
	selectionSortRecursivo(vetor, tam - 1, numComparacoes);

	return 0;
}

int selectionSort(int vetor[], int tam)
{
	int n = 0;
	selectionSortRecursivo(vetor, tam, &n);

	return n;
}

int mergeSortRecursivo(int vetor[], int a, int b, int *numComparacoes)
{
	if (a >= b)
		return *vetor;

	int m = (a + b) / 2;

	mergeSortRecursivo(vetor, a, m, numComparacoes);
	mergeSortRecursivo(vetor, m + 1, b, numComparacoes);

	return juntaVetor(vetor, a, m, b, numComparacoes);
}

int mergeSort(int vetor[], int tam)
{
	int n = 0;
	mergeSortRecursivo(vetor, 0, tam - 1, &n);

	return n;
}

int quickSortRecursivo(int vetor[], int a, int b, int *numComparacoes)
{
	if (a >= b)
		return *vetor;

	int m = particionaVetor(vetor, a, b, vetor[b], numComparacoes);

	quickSortRecursivo(vetor, a, m - 1, numComparacoes);
	quickSortRecursivo(vetor, m + 1, b, numComparacoes);

	return *vetor;
}

int quickSort(int vetor[], int tam)
{
	int n = 0;
	quickSortRecursivo(vetor, 0, tam - 1, &n);

	return n;
}

void heapSortRecursivo(int vetor[], int n, int i, int *numComparacoes)
{
	int maior = i;
	int esq = 2 * i + 1;
	int dir = 2 * i + 2;

	(*numComparacoes)++;
	if (esq < n && vetor[esq] > vetor[maior])
		maior = esq;

	(*numComparacoes)++;
	if (dir < n && vetor[dir] > vetor[maior])
		maior = dir;

	if (maior != i)
	{
		troca(vetor, i, maior);
		heapSortRecursivo(vetor, n, maior, numComparacoes);
	}
}

int heapSort(int vetor[], int tam)
{
	int n = 0;
	for (int i = tam / 2 - 1; i >= 0; i--)
		heapSortRecursivo(vetor, tam, i, &n);

	for (int i = tam - 1; i >= 0; i--)
	{
		troca(vetor, 0, i);
		heapSortRecursivo(vetor, i, 0, &n);
	}

	return n;
}