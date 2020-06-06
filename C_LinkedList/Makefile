CC = gcc 
CXX = g++
CCFLAGS = -O0 -g -Wall
CXXFLAGS =  -std=c++11 -O0 -g -Wall -fmessage-length=0

#PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

TARGET = llist.exe
OBJS = main.o llist.o
INCLUDES = 

#ifeq ($(BUILD_MODE),debug)
#	CFLAGS += -g
#else ifeq ($(BUILD_MODE),run)
#	CFLAGS += -O2
#else
#	$(error Build mode $(BUILD_MODE) not supported by this Makefile)
#endif

all:	$(TARGET)

%.o:	%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

%.o:	%.c
	$(CC) -c $(CCFLAGS)  -o $@ $<

$(TARGET):	$(OBJS)
	$(CXX) -o $@ $^

clean:
	rm -fr $(TARGET) $(OBJS) *~
	rm -rf Debug Default
