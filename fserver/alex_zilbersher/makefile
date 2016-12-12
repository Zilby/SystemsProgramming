all: server.o client.o
	gcc -o server server.o 
	gcc -o client client.o

server.o: server.c fserver.h
	gcc -c server.c 

client.o: client.c fserver.h
	gcc -c client.c

clean: 
	rm *o
	rm ./run
