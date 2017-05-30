#
#             Author: Michael Marven
#       Date Created: 05/26/17
# Date Last Modified: 05/26/17
#            Purpose: Linux Makefile for MoveValidator class and test program
#
#

CC=g++
DEBUG=-g
CFLAGS=$(DEBUG)
PROGS=mvtest

all: $(PROGS)

mvtest : mvtest.o movevalidator.o
	$(CC) -g movevalidator.o mvtest.o -o mvtest
    
movevalidator.o : MoveValidator.cpp MoveValidator.h CommonDefs.h
	$(CC) -g -c -std=c++0x MoveValidator.cpp

mvtest.o : mvtest.cpp MoveValidator.h CommonDefs.h
	$(CC) -g -c -std=c++0x mvtest.cpp
    
clean:
	rm -rf *.o $(PROGS)