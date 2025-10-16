parametrosCompilacao=-Wall #-Wshadow
nomePrograma=antesprova2_20204397

all: $(nomePrograma)

$(nomePrograma): main.o redblack.o
	gcc -o $(nomePrograma) main.o redblack.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

ordenacao.o: redblack.h redblack.c
	gcc -c redblack.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
