CC = gcc
CXX = g++
CCFLAGS =  -O0 -g -Wall
CXXFLAGS =  -std=c++11 -O0 -g -Wall -fmessage-length=0

#PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

SRCDIR = src/

OBJS = Hashtable.o LinkedList.o
INCLUDES = LinkedList.h
TARGET = Hashtable.exe

#ifeq ($(BUILD_MODE),debug)
#	CFLAGS += -g
#else ifeq ($(BUILD_MODE),run)
#	CFLAGS += -O2
#else
#	$(error Build mode $(BUILD_MODE) not supported by this Makefile)
#endif

all:	$(TARGET)

%.o:	$(SRCDIR)%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

%.o:	$(SRCDIR)%.c
	$(CC) -c $(CFLAGS)  -o $@ $<

$(TARGET):	$(OBJS)
	$(CXX) -o $@ $^

clean:
	rm -fr $(TARGET) $(OBJS)
