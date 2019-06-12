CC = 	gcc 
CXX = 	g++ 

OBJS =		knapsack.o main.o
INCS = 		knapsack.h
LIBS =
SRC  =  ./src

TARGET =	knapsack.exe

CXX +=	-O0 -g -Wall -fmessage-length=0
CC  += 	-O0 -g -Wall


%.o: $(SRC)/%.c $(INCLUDES)
	$(CC)  -c $<

%.o: $(SRC)/%.cpp $(INCLUDES)
	$(CXX) -c $<
	
$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
