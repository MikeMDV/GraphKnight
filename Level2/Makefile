#
#             Author: Michael Marven
#       Date Created: 05/30/17
# Date Last Modified: 05/30/17
#            Purpose: Linux Makefile for KnightGraph class and test program
#
#

CC=g++
DEBUG=-g
CFLAGS=$(DEBUG)
PROGS=kgtest

all: $(PROGS)

kgtest : kgtest.o knightgraph.o
	$(CC) -g knightgraph.o kgtest.o -o kgtest
    
knightgraph.o : KnightGraph.cpp KnightGraph.h CommonDefs.h
	$(CC) -g -c -std=c++0x KnightGraph.cpp

kgtest.o : kgtest.cpp KnightGraph.h MoveValidator.h CommonDefs.h
	$(CC) -g -c -std=c++0x kgtest.cpp
    
clean:
	rm -rf *.o $(PROGS)