#include <stdio.h>
#include <stdlib.h>

#define MAX_V 100

int minimo(int *v, int a, int b) {}

void init_v(int *v, int n) {
    for(int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    return;
}

void write_v(int *v, int n) {
    printf("\nvetor: ");
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    
    printf("\n");
    return;
}

int main() {
    int v[MAX_V], n;

    printf("Qual o tamanho do vetor? ");
    scanf("%d", &n);

    init_v(v, n);
    write_v(v, n);

    printf("minimo: %d", minimo(v, 0, n));

    return 0;
}
