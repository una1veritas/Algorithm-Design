
CC = gcc -O -g
CXX = g++ -O -g

CCFLAGS = -O -g -Wall
CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =	TowerOfHanoi.o
LIBS = 
INCDIRS = -I./src/

%.o: ./src/%.c $(INCLUDES)
	$(CC) -c $(INCLIDRS) $<

%.o:%.cpp $(INCLUDES)
	$(CXX) -c $(INCLIDRS) $<

TARGET =	hanoi.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

