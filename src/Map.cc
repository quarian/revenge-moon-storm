#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstring>

#include "Map.hh"
#include "MapObjectManager.hh"

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

Map::~Map() {
    clear();
}

void Map::clear() {
    for (auto m : monsters)
        delete m;
    monsters.clear();

    for (auto i : items)
        delete i;
    items.clear();

    for (auto p : players)
        p->clearAvatar();
    players.clear();

    for (auto row : grid_) {
        for (auto p : row)
            delete p;
        row.clear();
    }
    grid_.clear();
}

void Map::loadFromFile(std::string filename, TerrainManager const& tmgr) {
    clear();

    std::cout << "Loading from file " << filename << " ...";
    std::ifstream infile(filename);
    std::string line;
    if (!infile)
        std::cout << " error: could not open file!" << std::endl;

    int row = 0;
    int column = 0;
    while (std::getline(infile, line)) {
        std::string temp;
        std::istringstream iss(line);
        std::string line_as_string = iss.str();
        column = 0;
        std::vector<MapBlock*> new_row;
        grid_.push_back(new_row);

        for (char content : line_as_string) {
            if (MapObjectManager::contains(content)) {
                MapBlock* mb = new MapBlock(column, row, ' ', *this, Terrain(tmgr[' ']));
                MapObjectManager::place(content, *this, mb);
                grid_[row].push_back(mb);
            } else {
                Terrain terrain(tmgr[content]);
                MapBlock* mb = new MapBlock(column, row, content, *this, terrain);
                grid_[row].push_back(mb);
            }
            column++;
        }
        row++;
    }
    std::cout << " done. (" << getWidth() << " by " << getHeight() << " blocks)\n";
}

void Map::generateRandomMap(TerrainManager const& tmgr, bool overlap, int height, int width) {
    generateBorders(tmgr, height, width);
    int features;
    if (overlap)
        features = 10;
    else
        features = 200;
    for (int i = 0; i < features; i++) {
        insertFeature(tmgr, overlap);
    }
}

void Map::generateBorders(TerrainManager const& tmgr, int height, int width) {
    char content;
    for (int i = 0; i < height; i ++) {
        std::vector<MapBlock*> new_row;
        grid_.push_back(new_row);
        for (int j = 0; j < width; j++) {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
                content = '#';
                Terrain t(tmgr[content]);
                MapBlock* mb = new MapBlock(j, i, content, *this, t);
                grid_[i].push_back(mb);
            } else {
                content = ' ';
                Terrain t(tmgr[content]);
                MapBlock* mb = new MapBlock(j, i, content, *this, t);
                grid_[i].push_back(mb);
            }
        }
    }
}

void Map::insertFeature(TerrainManager const& tmgr, bool overlap) {
    int w = getWidth() - 1;
    int h = getHeight() - 1;
    Terrain t = tmgr.random();
    char content = t.type->signifier;
    char empty = ' ';
    bool indestructible = t.toughness < -90.0f;
    while (indestructible || !strcmp(&content, &empty)) {
        t = tmgr.random();
        indestructible = t.toughness < -90.0f;
        content = t.type->signifier;
    }
    int x_min, x_max, y_min, y_max, door_x, door_y;
    x_min = std::min(w, (rand() % w) + 1);
    y_min = std::min(h, (rand() % h) + 1);
    //std::cout << "x_min " << x_min << ", y_min " << y_min << ", w " << w << ", h " << h << std::endl;
    x_max = std::min(w, x_min + 1 + rand() % (getWidth() - x_min));
    y_max = std::min(h, y_min + 1 + rand() % (getHeight() - y_min));
    if (x_max > x_min && y_max > y_min) {
        door_x = rand() % (x_max - x_min) + x_min;
        door_y = rand() % (y_max - y_min) + y_min;
    }
    
    // Check for overlaps on features - if overlaps, forget aboyt adding the feature
    if (!overlap) {
        for (int i = 1; i < h; i++) {
            for (int j = 1; j < w; j++) {
                if (((i == y_min || i == y_max) && (j >= x_min && j <= x_max)) ||
                    ((j == x_min || j == x_max) && (i >= y_min && i <= y_max))) {
                    if ((y_min < y_max) && (x_min < x_max)) {
                        if (!grid_[i][j]->isPassable())
                            return;
                    }
                }
            }
        }
    }

    for (int i = 1; i < h; i++) {
        for (int j = 1; j < w; j++) {
            if (((i == y_min || i == y_max) && (j >= x_min && j <= x_max)) ||
                ((j == x_min || j == x_max) && (i >= y_min && i <= y_max))) {
                if ((y_min < y_max) && (x_min < x_max)) {
		    MapBlock* mb = new MapBlock(j, i, content, *this, t);
                    delete grid_[i][j];
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
    for (auto row : grid_) {
        for (auto mb : row) {
            std::cout << mb->content_;
        }
        std::cout << std::endl;
    }
}

MapBlock* Map::getBlock(int x, int y) {
    if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight()) return nullptr;
    return grid_[y][x];
}

MapBlock* Map::getBlock(int x, int y, Direction direction) {
    if (direction == Direction::NORTH)
        return getBlock(x, y-1);
    else if (direction == Direction::SOUTH)
        return getBlock(x, y+1);
    else if (direction == Direction::WEST)
        return getBlock(x-1, y);
    else if (direction == Direction::EAST)
        return getBlock(x+1, y);
    else
        return getBlock(x, y);
}

int Map::getHeight() {
    return grid_.size();
}
int Map::getWidth() {
    return grid_[0].size();
}

std::vector<std::vector<MapBlock*>>* Map::getGrid() {
    return &grid_;
}

void Map::spawnPlayer(Player* player, int x, int y) {
    player->spawn(*this, getBlock(x, y));
    player->getActor()->initSprite(
            game_->graphicsManager_.getAnimation("walking_player"),
            game_->graphicsManager_.getAnimation("digging_player"),
            game_->graphicsManager_.getPlayerColor());
    players.insert(player);
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
