
CC = gcc -O -g
CXX = g++ -O -g -std=c++11

CCFLAGS = -O -g -Wall
CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

LIBS = 
INCDIRS = -I./src/

#TARGET =	hanoi.exe
#OBJS =	TowerOfHanoi.o
#TARGET =	fibo.exe
#OBJS =	fibo.o
TARGET = gcd.exe
OBJS = gcd.o

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)


%.o: ./src/%.c $(INCLUDES)
	$(CC) -c $(INCLIDRS) $<

%.o: ./src/%.cpp $(INCLUDES)
	$(CXX) -c $(INCLIDRS) $<

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

