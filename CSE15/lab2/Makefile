#---------------------------------------------------
# Makefile for charType.c with macros
#---------------------------------------------------
#
# Name:Kuo-Peng Huang
# UCSC ID:khuang53
# Class:CSE15
# Role:Makefile for lab2
# Assignment:Lab2
# Date:Oct 21,2019
#

ASSIGNMENT = lab2
EXEBIN = charType
SOURCES = charType.c
OBJECTS = charType.o
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
	ls  /afs/cats.ucsc.edu/class/cse015-pt.f19/lab2/khuang53

memcheck:
	$ valgrind --leak-check=full charType infile outfile
