#---------------------------------------------------
# Makefile for ArithmeticOperations.c with macros
#---------------------------------------------------
#
# Name:Kuo-Peng Huang
# UCSC ID:khuang53
# Class:CSE15
# Role:Makefile for lab4
# Assignment:Lab4
# Date:Nov 21,2019
#

ASSIGNMENT = lab4
EXEBIN = ArithmeticOperations
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
	ls  /afs/cats.ucsc.edu/class/cse015-pt.f19/lab4/khuang53

memcheck:
	$ valgrind --leak-check=full $(EXEBIN) in1
