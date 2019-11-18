PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = lcs.o gpspoint.o
HEADERS = gpspoint.h

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -std=c++11 -g
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -std=c++11 -O2
else 
	CFLAGS += -std=c++11 -g -Wall
#	$(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

all:	lcs test

test:   test.o gpspoint.o
	$(CXX) -o $@ $^

lcs:	$(OBJS)
	$(CXX) -o $@ $^

#gpspoint.o:	gpspoint.h 
#	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<


%.o:	$(PROJECT_ROOT)%.cpp 
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c 
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr lcs $(OBJS) test test.o
