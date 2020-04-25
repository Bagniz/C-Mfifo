GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: mfile.o trylock.o
	$(GCC) $(WALL) $(G) trylock.o mfile.o $(O) trylock $(LRT) $(PTHREAD)
	make clear

trylock.o: trylock.c
	$(GCC) $(WALL) $(G) $(C) trylock.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o