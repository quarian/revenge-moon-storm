#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "MapBlock.hh"

enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST };

// Note that Map coordinates (0,0) are at the upper left hand corner.

class Map {

    public:
        Map();
        void loadFromFile(std::string filename);
        void printMap();
    private:
        std::vector<std::vector<MapBlock>> grid_;
};
