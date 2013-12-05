#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>

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

void Map::generateRandomMap(TerrainManager const& tmgr, int height, int width) {
    generateBorders(tmgr, height, width);
    for (int i = 0; i < 15; i++) {
        insertFeature(tmgr);
    }
}

void Map::generateBorders(TerrainManager const& tmgr, int height, int width) {
    std::string content;
    for (int i = 0; i < height; i ++) {
        std::vector<MapBlock> new_row;
        grid_.push_back(new_row);
        for (int j = 0; j < width; j++) {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
                content = "#";
                Terrain t(tmgr[content[0]]);
                MapBlock mb(j, i, content, *this, t);
                grid_[i].push_back(mb);
            } else {
                content = " ";
                Terrain t(tmgr[content[0]]);
                MapBlock mb(j, i, content, *this, t);
                grid_[i].push_back(mb);
            }
        }
    }
}

void Map::insertFeature(TerrainManager const& tmgr) {
    unsigned w = getWidth() - 1;
    unsigned h = getHeight() - 1;
    Terrain t = tmgr.random();
    std::string content(&t.type->signifier, 0, 1);
    unsigned x_min, x_max, y_min, y_max;
    x_min = (rand() % w) + 1;
    y_min = (rand() % h) + 1;
    //std::cout << "x_min " << x_min << ", y_min " << y_min << ", w " << w << ", h " << h << std::endl;
    x_max = std::min(w, x_min + rand() % (getWidth() - x_min));
    y_max = std::min(h, y_min + rand() % (getHeight() - y_min));
    std::string empty = " ";
    for (unsigned i = 0; i < getHeight(); i++) {
        for (unsigned j = 0; j < getWidth(); j++) {
            if (((i == y_min || i == y_max) && (j >= x_min && j <= x_max)) ||
                ((j == x_min || j == x_max) && (i >= y_min && i <= y_max))) {
                if (!empty.compare(grid_[i][j].content_) && (y_min != y_max) && (x_min != x_max)) {
                    MapBlock mb(j, i, content, *this, t);
                    grid_[i][j] = mb;
                } else {
                    break;
                }
            }
        }
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

float Map::getDistance(int x1, int y1, int x2, int y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

float Map::getDistance(MapBlock* mb1, MapBlock* mb2) {
    return getDistance(mb1->x_, mb1->y_, mb2->x_, mb2->y_);
}

void Map::blast(Weapon* w) {
    int r = w->getRadius();
    int p = w->getPower();
    MapBlock* location = w->getLocation();
    for (auto mb : getInRadius(location, r)) {
        //std::cerr << "distance: " << getDistance(location, mb) << std::endl;
        mb->takeDamage(p - getDistance(location, mb) * 3); //lower power over distance
        new Explosion(*this, mb);
    }
}

void Map::crossblast(Weapon* w) {
    int l = w->getRadius();
    int p = w->getPower();
    MapBlock* location = w->getLocation();

    //The blast square takes damage
    location->takeDamage(p);
    new Explosion(*this, location);

    bool up, down, left, right = false;

    //The other squares take damage
    for (int i = 1; i < l; i++) {
        if (location->x_ - i > 0) {
            auto mb = getBlock(location->x_ - i, location->y_);
            if (mb->getToughness() < 0) {
                left = true;
            }
            if (!left) {
                mb->takeDamage(p - i*3);
                new Explosion(*this, mb);
            }
        }
        if (location->x_ + i < getWidth() - 1) {
            auto mb = getBlock(location->x_ + i, location->y_);
            if (mb->getToughness() < 0) {
                right = true;
            }
            if (!right) {
                mb->takeDamage(p - i*3);
                new Explosion(*this, mb);
            }
        }
        if (location->y_ - i > 0) {
            auto mb = getBlock(location->x_, location->y_ - i);
            if (mb->getToughness() < 0) {
                up = true;
            }
            if (!up) {
                mb->takeDamage(p - i*3);
                new Explosion(*this, mb);
            }
        }
        if (location->y_ + i < getHeight() - 1) {
            auto mb = getBlock(location->x_, location->y_ + i);
            if (mb->getToughness() < 0) {
                down = true;
            }
            if (!down) {
                mb->takeDamage(p - i*3);
                new Explosion(*this, mb);
            }
        }
    }
}