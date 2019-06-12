CC = gcc
CXX = g++

OBJS =	main.o sortalgorithms.o stopwatch.o
LIBS = 
INCDIRS = -I./src/

CC +=  -O2 -g -Wall
CXX +=  -O -g -Wall -fmessage-length=0

%.o: ./src/%.c $(INCLUDES)
	$(CC) -c $(INCLIDRS) $<

%.o:%.cpp $(INCLUDES)
	$(CXX) -c $(INCLIDRS) $<

TARGET =	sortalgorithms.exe

$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

