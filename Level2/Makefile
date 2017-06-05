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
PROGS=kgtest

all: $(PROGS)

kgtest : kgtest.o KnightGraph.o MoveValidator.o
	$(CC) $(CFLAGS) KnightGraph.o kgtest.o MoveValidator.o -o kgtest
    
KnightGraph.o : KnightGraph.cpp KnightGraph.h MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x KnightGraph.cpp

MoveValidator.o : MoveValidator.cpp MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x MoveValidator.cpp

kgtest.o : kgtest.cpp KnightGraph.h MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x kgtest.cpp
    
clean:
	rm -rf *.o $(PROGS)
