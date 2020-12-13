CC = gcc -std=c11
CXX = g++ -std=c++17

CFLAGS = -O0 -g -Wall -fmessage-length=0
CPPFLAGS = -O0 -g -Wall

INCLUDES =

TARGET = kruskal.exe
OBJS = kruskal.o
LIBS = 

%.o:	%.c $(INCLUDES)
	$(CC) -c $(CFLAGS) -c $<

%.o:	%.cpp $(INCLUDES)
	$(CXX) -c $(CPPFLAGS) -c $<

$(TARGET): 	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
