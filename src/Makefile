CC=g++
CFLAGS=-c -std=c++0x -pedantic -Wall -Wextra -D_GLIBCXX_DEBUG -g
LDFLAGS=
SOURCES=Direction.cc MapBlock.cc Map.cc Walker.cc Actor.cc ControlledActor.cc Player.cc Item.cc Inventory.cc main.cc
TEST_SOURCES=Direction.cc MapBlock.cc Map.cc Item.cc Walker.cc Actor.cc ControlledActor.cc Player.cc Inventory.cc WalkerTest.cc DirectionTest.cc ActorTest.cc ControlledActorTest.cc PlayerTest.cc MapTest.cc InventoryTest.cc testMain.cc
OBJECTS=$(SOURCES:.cc=.o)
TEST_OBJECTS=$(TEST_SOURCES:.cc=.o)
EXECUTABLE=minebombers
TEST_EXECUTABLE=tests

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(EXECUTABLE) tests

tests: $(TEST_SOURCES) $(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CC) $(TEST_OBJECTS) $(LDFLAGS) -o $@
