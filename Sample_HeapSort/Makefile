
CC = 	gcc 
CXX =	g++ 

CC  += -O0 -g -Wall
CXX += -O0 -g -Wall -fmessage-length=0

OBJS =		main.o heapsort.o stdlib_qsort.o selectionsort.o
LIBS = 
INCDIRS = 
SRCDIR = 	./src/
TARGET = 	sample_heap.exe

%.o: $(SRCDIR)%.c $(INCLUDES)
	$(CC) -c $(INCLIDRS) $<

%.o: $(SRCDIR)%.cpp $(INCLUDES)
	$(CXX) -c $(INCLIDRS) $<

$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all:	sample_heap.exe

clean:
	rm -f $(OBJS) $(TARGET)

