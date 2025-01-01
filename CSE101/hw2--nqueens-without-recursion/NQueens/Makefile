#Homework 2 Makefile

nqueens : nQueens.o
	g++ -g -o nqueens nQueens.o
	
nQueens.o : nQueens.cpp
	g++ -g -c -Wall nQueens.cpp

clean : nQueens.o nqueens
	rm -f nQueens.o nqueens

