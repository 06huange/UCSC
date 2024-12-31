#---------------------------------------------------
# Makefile for Queens.c with macros
#---------------------------------------------------
#
# Name:Kuo-Peng Huang
# UCSC ID:khuang53
# Class:CSE15
# Role:Makefile for pa2
# Assignment:pa2
# Date:Oct 26,2019
#

ASSIGNMENT = pa2
EXEBIN = Queens
SOURCES = Queens.c
OBJECTS = Queens.o
FLAGS = -std=c99 -Wall
FILES = $(SOURCES) Makefile README
SUBMIT = submit cse015-pt.f19 $(ASSIGNMENT)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)

submit: $(FILES)
	$(SUBMIT) $(FILES)

check:
	ls  /afs/cats.ucsc.edu/class/cse015-pt.f19/pa2/khuang53

memcheck:
	$ valgrind --leak-check=full Queens -v 8
