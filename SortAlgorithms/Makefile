CC = gcc
CXX = g++

#OBJS =	test.o
OBJS =	insertion_sort.o heap_sort.o selection_sort.o counting_sort.o main_test.o
#OBJS =	bucketsort.o llist.o 
LIBS = 
INCLUDES = ../C_LinkedList/llist.h 
INCDIRS = -I./src/ -I../C_LinkedList/

CC += -O0 -g -Wall $(INCDIRS) 
CXX +=	-O0 -g -Wall -fmessage-length=0


%.o:./src/%.c $(INCLUDES)
	$(CC) -c $<

%.o:%.cpp $(INCLUDES)
	$(CXX) -c $<

llist.o:../C_LinkedList/llist.c $(INCLUDES)
	$(CC) -c $<

#TARGET =	countingsort.exe
TARGET =	test.exe
#TARGET =	libcqsort.exe
#TARGET =	sortalgorithms.exe

$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)
#all:	selection_asm


selection_asm:
	gcc -O0 -S ./src/selection.c
	gcc -O0 -o selection.exe ./src/selection.c

test_strsort:
	$(CC) -o test_strsort.exe test_strsort.c
	
clean:
	rm -f $(OBJS) $(TARGET) *.exe *.o a.out

