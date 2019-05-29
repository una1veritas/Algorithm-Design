CC = gcc
CCFLAGS =  -O0 -g -Wall
CXX = g++
CXXFLAGS =  -std=c++11 -O0 -g -Wall -fmessage-length=0

PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = main.o LinkedList.o
INCLUDES = LinkedList.h

#ifeq ($(BUILD_MODE),debug)
#	CFLAGS += -g
#else ifeq ($(BUILD_MODE),run)
#	CFLAGS += -O2
#else
#	$(error Build mode $(BUILD_MODE) not supported by this Makefile)
#endif

all:	C++LinkedList

%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS)  -o $@ $<

C++LinkedList:	$(OBJS)
	$(CXX) -o $@ $^

clean:
	rm -fr C++LinkedList $(OBJS)
