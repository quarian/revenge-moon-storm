#ifndef MB2_MAPGENERATOR_HH
#define MB2_MAPGENERATOR_HH

#include "Map.hh"

class Game;

class MapGenerator {

    public:
        MapGenerator(TerrainManager* tmgr, Game* game);
        Map& generateMap();
        Map generateTotallyRandomMap();
    
    private:
        TerrainManager* tmgr_;
        Game* game_;
};

#endif
