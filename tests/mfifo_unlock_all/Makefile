GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: mfile.o unlock_all.o
	$(GCC) $(WALL) $(G) unlock_all.o mfile.o $(O) unlock_all $(LRT) $(PTHREAD)
	make clear

unlock_all.o: unlock_all.c
	$(GCC) $(WALL) $(G) $(C) unlock_all.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o