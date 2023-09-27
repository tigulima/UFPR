Main: main.c arff.c log.c
	$(CC) main.c arff.c log.c -o main

run: main.c arff.c log.c
	$(CC) main.c arff.c log.c -o main
	./main -i arff/netlog.arff -p -v -a -b -c -d

test: main.c arff.c log.c
	$(CC) main.c arff.c log.c -o main
	./main -i arff/test.arff -p -v -a -b -c -d

gdb: main.c arff.c log.c
	$(CC) -g main.c arff.c log.c -o main
	gdb --args ./main -i arff/test.arff -p -v -a -b -c -d

valgrind: main.c arff.c log.c
	$(CC) main.c arff.c log.c -o main
	valgrind --leak-check=full --track-origins=yes ./main -i arff/test.arff -p -v -a -b -c -d

clear:
	rm -f main
	rm -f R_ATAQUES.txt
	rm -f R_ENTIDADES.txt
	rm -f R_TAMANHO.txt
	rm -f BLACKLIST.bl
