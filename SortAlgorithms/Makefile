
CC = /opt/local/bin/gcc 
CXX = /opt/local/bin/g++ 

CC += -O -g -Wall
CXX +=	-O2 -g -Wall -fmessage-length=0

OBJS =	main.o sortalgorithms.o stopwatch.o
LIBS = 
INCDIRS = -I./src/

%.o: ./src/%.c $(INCLUDES)
	$(CC) -c $(INCLIDRS) $<

%.o:%.cpp $(INCLUDES)
	$(CXX) -c $(INCLIDRS) $<

TARGET =	sortalgorithms.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

