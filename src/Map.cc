#include <SFML/Graphics.hpp>
#include "Map.hh"

//Map::Map() : game_(nullptr) {}

Map::Map(Game* game) : game_(game)
{
}

Map& Map::operator=(const Map& other) {
    if (this == &other) return *this;
    grid_ = other.grid_;
    game_ = other.game_;
    return *this;
}

Map::Map(const Map& other) : game_(other.game_)
{
}

void Map::loadFromFile(std::string filename, TerrainManager const& tmgr) {
    std::cout << "Loading from file: " << filename << std::endl;
    std::ifstream infile(filename);
    std::string line;
    int row = 0;
    int column = 0;
    while (std::getline(infile, line)) {
        std::string temp;
        std::istringstream iss(line);
        std::string line_as_string = iss.str();
        column = 0;
        std::vector<MapBlock> new_row;
        grid_.push_back(new_row);
        for (auto iter = line_as_string.begin(); iter != line_as_string.end(); iter++) {
            std::string content(1, *iter);
            Terrain terrain(tmgr[content[0]]);
            MapBlock mb(column, row, content, *this, terrain);
            column++;
            grid_[row].push_back(mb);
        }
        row++;
    }
}

void Map::printMap() {
    std::cout  << "Printing map" << std::endl;
    for (auto iter = grid_.begin(); iter != grid_.end(); iter++) {
        for (auto jiter = (*iter).begin(); jiter != (*iter).end(); jiter++) {
            if (!(jiter->content_).compare(""))
                std::cout << " ";
            else
                std::cout << jiter->content_;
        }
        std::cout << std::endl;
    }
}

MapBlock* Map::getBlock(int x, int y) {
    return &grid_[y][x];
}

MapBlock* Map::getBlock(int x, int y, Direction direction) {
    if (direction == Direction::NORTH)
        return &grid_[y - 1][x];
    else if (direction == Direction::SOUTH)
        return &grid_[y + 1][x];
    else if (direction == Direction::WEST)
        return &grid_[y][x - 1];
    else if (direction == Direction::EAST)
        return &grid_[y][x + 1];
    else
        return &grid_[y][x];
}

unsigned Map::getHeight() {
    return grid_.size();
}
unsigned Map::getWidth() {
    return grid_[0].size();
}

std::vector<std::vector<MapBlock>>* Map::getGrid() {
    return &grid_;
}

void Map::blast(Weapon* w) {
    int r = w->getRadius();
    int p = w->getPower();
    MapBlock* location = w->getLocation();
    int distance = 0;
    if (SmallBomb* sb = dynamic_cast<SmallBomb*>(w)) {
        for (auto iter = grid_.begin(); iter != grid_.end(); iter++) {
            for (auto jiter = iter->begin(); jiter != iter->end(); jiter++) {
                distance = sqrt(((*jiter).x_ - location->x_) * ((*jiter).x_ - location->x_) +
                                ((*jiter).y_ - location->y_) * ((*jiter).y_ - location->y_));
                if (distance < r)
                    (*jiter).takeDamage(p);
            }
        }
    }
}


void Map::pushItem(Item* item) {
    items.push_back(item);
}
