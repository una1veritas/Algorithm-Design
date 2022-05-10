CC = gcc
CXX = g++

OBJS =	main.o datadef.o selection_sort.o heap_sort.o insertion_sort.o
#OBJS =	insertion_sort.o heap_sort.o selection_sort.o counting_sort.o main_test.o
#OBJS = heap_sort.o
OBJS += binsearch.o 
LIBS = 
INCLUDES = ../C_LinkedList/llist.h 
INCDIRS = -I./src/ -I../C_LinkedList/

#CC += -O0 -g -Wall $(INCDIRS) 
CC += -O0 -g -Wall 
CXX +=	-O0 -g -Wall -fmessage-length=0


%.o:./src/%.c $(INCLUDES)
	$(CC) -c $<

%.o:%.cpp $(INCLUDES)
	$(CXX) -c $<

llist.o:../C_LinkedList/llist.c $(INCLUDES)
	$(CC) -c $<

#TARGET =	countingsort.exe
TARGET =	heapsort.exe
#TARGET =	libcqsort.exe
#TARGET =	sortalgorithms.exe

#$(TARGET):	$(OBJS)
#	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

heapsort.exe:$(OBJS)
	$(CC) -o heapsort.exe $(OBJS)

all:	$(TARGET)
#all:	selection_asm


selection_asm:
	gcc -O0 -S ./src/selection.c
	gcc -O0 -o selection.exe ./src/selection.c
	
clean:
	rm -f $(OBJS) $(TARGET) *.exe *.o a.out

