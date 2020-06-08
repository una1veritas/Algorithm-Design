CC = gcc
CXX = g++

#OBJS =	main.o sortalgorithms.o stopwatch.o
#OBJS =	heapchecker.o
OBJS =	bucketsort.o llist.o
LIBS = 
INCLUDES = ../C_LinkedList/llist.h
INCDIRS = -I./src/ 
#INCDIRS = -I./src/ -I../C_LinkedList

CC += -O0 -g -Wall $(INCDIRS)
CXX +=	-O0 -g -Wall -fmessage-length=0


%.o:./src/%.c $(INCLUDES)
	$(CC) -c $<

%.o:%.cpp $(INCLUDES)
	$(CXX) -c $<

TARGET =	bucketsort.exe
#TARGET =	libcqsort.exe
#TARGET =	sortalgorithms.exe

$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)
#all:	selection_asm

#llist.o: ../C_LinkedList/llist.h
#	$(CC) -c ../C_LinkedList/llist.c

selection_asm:
	gcc -O0 -S ./src/selection.c
	gcc -O0 -o selection.exe ./src/selection.c

clean:
	rm -f $(OBJS) $(TARGET) *.exe *.o

