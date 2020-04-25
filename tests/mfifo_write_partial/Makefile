GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: mfile.o write_patial.o
	$(GCC) $(WALL) $(G) write_patial.o mfile.o $(O) write_patial $(LRT) $(PTHREAD)
	make clear

write_patial.o: write_patial.c
	$(GCC) $(WALL) $(G) $(C) write_patial.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o