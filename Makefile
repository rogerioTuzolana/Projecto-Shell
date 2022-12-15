all: jc-shell fibonacci div0 jcshell-terminal

jc-shell: list.o jc-shell.o commandlinereader.o 
	gcc -o jc-shell list.o jc-shell.o commandlinereader.o -lpthread

fibonacci: fibonacci.o
	gcc -o fibonacci fibonacci.o

jcshell-terminal: jcshell-terminal.o
	gcc -o jcshell-terminal jcshell-terminal.o

div0: div0.o
	gcc -o div0 div0.o
	
g = gcc
CFLAGS = $(g) -g -Wall -pedantic -c

list.o: list.c list.h
	$(CFLAGS) list.c

jcshell-terminal.o: jcshell-terminal.c 
	$(CFLAGS) jcshell-terminal.c

fibonacci.o: fibonacci.c
	$(CFLAGS) fibonacci.c

div0.o: div0.c
	$(CFLAGS) div0.c

commandlinereader.o: commandlinereader.c commandlinereader.h
	$(CFLAGS) commandlinereader.c

jc-shell.o: jc-shell.c commandlinereader.h Ficheiro.h
	$(CFLAGS) jc-shell.c

clean:
	clear
	rm -f *.o  *.txt jc-shell fibonacci div0 jcshell-terminal jcshell-in
run:
	clear
	./jc-shell < test2.txt
