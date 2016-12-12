all: reading.o main.o
	gcc -o Run reading.o main.o
	./Run

reading.o: reading.c reading.h
	gcc -c reading.c

main.o: main.c reading.h
	gcc -c main.c
clean: 
	rm *o
	rm ./Run
