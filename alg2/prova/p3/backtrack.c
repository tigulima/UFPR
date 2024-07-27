#include <stdio.h>
#include <stdlib.h>

void preenche_vetor(int v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i] = 0;
    }
}

void imprime_vetor(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void backtrack(int v[], int n, int i, int k) {
    if (i == n){
        imprime_vetor(v, n);
        return;
    }

    for (int j = 0; j < k; j++) {
        v[i] = j;
        backtrack(v, n, i+1, k);
    }
}

int main() {

    int n = 3;
    int k = 3;
    int v[n];

    preenche_vetor(v, n);

    backtrack(v, n, 0, k);

    return 0;
}