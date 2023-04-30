CC = 	gcc -std=c11 -O1
CXX = 	g++ -std=c++2a -O1

OBJS =		main.o
INCS = 		
LIBS =
SRC  =  

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
