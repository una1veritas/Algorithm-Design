CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		jd.o

LIBS =

TARGET =	jd

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
