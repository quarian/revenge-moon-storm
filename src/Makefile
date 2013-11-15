CC=g++
CFLAGS=-c -std=c++0x -pedantic -Wall -Wextra -D_GLIBCXX_DEBUG -g
SFMLLINKS=-lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS=
SOURCES=Direction.cc MapBlock.cc Map.cc Walker.cc Actor.cc ControlledActor.cc Player.cc Item.cc Inventory.cc Game.cc GraphicsManager.cc EventManager.cc WindowManager.cc AnimatedSprite.cc Animation.cc
MAIN=main.cc
TESTS=WalkerTest.cc DirectionTest.cc ActorTest.cc ControlledActorTest.cc PlayerTest.cc MapTest.cc InventoryTest.cc GameTest.cc testMain.cc
TMP=$(SOURCES:.cc=.o)
SOURCES_O=$(TMP:.cpp=.o)
MAIN_O=$(MAIN:.cc=.o)
TESTS_O=$(TESTS:.cc=.o)
EXECUTABLE=minebombers
TEST_EXECUTABLE=tests

all: $(SOURCES) $(MAIN) $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES_O) $(MAIN_O)
	$(CC) $(SOURCES_O) $(MAIN_O) $(LDFLAGS) -o $@ $(SFMLLINKS)

%.o: %.cc
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(SOURCES_O) $(TESTS_O) $(MAIN_O) $(EXECUTABLE) $(TESTS_EXECUTABLE)

$(TEST_EXECUTABLE): $(SOURCES_O) $(TESTS_O)
	$(CC) $(SOURCES_O) $(TESTS_O) $(LDFLAGS) -o $@ $(SFMLLINKS)

redo:
	make clean
	make

redo_t:
	make clean
	make tests

echo:
	$(SOURCES_O)
