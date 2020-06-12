CC = gcc
CXX = g++
CCFLAGS =  -O0 -g -Wall -I../C_LinkedList/
CXXFLAGS =  -std=c++11 -O0 -g -Wall -fmessage-length=0

#PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

SRCDIR = ./src/

#OBJS = hashtable.o llist.o
OBJS = level1.o
INCLUDES = llist.h
TARGET = level1.exe

#ifeq ($(BUILD_MODE),debug)
#	CFLAGS += -g
#else ifeq ($(BUILD_MODE),run)
#	CFLAGS += -O2
#else
#	$(error Build mode $(BUILD_MODE) not supported by this Makefile)
#endif

all:	$(TARGET)

llist.o: ../C_LinkedList/llist.c
	$(CC) -c $(CCFLAGS) -o $@ $<


%.o:	$(SRCDIR)%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

%.o:	$(SRCDIR)%.c
	$(CC) -c $(CCFLAGS) -o $@ $<

$(TARGET):	$(OBJS)
	$(CXX) -o $@ $^

clean:
	rm -fr $(TARGET) $(OBJS)
