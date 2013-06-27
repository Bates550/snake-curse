CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lncurses
SOURCES=main.cpp Snake.cpp SnakePiece.cpp Food.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=snake

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE):$(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
