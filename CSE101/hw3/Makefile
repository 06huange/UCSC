CXX = g++
CXXFLAGS = -Wall

OBJECTS = BST.o wordrange.o
all: wordrange check

check: check.o
	$(CXX) -g $(CXXFLAGS) -o check check.o

wordrange: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o wordrange BST.o wordrange.o

BST.o: BST.cpp BST.h
	$(CXX) -g $(CXXFLAGS) -c BST.cpp
	
wordrange.o: BST.cpp BST.h wordrange.cpp
	$(CXX) -g $(CXXFLAGS) -c wordrange.cpp

check.o: check.cpp
	$(CXX) -g $(CXXFLAGS) -c check.cpp

clean: 
	rm -f *.o
	rm wordrange
	rm check
	