# Compiler
CC = gcc
#Linker
SOURCES = diner.c
#Debug
DEBUG = gdb
#Flags
CFLAGS = -ggdb -Wall
#Thread
THREAD = -lpthread


all:
	$(CC) $(SOURCES) $(CFLAGS) -o output.o $(THREAD)
debug: all
	$(DEBUG) output.o

clear:
	rm ./*.o
