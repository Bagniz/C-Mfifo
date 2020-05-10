GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: read write
	make clear
	echo 'Write_Partial_Read Compilation Succeed'
	
write: mfile.o write.o
	$(GCC) $(WALL) $(G) write.o mfile.o $(O) write $(LRT) $(PTHREAD)

write.o: write.c
	$(GCC) $(WALL) $(G) $(C) write.c

read: mfile.o read.o
	$(GCC) $(WALL) $(G) read.o mfile.o $(O) read $(LRT) $(PTHREAD)

read.o: read.c
	$(GCC) $(WALL) $(G) $(C) read.c

mfile.o: ../../src/mfile.c ../../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../../src/mfile.c

clear:
	rm *.o

clean:
	rm read
	rm write
	echo 'Write_Partial_Read Clean Succeed'
