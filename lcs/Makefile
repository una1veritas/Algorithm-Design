PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = lcs.o gpspoint.o
HEADERS = gpspoint.h

ifeq ($(BUILD_MODE),debug)
	CXXFLAGS += -std=c++11 -g
else ifeq ($(BUILD_MODE),run)
	CXXFLAGS += -std=c++11 -O2
else 
	CXXFLAGS += -std=c++11 -g -Wall
#	$(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

all:	lcs.exe

TESTOBJ = test.o

test.exe:   $(TESTOBJ)
	$(CXX) -o $@ $^

lcs.exe:	$(OBJS)
	$(CXX) -o $@ $^

#gpspoint.o:	gpspoint.h 
#	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<


%.o:	$(PROJECT_ROOT)%.cpp 
	$(CXX) -c $(CXXFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c 
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -fr lcs.exe test.exe $(OBJS) $(TESTOBJ)
