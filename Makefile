GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all:  mfile.o mfifo.o
	$(GCC) $(WALL) $(G) mfile.o mfifo.o $(O) mfifo $(LRT) $(PTHREAD)
	make clear

mfifo.o: mfifo.c
	$(GCC) $(WALL) $(G) $(C) mfifo.c
	
mfile.o: mfile.c mfile.h
	$(GCC) $(WALL) $(G) $(C) mfile.c

clear:
	rm *.o
