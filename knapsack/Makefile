CC = gcc 
CXX = g++ 

OBJS =		knapsack.o main.o
INCS = 		knapsack.h
LIBS =

TARGET =	knapsack.exe

CXXFLAGS =	-O0 -g -Wall -fmessage-length=0
#CCFLAGS = -O2 -Wall
CCFLAGS = -O0 -g -Wall


%.o:%.c $(INCLUDES)
	$(CC) -c $(CCFLAGS) $<

%.o:%.cpp $(INCLUDES)
	$(CXX) -c $(CXXFLAGS) $<
	
$(TARGET):	$(OBJS)
	$(CC) $(CCFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
