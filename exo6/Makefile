# Compiler
CC = gcc
#Linker
SOURCES = palindrome.c
# Debug
DEBUG = gdb

all:
	$(CC) $(SOURCES) -ggdb -o output.o
debug: all
	$(DEBUG) output.o

clear:
	rm ./*.o