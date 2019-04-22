CC = gcc -O2 -g -DPRINT_COMBINATION
CXX = g++ -O2 -g

OBJS = knapsack.o main.o
LIBS = 
INCDIRS = -I./

TARGET =

%.o:%.c $(INCLUDES)
	$(CC) -c $(INCLIDRS) $<

%.o:%.cpp $(INCLUDES)
	$(CXX) -c $(INCLIDRS) $<
	

#$(TARGET):	$(OBJS)
#	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all: knapsack_p

knapsack: $(OBJS)
	$(CC) -o knapsack.exe $(OBJS)

knapsack_p: $(OBJS)
	$(CC) -o knapsack.exe $(OBJS)

subsetenum: subsetenum.o
	$(CC) -o subsetenum.exe subsetenum.c

clean:
	\rm -f *.o *.exe