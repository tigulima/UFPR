Main: main.c arff.c log.c
	$(CC) main.c arff.c log.c -o main

run: main.c arff.c log.c
	$(CC) main.c arff.c log.c -o main
	./main -i arff/netlog.arff -p -v -a -b -c -d

test: main.c arff.c log.c
	$(CC) main.c arff.c log.c -o main
	./main -i arff/test.arff -p -v -a -b -c -d

clear:
	rm main
	rm R_ATAQUES.txt
	rm R_ENTIDADES.txt
	rm R_TAMANHO.txt
	rm BLACKLIST.bl
