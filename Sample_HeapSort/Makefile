CC = gcc -O0 -g -Wall
CXX =	gxx -O0 -g -Wall -fmessage-length=0

OBJS =	main.o
LIBS = 
INCDIRS = 

%.o: %.c $(INCLUDES)
	$(CC) -c $(INCLIDRS) $<

%.o: %.cpp $(INCLUDES)
	$(CXX) -c $(INCLIDRS) $<

sample_heap.exe:	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all:	sample_heap.exe

clean:
	rm -f $(OBJS) $(TARGET)

