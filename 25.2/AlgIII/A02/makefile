parametrosCompilacao=-Wall #-Wshadow
parametrosVinculacao=-lm
nomePrograma=prova4_20204397

all: $(nomePrograma)

$(nomePrograma): main.o kdtree.o
	gcc -o $(nomePrograma) main.o kdtree.o $(parametrosCompilacao) $(parametrosVinculacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

kdtree.o: kdtree.h kdtree.c
	gcc -c kdtree.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)