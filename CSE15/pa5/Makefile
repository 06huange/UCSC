#------------------------------------------------------------------------------
# Makefile for any client of any ADT in C
# Name: Kuo-Peng Huang
# UCSC ID: khuang53
# Class: CSE15
# Assignment:pa5
# Date: Dec 6,2019
# Role: Makefile for pa5
#------------------------------------------------------------------------------

ASSIGNMENT     = pa5
CLIENT         = DictionaryTest
ADT            = Dictionary
SOURCE         = $(CLIENT).c
OBJECT         = $(CLIENT).o
ADT_SOURCE     = $(ADT).c
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full
SUBMIT 		   = submit cse015-pt.f19 $(ASSIGNMENT)
FILES          = $(SOURCE) $(ADT_SOURCE) Makefile README

$(CLIENT) : $(OBJECT) $(ADT_OBJECT) 
	$(LINK) $(CLIENT) $(OBJECT) $(ADT_OBJECT) 

$(OBJECT) : $(SOURCE) $(ADT_HEADER) 
	$(COMPILE) $(SOURCE)

$(ADT_OBJECT) : $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT_OBJECT) 

submit: $(FILES)
	$(SUBMIT) $(FILES)

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT)