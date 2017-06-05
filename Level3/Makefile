#
#             Author: Michael Marven
#       Date Created: 05/30/17
# Date Last Modified: 06/04/17
#            Purpose: Linux Makefile for KnightGraph class and test program
#
#

CC=g++
DEBUG=-g
WARN=-Wall
CFLAGS=$(DEBUG) $(WARN)
PROGS=sptest

all: $(PROGS)

sptest : sptest.o KnightGraph.o MoveValidator.o
	$(CC) $(CFLAGS) KnightGraph.o sptest.o MoveValidator.o -o sptest
    
KnightGraph.o : KnightGraph.cpp KnightGraph.h MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x KnightGraph.cpp

MoveValidator.o : MoveValidator.cpp MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x MoveValidator.cpp

sptest.o : sptest.cpp KnightGraph.h MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x sptest.cpp
    
clean:
	rm -rf *.o $(PROGS)
