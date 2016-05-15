TARGET = VoteSystem
CC = g++
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
CFLAGS = -std=c++11
INCLUDE =
LFLAGS =
LIBS =


all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

clean:
	rm *.o
