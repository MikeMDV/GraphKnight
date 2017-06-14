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
PROGS=dasptest

all: $(PROGS)

dasptest : dasptest.o KnightGraph.o MoveValidator.o
	$(CC) $(CFLAGS) KnightGraph.o dasptest.o MoveValidator.o -o dasptest
    
KnightGraph.o : KnightGraph.cpp KnightGraph.h MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x KnightGraph.cpp

MoveValidator.o : MoveValidator.cpp MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x MoveValidator.cpp

dasptest.o : dasptest.cpp KnightGraph.h MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x dasptest.cpp
    
clean:
	rm -rf *.o $(PROGS)
