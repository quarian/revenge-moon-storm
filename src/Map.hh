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
        void crossblast(Weapon* w);
        unsigned getHeight();
        unsigned getWidth();
        Game* getGame() const { return game_; }
        std::vector<std::vector<MapBlock>>* getGrid();

        void pushItem(Item* item) { items.insert(item); }
        void popItem(Item* item) { items.erase(item); }

        float getDistance(MapBlock*, MapBlock*);
        float getDistance(int, int, int, int);

        std::set <Player*> players;
        std::set <Walker*> monsters;
        std::set <Item*> items;


    private:
        std::vector<std::vector<MapBlock>> grid_;
        Game* game_;


    public:
        /* MAP UTILITIES -- defined in MapUtils.cc */

        /* Returns a vector of all the MapBlocks that lie within a certain
         * radius of some reference block. Set the last parameter to false to
         * exclude the reference block from the vector.
         */
        std::vector<MapBlock*> getInRadius(MapBlock*, float, bool=true);

        /* Returns a vector of all the MapBlocks that can be seen from the
         * given reference block. Used, for example, to determine fog of war.
         */
        std::vector<MapBlock*> getLOS(MapBlock*);
};

#endif
