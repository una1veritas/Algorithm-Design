CC = gcc -std=c11
CXX = g++ -std=c++17

CFLAGS = -O2 -g -Wall -fmessage-length=0
CPPFLAGS = -O2 -g -Wall

INCLUDES =

TARGET = kruskal
OBJS = simplegraph.o UnionFind.o Dijkstra.o Kruskal.o
LIBS = 

%.o:	%.c $(INCLUDES)
	$(CC) -c $(CFLAGS) -c $<

%.o:	%.cpp $(INCLUDES)
	$(CXX) -c $(CPPFLAGS) -c $<

kruskal: 	main_Kruskal.o $(OBJS)
	$(CC) -o kruskal.exe main_Kruskal.o $(OBJS) $(LIBS)

dijkstra: 	main_Dijkstra.o $(OBJS)
	$(CC) -o dijkstra.exe main_Dijkstra.o $(OBJS) $(LIBS)

all:	kruskal dijkstra

clean:
	rm -f $(OBJS) kruskal.exe dijkstra.exe
