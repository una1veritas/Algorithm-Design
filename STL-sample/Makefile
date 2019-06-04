CC = gcc  
CXX = g++ -std=c++11

CXX += -O0 -g -Wall
INCDIRS = -I./
SRCDIR = ./src/

OBJS = STL-sample.o
INCLUDES =  
LIBS = 

%.o: $(SRCDIR)%.c $(INCLUDES)
	$(CC) -c $(INCLIDRS) $<

%.o: $(SRCDIR)%.cpp $(INCLUDES)
	$(CXX) -c $(INCLIDRS) $<

all: STL-sample.exe

STL-sample.exe: $(OBJS) 
	$(CXX) -o STL-sample.exe $(OBJS)


clean:
	\rm -f *.o *~ *.exe