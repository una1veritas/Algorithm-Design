CC = gcc -std=c11
CXX = g++ -std=c++17

CFLAGS = -O2 -g -Wall -fmessage-length=0
CPPFLAGS = -O2 -g -Wall

INCLUDES =

TARGET = kruskal.exe
OBJS = Graph_algorithms.o SimpleGraph.o UnionFind.o kruskal.o
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
