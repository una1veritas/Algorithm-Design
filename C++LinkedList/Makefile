CC = gcc
CXX = g++
CCFLAGS =  -O0 -g -Wall
CXXFLAGS =  -std=c++11 -O0 -g -Wall -fmessage-length=0

#PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = main.o LinkedList.o
INCLUDES = LinkedList.h

#ifeq ($(BUILD_MODE),debug)
#	CFLAGS += -g
#else ifeq ($(BUILD_MODE),run)
#	CFLAGS += -O2
#else
#	$(error Build mode $(BUILD_MODE) not supported by this Makefile)
#endif

all:	C++LinkedList.exe

%.o:	%.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	%.c
	$(CC) -c $(CFLAGS)  -o $@ $<

C++LinkedList.exe:	$(OBJS)
	$(CXX) -o $@ $^

clean:
	rm -fr C++LinkedList.exe $(OBJS)
