GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: mfile.o trywrite.o
	$(GCC) $(WALL) $(G) trywrite.o mfile.o $(O) trywrite $(LRT) $(PTHREAD)
	make clear

trywrite.o: trywrite.c
	$(GCC) $(WALL) $(G) $(C) trywrite.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o