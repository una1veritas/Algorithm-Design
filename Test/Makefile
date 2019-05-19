CXXFLAGS =	-O0 -g -Wall -fmessage-length=0

OBJS =		Test.o

LIBS =

TARGET =	Test.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
