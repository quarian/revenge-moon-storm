#ifndef MB2_MAPBLOCK_HH
#define MB2_MAPBLOCK_HH

#include <string>
#include <vector>
#include <algorithm> // for find_if
#include "Map.hh"
#include "Direction.hh"

// Forward declaration
class Walker;
class Map;

enum BlockToughness {
    NONE,
    WEAK,
    MEDIUM,
    STRONG,
    INDESTRUCTIBLE
};

class MapBlock {
    public:
        MapBlock(int x, int y, std::string content, Map& map, BlockToughness toughness = NONE);
        ~MapBlock() {};
        MapBlock(const MapBlock& other);
        MapBlock operator=(const MapBlock& other);

        int x_;
        int y_;
        std::string content_;
        bool isPassable() const;
        MapBlock* getBlock(Direction direction);
        void exit(const Walker* w);
        void enter(Walker* w);
        
        void weaken();
        
    private:
        std::vector<Walker*> walkers_;
        //std::vector<Item*> items_;
        Map& map_;
        BlockToughness toughness_;

};

#endif
