GCC=gcc
WALL=-Wall
G=-g
O=-o
C=-c
LRT=-lrt
PTHREAD=-pthread

.SILENT:
all: creator writer reader 
	make clear

creator:  mfile.o creator.o
	$(GCC) $(WALL) $(G) mfile.o creator.o $(O) creator $(LRT) $(PTHREAD)

creator.o: creator.c
	$(GCC) $(WALL) $(G) $(C) creator.c

writer:  mfile.o writer.o
	$(GCC) $(WALL) $(G) mfile.o writer.o $(O) writer $(LRT) $(PTHREAD)

writer.o: writer.c
	$(GCC) $(WALL) $(G) $(C) writer.c

reader:  mfile.o reader.o
	$(GCC) $(WALL) $(G) mfile.o reader.o $(O) reader $(LRT) $(PTHREAD)

reader.o: reader.c
	$(GCC) $(WALL) $(G) $(C) reader.c
	
mfile.o: mfile.c mfile.h
	$(GCC) $(WALL) $(G) $(C) mfile.c

clear:
	rm *.o
