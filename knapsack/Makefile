CC = 	gcc -std=c11
CXX = 	g++ -std=c1y

OBJS =		knapsack.o main.o
INCS = 		knapsack.h
LIBS =
SRC  =  ./src

TARGET =	knapsack.exe

CXX +=	-O0 -g -Wall -fmessage-length=0
CC  += 	-O0 -g -Wall


%.o: $(SRC)/%.c $(SRC)/$(INCS)
	$(CC)  -c $<

%.o: $(SRC)/%.cpp $(SRC)/$(INCS)
	$(CXX) -c $<
	
$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
