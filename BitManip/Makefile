CC = gcc 

OBJS = BitManip.o

CFLAGS = -O0 -g -Wall

all:	BitManip

BitManip:	$(OBJS)
	$(CXX) -o $@ $^

%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr BitManip $(OBJS)
