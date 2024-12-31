#---------------------------------------------------
# Makefile for sortString.c with macros
#---------------------------------------------------
#
# Name:Kuo-Peng Huang
# UCSC ID:khuang53
# Class:CSE15
# Role:Makefile for lab5
# Assignment:Lab5
# Date:Dec 5th,2019
#

ASSIGNMENT = lab5
EXEBIN = SortString
SOURCES = $(EXEBIN).c
OBJECTS = $(EXEBIN).o
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
	ls  /afs/cats.ucsc.edu/class/cse015-pt.f19/lab5/khuang53

memcheck:
	$ valgrind --leak-check=full SortString input output
