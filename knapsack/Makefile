CC = 	gcc -std=c11 -O2
CXX = 	g++ -std=c++2a -O2

OBJS =		main.o knapsack_allsubset.o knapsack_recursive.o knapsack_dp.o
INCS = 		
LIBS =
SRC  =  

TARGET =	knapsack.exe

CXX +=	-g -Wall -fmessage-length=0
CC  += 	-g -Wall


%.o: $(SRC)/%.c $(SRC)/$(INCS)
	$(CC)  -c $<

%.o: $(SRC)/%.cpp $(SRC)/$(INCS)
	$(CXX) -c $<
	
$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
