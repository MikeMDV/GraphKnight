#
#             Author: Michael Marven
#       Date Created: 05/30/17
# Date Last Modified: 06/03/17
#            Purpose: Linux Makefile for KnightGraph class and test program
#
#

CC=g++
DEBUG=-g
WARN=-Wall
CFLAGS=$(DEBUG) $(WARN)
PROGS=sptest

all: $(PROGS)

sptest : sptest.o knightgraph.o movevalidator.o
	$(CC) $(CFLAGS) knightgraph.o sptest.o movevalidator.o -o sptest
    
knightgraph.o : KnightGraph.cpp KnightGraph.h MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x KnightGraph.cpp

movevalidator.o : MoveValidator.cpp MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x MoveValidator.cpp

sptest.o : sptest.cpp KnightGraph.h MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x sptest.cpp
    
clean:
	rm -rf *.o $(PROGS)