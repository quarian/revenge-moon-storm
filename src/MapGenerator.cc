#include "MapGenerator.hh"

MapGenerator::MapGenerator(TerrainManager* tmgr, Game* game) : tmgr_(tmgr), game_(game) {
}

Map& MapGenerator::generateMap() {
    Map result(game_);
    Map& ref = result;
    int size = 64;
    std::string content;
    for (int i = 0; i < size; i ++) {
        std::vector<MapBlock> new_row;
        result.grid_.push_back(new_row);
        for (int j = 0; j < size; j++) {
            if (i == 0 || j == 0 || i == size - 1 || j == size - 1) {
                content = "#";
                Terrain t((*tmgr_)[content[0]]);
                MapBlock mb(j, i, content, ref, t);
                result.grid_[i].push_back(mb);
            } else {
                content = " ";
                Terrain t((*tmgr_)[content[0]]);
                MapBlock mb(j, i, content, ref, t);
                result.grid_[i].push_back(mb);
            }
        }
    }
    return result;
}

Map MapGenerator::generateTotallyRandomMap() {
    return generateMap();
}
