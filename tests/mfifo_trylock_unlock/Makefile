GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: mfile.o trylock_unlock.o
	$(GCC) $(WALL) $(G) trylock_unlock.o mfile.o $(O) trylock_unlock $(LRT) $(PTHREAD)
	make clear
	echo 'Trylock_Unlock Compilation Succeed'
	
trylock_unlock.o: trylock_unlock.c
	$(GCC) $(WALL) $(G) $(C) trylock_unlock.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o

clean:
	rm trylock_unlock
	echo 'Trylock_Unlock Clean Succeed'
