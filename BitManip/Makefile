CC = gcc 

OBJS = BitManip.o

CFLAGS = -O0 -g -Wall

all:	BitManip.exe

BitManip.exe:	$(OBJS)
	$(CXX) -o $@ $^

%.o:	%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	src/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr BitManip.exe $(OBJS)
