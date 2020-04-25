GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: mfile.o unlink.o
	$(GCC) $(WALL) $(G) unlink.o mfile.o $(O) unlink $(LRT) $(PTHREAD)
	make clear

unlink.o: unlink.c
	$(GCC) $(WALL) $(G) $(C) unlink.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o