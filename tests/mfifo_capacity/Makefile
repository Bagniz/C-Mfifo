GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: mfile.o capacity.o
	$(GCC) $(WALL) $(G) capacity.o mfile.o $(O) capacity $(LRT) $(PTHREAD)
	make clear

capacity.o: capacity.c
	$(GCC) $(WALL) $(G) $(C) capacity.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o

clean:
	rm capacity