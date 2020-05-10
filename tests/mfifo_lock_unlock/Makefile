GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: mfile.o lock_unlock.o
	$(GCC) $(WALL) $(G) lock_unlock.o mfile.o $(O) lock_unlock $(LRT) $(PTHREAD)
	make clear
	echo 'Lock_Unlock Compilation Succeed'
	
lock_unlock.o: lock_unlock.c
	$(GCC) $(WALL) $(G) $(C) lock_unlock.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o

clean:
	rm lock_unlock
	echo 'Lock_Unlock Clean Succeed'
