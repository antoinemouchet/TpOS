all:
	gcc PGCD.c -o output.o

debug: all
	gdb output.o 

clear:
	rm ./*.o