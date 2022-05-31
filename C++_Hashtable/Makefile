PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS =  C++11_unordered_map.o

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -g -std=c++11
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -O2 -std=c++11
else ifeq ($(BUILD_MODE),linuxtools)
	CFLAGS += -g -pg -fprofile-arcs -ftest-coverage  -std=c++11
	LDFLAGS += -pg -fprofile-arcs -ftest-coverage
	EXTRA_CLEAN += C++_Hashtable.gcda C++_Hashtable.gcno $(PROJECT_ROOT)gmon.out
	EXTRA_CMDS = rm -rf C++_Hashtable.gcda
else
    $(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

all:	C++_Hashtable

C++_Hashtable:	$(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^
	$(EXTRA_CMDS)

%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr C++_Hashtable $(OBJS) $(EXTRA_CLEAN)
