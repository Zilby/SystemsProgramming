all: main.o pl.o plt.o
	gcc -o Run main.o pl.o plt.o
	./Run

main.o: main.c pl.h
	gcc -c main.c

pl.o: pl.c pl.h
	gcc -c pl.c

plt.o: plt.c pl.h
	gcc -c plt.c

clean: 
	rm *o
	rm ./Run
