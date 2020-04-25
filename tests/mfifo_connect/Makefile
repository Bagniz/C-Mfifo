GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: mfile.o connect.o
	$(GCC) $(WALL) $(G) connect.o mfile.o $(O) connect $(LRT) $(PTHREAD)
	make clear

connect.o: connect.c
	$(GCC) $(WALL) $(G) $(C) connect.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o