#ifndef MB2_MAP_HH
#define MB2_MAP_HH

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>

#include "Direction.hh"
#include "MapBlock.hh"
#include "Terrain.hh"
#include "Item.hh"
#include "Walker.hh"
//#include "Player.hh"

// Note that Map coordinates (0,0) are at the upper left hand corner.

class MapBlock;
class Game;
class Weapon;
class Item;
class Player;

class Map {

    public:
        //Map();
        Map(Game* game);
        Map& operator=(const Map& other);
        Map(const Map& other);
        void loadFromFile(std::string filename, TerrainManager const&);
        void printMap();
        MapBlock* getBlock(int x, int y);
        MapBlock* getBlock(int x, int y, Direction direction);
        void blast(Weapon* w);
        unsigned getHeight();
        unsigned getWidth();
        Game* getGame() const { return game_; }
        std::vector<std::vector<MapBlock>>* getGrid();
        void pushItem(Item*);

        std::vector <Player*> players;
        std::vector <Walker*> monsters;
        std::vector <Item*> items;

    private:
        std::vector<std::vector<MapBlock>> grid_;
        Game* game_;
};

#endif
