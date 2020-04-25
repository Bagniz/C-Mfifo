GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: mfile.o lock.o
	$(GCC) $(WALL) $(G) lock.o mfile.o $(O) lock $(LRT) $(PTHREAD)
	make clear

lock.o: lock.c
	$(GCC) $(WALL) $(G) $(C) lock.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o