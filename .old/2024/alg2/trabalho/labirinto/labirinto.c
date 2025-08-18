//==========================================
//Author: Paulo R. Lisboa de Almeida
//Date:   7 Feb 2023
//==========================================

#include <stdio.h>

#define M 20
#define N 18
#define PAREDE 64
#define PASSAGEM 32
#define PASSOU 46

void imprimirLabirinto(int labirinto[][N]);
void lerLabirinto(int labirinto[][N], int*linInicio, int* colInicio, int* linFim, int* colFim);
int resolveLabirinto(int labirinto[][N], int linAtual, int colAtual, int linFim, int colFim);

int main(){
	int labirinto[M][N];
	int linhaInicio, colInicio, linhaFim, colFim;
	lerLabirinto(labirinto, &linhaInicio, &colInicio, &linhaFim, &colFim);
	//Testa o caminho possíel
	if (!resolveLabirinto(labirinto, linhaInicio, colInicio, linhaFim, colFim))
		printf("Não achou o caminho :(\n");

	imprimirLabirinto(labirinto);

	return 0;
}

void lerLabirinto(int labirinto[][N], int*linInicio, int* colInicio, int* linFim, int* colFim){
	scanf("%d %d %d %d", linInicio, colInicio, linFim, colFim);
	for(int i=0; i < M; i++)
		for(int j=0; j<N; j++)
			scanf("%d", &labirinto[i][j]);
}

void imprimirLabirinto(int labirinto[][N]){
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			printf("%c",labirinto[i][j]);
		}
		printf("\n");
	}
}

int resolveLabirinto(int labirinto[][N], int linAtual, int colAtual, int linFim, int colFim){

	// Retorna se atinge a borda do labirinto
	if (linAtual < 0 || linAtual > M || colAtual < 0 || colAtual > N)
		return 0;

	// Retorna se ja passou por ali ou se achou uma parede
	if (labirinto[linAtual][colAtual] != PASSAGEM)
		return 0;

	// Retorna se achou a saida
	if (linAtual == linFim && colAtual == colFim)
		return 1;

	// Joga o paozinho pra marcar o caminho
	labirinto[linAtual][colAtual] = PASSOU;


	// Testa todos os caminhos e retorna 1 se for passagem
	if (resolveLabirinto(labirinto, linAtual + 1, colAtual, linFim, colFim))
		return 1; // Retorna se tem passagem em cima

	if (resolveLabirinto(labirinto, linAtual, colAtual + 1, linFim, colFim))
		return 1; // Retorna se tem passagem na direita

	if (resolveLabirinto(labirinto, linAtual - 1, colAtual, linFim, colFim))
		return 1; // Retorna se tem passagem em baixo

	if (resolveLabirinto(labirinto, linAtual, colAtual - 1, linFim, colFim))
		return 1; // Retorna se tem passagem na esquerda

	// Marca o caminho como uma passagem possível
	labirinto[linAtual][colAtual] = PASSAGEM;

	return 0;

}
