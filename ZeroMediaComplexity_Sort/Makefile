CC = gcc  -g #-DSTATUS_PRINT_STDOUT
CXX = g++  -g

OBJS = zmsort_algorithms.o mt19937ar.o main.o
INCLUDES = sort_algorithms.h 
LIBS = 
INCDIRS = -I./

TARGET =

%.o:%.c $(INCLUDES)
	$(CC) -c $(INCLIDRS) $<

%.o:%.cpp $(INCLUDES)
	$(CXX) -c $(INCLIDRS) $<
	

#$(TARGET):	$(OBJS)
#	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all: zmsort

zmsort: $(OBJS) 
	$(CC) -o zmsort.exe $(OBJS)


clean:
	\rm -f *.o *~ *.exe