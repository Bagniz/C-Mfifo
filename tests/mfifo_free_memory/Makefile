GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: mfile.o free_memory.o
	$(GCC) $(WALL) $(G) free_memory.o mfile.o $(O) free_memory $(LRT) $(PTHREAD)
	make clear
	echo 'Free_Memory Compilation Succeed'
	
free_memory.o: free_memory.c
	$(GCC) $(WALL) $(G) $(C) free_memory.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o

clean:
	rm free_memory
	echo 'Free_Memory Clean Succeed'
