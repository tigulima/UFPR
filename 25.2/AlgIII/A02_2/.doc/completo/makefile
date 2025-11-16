parametrosCompilacao=-Wall
parametrosVinculacao=-lm
nomePrograma=kdtree_completo

all: $(nomePrograma)

$(nomePrograma): main_completo.o kdtree_completo.o
	gcc -o $(nomePrograma) main_completo.o kdtree_completo.o $(parametrosCompilacao) $(parametrosVinculacao)

main_completo.o: main_completo.c kdtree_completo.h
	gcc -c main_completo.c $(parametrosCompilacao)

kdtree_completo.o: kdtree_completo.h kdtree_completo.c
	gcc -c kdtree_completo.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)

