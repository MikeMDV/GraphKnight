#
#             Author: Michael Marven
#       Date Created: 05/26/17
# Date Last Modified: 06/03/17
#            Purpose: Linux Makefile for MoveValidator class and test program
#
#

CC=g++
DEBUG=-g
WARN=-Wall
CFLAGS=$(DEBUG) $(WARN)
PROGS=mvtest

all: $(PROGS)

mvtest : mvtest.o MoveValidator.o
	$(CC) $(CFLAGS) MoveValidator.o mvtest.o -o mvtest
    
MoveValidator.o : MoveValidator.cpp MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x MoveValidator.cpp

mvtest.o : mvtest.cpp MoveValidator.h CommonDefs.h
	$(CC) $(CFLAGS) -c -std=c++0x mvtest.cpp
    
clean:
	rm -rf *.o $(PROGS)
