CC = gcc -O2 -g
CXX = g++ -O2 -g

OBJS = knapsack.o
LIBS = 
INCDIRS = -I./

TARGET =

%.o:%.c $(INCLUDES)
	$(CC) -c $(INCLIDRS) $<

%.o:%.cpp $(INCLUDES)
	$(CXX) -c $(INCLIDRS) $<
	

#$(TARGET):	$(OBJS)
#	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all: knapsack

knapsack: $(OBJS)
	$(CXX) -o knapsack $(OBJS)

subsetenum: 	subsetenum.o
	$(CC) -o subsetenum subsetenum.c

clean:
	\rm -f *.o 