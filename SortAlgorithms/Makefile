CC = gcc
CXX = g++

OBJS =  datadef.o selection_sort.o heap_sort.o insertion_sort.o mergesort.o 
#OBJS =	insertion_sort.o heap_sort.o selection_sort.o counting_sort.o main_test.o
#OBJS += binsearch.o 
MAINOBJ = main.o
#MAINOBJ = test.o

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
TARGET =	sortalgs.exe
#TARGET =	test.exe
#TARGET =	libcqsort.exe
#TARGET =	sortalgorithms.exe

#$(TARGET):	$(OBJS)
#	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

sortalgs.exe: $(OBJS) $(MAINOBJ)
	$(CC) -o sortalgs.exe $(OBJS) $(MAINOBJ)

test.exe: $(MAINOBJ)
	$(CC) -o test.exe $(MAINOBJ)

main.o: ./src/main.c $(OBJS)
	$(CC) -c -o main.o ./src/main.c

all:	$(TARGET)
#all:	selection_asm


selection_asm:
	gcc -O2 -S ./src/selection_sort.c
	
clean:
	rm -f $(OBJS) $(MAINOBJ) $(TARGET) *.exe *.o a.out

