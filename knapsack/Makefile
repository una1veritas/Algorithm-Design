CC = 	gcc 
CXX = 	g++ -std=c1y

OBJS =		knapsack.o main.o
INCS = 		
LIBS =
SRC  =  ./src

TARGET =	knapsack.exe

CXX +=	-O0 -g -Wall -fmessage-length=0
CC  += 	-O0 -g -Wall


%.o: $(SRC)/%.c $(INCS)
	$(CC)  -c $<

%.o: $(SRC)/%.cpp $(INCS)
	$(CXX) -c $<
	
$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
