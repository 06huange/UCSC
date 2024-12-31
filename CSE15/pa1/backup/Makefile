#---------------------------------------------------
# Makefile for Hello.c with macros
#---------------------------------------------------
#
# Name:Kuo-Peng Huang
# UCSC ID:khuang53
# Class:CSE15
# Role:Makefile for pa1
# Assignment:pa1
# Date:Oct 12,2019
#

ASSIGNMENT = pa1
EXEBIN = Subset
SOURCES = Subset.c
OBJECTS = Subset.o
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
	ls  /afs/cats.ucsc.edu/class/cse015-pt.f19/pa1/khuang53