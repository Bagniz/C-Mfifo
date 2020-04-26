GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: mfile.o disconnect.o
	$(GCC) $(WALL) $(G) disconnect.o mfile.o $(O) disconnect $(LRT) $(PTHREAD)
	make clear

disconnect.o: disconnect.c
	$(GCC) $(WALL) $(G) $(C) disconnect.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o

clean:
	rm disconnect