
CC	= gcc -std=c99
CCFLAGS = -Wall -ggdb

CXX = g++ -std=c++11
CXXFLAGS = -Wall -ggdb

INCDIRS = -I./

INCLUDES = 
OBJS = cfft.o main.o
LIBS = 
TARGET = fftstrmatch.exe


%.o: %.c $(INCLUDES)
	$(CC) $(CCFLAGS) $(INCDIRS) -c $<

%.o: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c $<


$(TARGET):	$(OBJS) $(INCLUDES)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) *~
