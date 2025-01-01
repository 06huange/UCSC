#Homework 1 Makefile

twain : twain.o List.o
	gcc -g -o twain twain.o List.o

twain.o : twain.c List.h
	gcc -g -c -std=c99 -Wall twain.c
    
List.o : List.c List.h
	gcc -g -c -std=c99 -Wall List.c 

clean : List.o twain.o twain
	rm -f List.o twain.o twain

