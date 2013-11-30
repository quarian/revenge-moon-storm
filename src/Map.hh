#ifndef MB2_MAP_HH
#define MB2_MAP_HH

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "MapBlock.hh"
#include "Direction.hh"

// Note that Map coordinates (0,0) are at the upper left hand corner.

class MapBlock;
class Game;
class Weapon;

class Map {

    public:
        Map();
        Map(const Game* game);
        Map& operator=(const Map& other);
        Map(const Map& other);
        void loadFromFile(std::string filename);
        void printMap();
        MapBlock* getBlock(int x, int y);
        MapBlock* getBlock(int x, int y, Direction direction);
        void blast(Weapon* w);
        unsigned getHeight();
        unsigned getWidth();
        const Game* getGame() const { return game_; }
        std::vector<std::vector<MapBlock>>* getGrid();
    private:
        std::vector<std::vector<MapBlock>> grid_;
        const Game* game_;
};

#endif
