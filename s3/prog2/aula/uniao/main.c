#include <stdio.h>
#include <stdlib.h>

typedef union {
	char charArray[20];
	int intArray[6];
} str_u;

void alloc(str_u *str) {
	if(!(str = malloc(sizeof(str_u) + 1)))
		printf("Erro ao alocar mamória!");
}

void write(str_u str) {
	
}

int main() {
	str_u *str;

	alloc(str);

	for(int i = 0; str->charArray[i]; i++)
		str->charArray[i] = 'a';

	for(int i = 0; str->charArray[i]; i++)
		printf("%s ", str->charArray[i]);

	printf("\n");

	return 0;
}
