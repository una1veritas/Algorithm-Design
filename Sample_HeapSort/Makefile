CC = gcc -O0 -g -Wall
CXX =	gxx -O0 -g -Wall -fmessage-length=0

OBJS =	main.o
LIBS = 
INCDIRS = -I./src/

%.o: ./src/%.c $(INCLUDES)
	$(CC) -c $(INCLIDRS) $<

%.o:%.cpp $(INCLUDES)
	$(CXX) -c $(INCLIDRS) $<

TARGET =	sample_heap.exe

$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

