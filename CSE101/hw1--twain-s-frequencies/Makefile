#Makefile for twain.c
CC = gcc
OBJ = List.o, twain.o

List.o: List.c List.h
	$(CC) -c List.c

twain.o: twain.c List.h 
	$(CC) -c twain.c

twain: $(OBJ)
	$(CC) -o $(OBJ)
