all: control.o mainc.o write.o mainw.o
	gcc -o control control.o mainc.o
	gcc -o write write.o mainw.o

write.o: write.c semaphone.h
	gcc -c write.c

control.o: control.c semaphone.h
	gcc -c control.c

mainc.o: mainc.c semaphone.h
	gcc -c mainc.c

mainw.o: mainw.c semaphone.h
	gcc -c mainw.c

clean: 
	rm *o
	rm ./control
	rm ./write
