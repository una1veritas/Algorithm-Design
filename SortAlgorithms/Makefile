CC = gcc
CXX = g++

CC += -O0 -g -Wall
CXX +=	-O0 -g -Wall -fmessage-length=0

#OBJS =	main.o sortalgorithms.o stopwatch.o
OBJS =	heapchecker.o
LIBS = 
INCDIRS = -I./src/

%.o: ./src/%.c $(INCLUDES)
	$(CC) -c $(INCLIDRS) $<

%.o:%.cpp $(INCLUDES)
	$(CXX) -c $(INCLIDRS) $<

TARGET =	heapchecker.exe
#TARGET =	libcqsort.exe
#TARGET =	sortalgorithms.exe

$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)
#all:	selection_asm

selection_asm:
	gcc -O0 -S ./src/selection.c
	gcc -O0 -o selection.exe ./src/selection.c

clean:
	rm -f $(OBJS) $(TARGET)

