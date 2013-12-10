#ifndef MB2_MAP_HH
#define MB2_MAP_HH

#include <functional>
#include <iostream>
#include <fstream>
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
class MapGenerator;

class Map {
    friend class MapGenerator;
    public:
        //Map();
        Map(Game* game);
        Map& operator=(const Map& other);
        Map(const Map& other);
        ~Map();

        void loadFromFile(std::string filename, TerrainManager const&);
        void generateRandomMap(TerrainManager const&, bool overlap = true, int height = 44, int width = 64);
        void generateMaze(TerrainManager const&, int height = 44, int width = 64);
        void divide(TerrainManager const&, int x_min, int x_max, int y_min, int y_max);
        void printMap(std::ostream& os = std::cout);
        MapBlock* getBlock(int x, int y);
        MapBlock* getBlock(int x, int y, Direction direction);

        void clear();
        void blast(Weapon* w);
        void crossblast(Weapon* w);
        int getHeight();
        int getWidth();
        Game* getGame() const { return game_; }
        std::vector<std::vector<MapBlock*>>* getGrid();

        void setBlock(int, int, char, Terrain);
        void save();


        void pushItem(Item* item) { items.insert(item); }
        void popItem(Item* item) { items.erase(item); }

        void spawnPlayer(Player*, int, int);

        float getDistance(MapBlock*, MapBlock*);
        float getDistance(int, int, int, int);

        std::set <Player*> players;
        std::set <Walker*> monsters;
        std::set <Item*> items;


    private:
        void generateBorders(TerrainManager const&, int height, int width);
        void insertFeature(TerrainManager const&, bool overlap);
        std::vector<std::vector<MapBlock*>> grid_;
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
        std::vector<MapBlock*> getLOS(MapBlock*, bool=true);
        void bresenham(int, int, int, int, std::vector<MapBlock*>&, bool=true);

        /* Generates and returns a random-walk path starting at the given
         * MapBlock. The boolean specifies whether the starting MapBlock is
         * included. The caller may specify a predicate that specifies what
         * MapBlocks are valid path elements. The default is to construct the
         * walk strictly out of passable blocks.
         *
         * The silly overload dance here is to enable a default predicate that
         * would create a circular dependency in the header.
         */
        std::deque<MapBlock*> randomWalk(MapBlock*, size_t, bool=false);
        std::deque<MapBlock*> randomWalk(MapBlock*, size_t, bool,
                std::function<bool(MapBlock*)>);

        /* Chooses a MapBlock within the given number of steps of the starting
         * block, then returns an A* shortest-path to it. Parameters are the
         * same as above.
         *
         * WARNING: the integration with A* is NOT FOOLPROOF yet, wrt. the
         *          handling of the predicate.
         */
        std::deque<MapBlock*> randomDestinationWalk(
                MapBlock*, size_t, bool=false);
        std::deque<MapBlock*> randomDestinationWalk(
                MapBlock*, size_t, bool, std::function<bool(MapBlock*)>);
};

#endif
