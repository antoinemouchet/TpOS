# Compiler
CC = gcc
#Linker
SOURCES = diner.c
#Debug
DEBUG = gdb
#Flags
CFLAGS = -ggdb -Wall -lpthread

all:
	$(CC) $(SOURCES) $(CFLAGS) -o output.o
debug: all
	$(DEBUG) output.o

clear:
	rm ./*.o
