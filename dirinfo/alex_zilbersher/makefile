all: dir.o main.o
	gcc -o Run dir.o main.o
	./Run

reading.o: dir.c dir.h
	gcc -c dir.c

main.o: main.c dir.h
	gcc -c main.c
clean: 
	rm *o
	rm ./Run
