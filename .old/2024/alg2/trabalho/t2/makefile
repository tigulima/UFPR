parametrosCompilacao=-Wall #-Wshadow
nomePrograma=trab2grr20204397

all: $(nomePrograma)

$(nomePrograma): main.o ordenacao.o pilha.o
	gcc -o $(nomePrograma) main.o ordenacao.o pilha.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

ordenacao.o: ordenacao.h ordenacao.c pilha.h
	gcc -c ordenacao.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
