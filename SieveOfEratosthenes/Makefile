CC = 	gcc -std=c11
CXX = 	g++ -std=c1y

OBJS =		sieve.o 
INCS = 		
LIBS =
SRC  =  ./src

TARGET =	sieve.exe

CXX +=	-O2 -g -Wall -fmessage-length=0
CC  += 	-O2 -g -Wall


%.o: $(SRC)/%.c $(SRC)/$(INCS)
	$(CC)  -c $<

%.o: $(SRC)/%.cpp $(SRC)/$(INCS)
	$(CXX) -c $<
	
$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
