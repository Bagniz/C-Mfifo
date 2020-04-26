GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: create delete
	make clear

delete: mfile.o delete_mfifo.o
	$(GCC) $(WALL) $(G) mfile.o delete_mfifo.o $(O) delete $(LRT) $(PTHREAD)

delete_mfifo.o: delete_mfifo.c
	$(GCC) $(WALL) $(G) $(C) delete_mfifo.c

create: mfile.o create_mfifo.o
	$(GCC) $(WALL) $(G) mfile.o create_mfifo.o $(O) create $(LRT) $(PTHREAD)

create_mfifo.o: create_mfifo.c
	$(GCC) $(WALL) $(G) $(C) create_mfifo.c

mfile.o: ../src/mfile.c ../src/mfile.h
	$(GCC) $(WALL) $(G) $(C) ../src/mfile.c

clear:
	rm *.o

clean:
	rm create
	rm delete