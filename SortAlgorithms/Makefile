CC = gcc
CXX = g++ -std=c++11

CFLAGS = -Wall -O -g3
CXXFLAGS = -Wall -O -g3
INCLUDES = -I./src


%.o: ./src/%.c
	$(CC) $(CXXFLAGS) $(INCLUDES) -c $<

all: sortalgorithms.exe

nc++test.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

sortalgorithms.exe: main.o stopwatch.o sortalgorithms.o 
	$(CXX) $(CXXFLAGS) $(INCLUDES)  main.o stopwatch.o sortalgorithms.o -o $@

main.o: ./src/sortalgorithms.h
#	$(CXX) $(CXXFLAGS) $(INCLUDES) -c ./src/main.c
stopwatch.o: ./src/stopwatch.h
sortalgorithms.o: ./src/sortalgorithms.h

clean:
	rm -f *.exe *.o
