#
#             Author: Michael Marven
#       Date Created: 05/30/17
# Date Last Modified: 06/30/17
#            Purpose: Linux Makefile for KnightGraph class and test program
#
#

CC=g++
DEBUG=-g
WARN=-Wall
CFLAGS=$(DEBUG) $(WARN)
PROGS=lptest

all: $(PROGS)

lptest : lptest.o KnightGraph.o MoveValidator.o
	$(CC) $(CFLAGS) KnightGraph.o lptest.o MoveValidator.o -o lptest
    
KnightGraph.o : KnightGraph.cpp KnightGraph.h MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x KnightGraph.cpp

MoveValidator.o : MoveValidator.cpp MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x MoveValidator.cpp

lptest.o : lptest.cpp KnightGraph.h MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x lptest.cpp
    
clean:
	rm -rf *.o $(PROGS)
