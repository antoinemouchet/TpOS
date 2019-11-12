# Compiler
CC = gcc
#Linker
SOURCES = tree.c
#Debug
DEBUG = gdb
#Flags
CFLAGS = -ggdb -Wall

all:
	$(CC) $(SOURCES) $(CFLAGS) -o output.o
debug: all
	$(DEBUG) output.o

clear:
	rm ./*.o
