PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = C++split.o

CFLAGS += -std=c++2a
ifeq ($(BUILD_MODE),debug)
	CFLAGS += -g
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -O2
else ifeq ($(BUILD_MODE),linuxtools)
	CFLAGS += -g -pg -fprofile-arcs -ftest-coverage
	LDFLAGS += -pg -fprofile-arcs -ftest-coverage
	EXTRA_CLEAN += C++split.gcda C++split.gcno $(PROJECT_ROOT)gmon.out
	EXTRA_CMDS = rm -rf C++split.gcda
else
    $(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

all:	C++split

C++split:	$(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^
	$(EXTRA_CMDS)

%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr C++split $(OBJS) $(EXTRA_CLEAN)
