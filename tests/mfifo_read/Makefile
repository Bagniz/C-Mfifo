GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: mfile.o read.o
	$(GCC) $(WALL) $(G) read.o mfile.o $(O) read $(LRT) $(PTHREAD)
	make clear

read.o: read.c
	$(GCC) $(WALL) $(G) $(C) read.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o