CC=g++
CFLAGS=-c -std=c++0x -pedantic -Wall -Wextra -D_GLIBCXX_DEBUG -g
LDFLAGS= 
SFML=-L./lib/ -l:libsfml-audio.so.2 -l:libsfml-graphics.so.2 -l:libsfml-window.so.2 -l:libsfml-system.so.2 -l:libsfml-network.so.2
SFML_ALT=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
DIRS=-I .
SOURCES=\
Direction.cc\
PlayerInterface.cc\
MapBlock.cc\
Map.cc\
Walker.cc\
Actor.cc\
AIActor.cc\
ControlledActor.cc\
Player.cc\
Item.cc\
Inventory.cc\
Store.cc\
StoreInterface.cc\
Game.cc\
GraphicsManager.cc\
EventManager.cc\
WindowManager.cc\
AnimatedSprite.cc\
Animation.cc\
AStar.cc\
GlobalGameInterface.cc\
Terrain.cc\
MapObjectManager.cc\
GameState.cc\
World.cc\
SinglePlayerGame.cc\
WorldGUI.cc\
MapUtils.cc\
MultiplayerGame.cc\
AIPlayerSeeker.cc\
Enemies.cc\
Fixtures.cc\
CampaignGame.cc\
CampaignGameWorld.cc\
campaign/moonbase.cc\
campaign/tunnels.cc\
campaign/caverns.cc\
campaign/boss.cc\
MenuInterface.cc\
Menu.cc\
MainMenu.cc\
SinglePlayerMenu.cc
MAIN=main.cc
RPATH=-Wl,-rpath=./lib/
TESTS=WalkerTest.cc DirectionTest.cc ActorTest.cc ControlledActorTest.cc PlayerTest.cc MapTest.cc InventoryTest.cc AStarTest.cc testMain.cc TerrainTest.cc
TMP=$(SOURCES:.cc=.o)
SOURCES_O=$(TMP:.cpp=.o)
MAIN_O=$(MAIN:.cc=.o)
TESTS_O=$(TESTS:.cc=.o)
EXECUTABLE=minebombers
TEST_EXECUTABLE=tests

all: $(SOURCES) $(MAIN) $(EXECUTABLE)
$(EXECUTABLE): $(SOURCES_O) $(MAIN_O)
	$(CC) $(SOURCES_O) $(MAIN_O) $(LDFLAGS) -o $@ $(SFML) $(RPATH)

alt: $(SOURCES) $(MAIN) $(EXECUTABLE)alt
$(EXECUTABLE)alt: $(SOURCES_O) $(MAIN_O)
	$(CC) $(SOURCES_O) $(MAIN_O) $(LDFLAGS) -o $(EXECUTABLE) $(SFML_ALT)

%.o: %.cc
	$(CC) $(DIRS) $(CFLAGS) $< -o $@

clean:
	rm -f $(SOURCES_O) $(TESTS_O) $(MAIN_O) $(EXECUTABLE) $(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(SOURCES_O) $(TESTS_O)
	$(CC) $(SOURCES_O) $(TESTS_O) $(LDFLAGS) -o $@ $(SFML) $(RPATH)

alt$(TEST_EXECUTABLE): $(SOURCES_O) $(TESTS_O)
	$(CC) $(SOURCES_O) $(TESTS_O) $(LDFLAGS) -o $(TEST_EXECUTABLE) $(SFML_ALT)

redo:
	make clean
	make

realt:
	make clean
	make alt

redo_t:
	make clean
	make tests

realtt:
	make clean
	make alttests

echo:
	$(SOURCES_O)
