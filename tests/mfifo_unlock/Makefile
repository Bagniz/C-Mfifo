GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: mfile.o unlock.o
	$(GCC) $(WALL) $(G) unlock.o mfile.o $(O) unlock $(LRT) $(PTHREAD)
	make clear

unlock.o: unlock.c
	$(GCC) $(WALL) $(G) $(C) unlock.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o