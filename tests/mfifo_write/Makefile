GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: mfile.o write.o
	$(GCC) $(WALL) $(G) write.o mfile.o $(O) write $(LRT) $(PTHREAD)
	make clear

write.o: write.c
	$(GCC) $(WALL) $(G) $(C) write.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o