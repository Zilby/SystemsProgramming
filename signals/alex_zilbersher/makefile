all: signals.o 
	gcc -o run signals.o
	./run

exeggcute.o: signals.c signals.h
	gcc -c signals.c
clean: 
	rm *o
	rm ./run
	rm *.txt