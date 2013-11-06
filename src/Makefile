CC=g++
CFLAGS=-c -std=c++0x -pedantic -Wall -Wextra -D_GLIBCXX_DEBUG -g
LDFLAGS=
SOURCES=MapBlock.cc Map.cc Walker.cc main.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=minebombers

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
