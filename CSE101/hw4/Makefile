#Homework 4 Makefile


sixdegrees : sixdegrees.o graph.o
	g++ -std=c++11 -g -o sixdegrees sixdegrees.o graph.o
	
sixdegrees.o : sixdegrees.cpp
	g++ -std=c++11 -g -c -Wall sixdegrees.cpp

graph.o : graph.cpp
	g++ -std=c++11 -g -c -Wall graph.cpp
	
clean : sixdegrees.o sixdegrees
	rm -f sixdegrees.o sixdegrees

