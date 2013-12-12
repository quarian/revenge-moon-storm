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

bool Map::loadFromFile(std::string filename, TerrainManager const& tmgr) {
    clear();

    std::cout << "Loading from file " << filename << " ...";
    std::ifstream infile(filename);
    std::string line;
    if (!infile) {
        std::cout << " error: could not open file!" << std::endl;
        return false;
    }

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
    return true;
}

void Map::generateRandomMap(TerrainManager const& tmgr, bool overlap, int height, int width) {
    clear();
    generateBorders(tmgr, height, width);
    int features;
    if (overlap)
        features = 10;
    else
        features = 200;
    for (int i = 0; i < features; i++) {
        insertFeature(tmgr, overlap);
    }
    addItems(20);
}

void Map::generateMaze(TerrainManager const& tmgr, int height, int width) {
    clear();
    generateBorders(tmgr, height, width);
    divide(tmgr, 1, width - 1, 1, height - 1);
    addItems(20);
}

void Map::divide(TerrainManager const& tmgr, int x_min, int x_max, int y_min, int y_max) {
    if (x_max - x_min < 4 || y_max - y_min < 4)
        return;
    bool horizontal = (rand() % 2) == 0;
    char content = '#';
    Terrain t(tmgr[content]);
    int door;
    if (horizontal) {
        int y = rand() % (y_max - y_min - 3) + y_min + 2;
        door = rand() % (x_max - x_min - 3) + x_min + 2;
        //door = (x_max + x_min) / 2;
        for (int i = x_min; i < x_max; i++) {
            if (i != door) {
                MapBlock* mb = new MapBlock(i, y, content, *this, t);
                delete grid_[y][i];
                grid_[y][i] = mb;
            }
        }
        if (grid_[y][x_min - 1]->isPassable() && !grid_[y + 1][x_min - 1]->isPassable() && !grid_[y + 1][x_min - 1]->isPassable()) {
            content = ' ';
            t = tmgr[content];
            MapBlock* mb = new MapBlock(x_min, y, content, *this, t);
            delete grid_[y][x_min];
            grid_[y][x_min] = mb;
        }
        if (grid_[y][x_max]->isPassable() && !grid_[y - 1][x_max]->isPassable() && !grid_[y + 1][x_max]->isPassable()) {
            content = ' ';
            t = tmgr[content];
            MapBlock* mb = new MapBlock(x_max - 1, y, content, *this, t);
            delete grid_[y][x_max - 1];
            grid_[y][x_max - 1] = mb;
        }
        divide(tmgr, x_min, x_max, y_min, y);
        divide(tmgr, x_min, x_max, y + 1, y_max);
    } else {
        int x = rand() % (x_max - x_min - 3) + x_min + 2;
        door = (rand() % (y_max - y_min - 3)) + y_min + 2;
        //door = (y_max + y_min) / 2;
        for (int i = y_min; i < y_max; i++) {
            if (i != door) {
                MapBlock* mb = new MapBlock(x, i, content, *this, t);
                delete grid_[i][x];
                grid_[i][x] = mb;
            }
        }
        if (grid_[y_min - 1][x]->isPassable() && !grid_[y_min - 1][x + 1]->isPassable() && !grid_[y_min - 1][x - 1]->isPassable()) {
            content = ' ';
            t = tmgr[content];
            MapBlock* mb = new MapBlock(x, y_min, content, *this, t);
            delete grid_[y_min][x];
            grid_[y_min][x] = mb;
        }
        if (grid_[y_max][x]->isPassable() && !grid_[y_max][x - 1]->isPassable() && !grid_[y_max][x + 1]->isPassable()) {
            content = ' ';
            t = tmgr[content];
            MapBlock* mb = new MapBlock(x, y_max - 1, content, *this, t);
            delete grid_[y_max - 1][x];
            grid_[y_max - 1][x] = mb;
        }
        divide(tmgr, x + 1, x_max, y_min, y_max);
        divide(tmgr, x_min, x, y_min, y_max);
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

void Map::addItems(int amount) {
    for (int i = 0; i < amount; i++) {
        bool placed = false;
        int x, y;
        while (!placed) {
            x = rand() % (getWidth() - 3) + 1;
            y = rand() % (getHeight() - 3) + 1;
            if (grid_[y][x]->isPassable()) {
                bool gold = rand() % 2 == 0;
                if (gold) {
                    grid_[y][x]->content_ = '4'; // HACKS GALORE
                    new Treasure(*this, grid_[y][x], "Gold Bar", 100);
                }
                else {
                    grid_[y][x]->content_ = 'B'; // HACKS GALORE
                    new Weaponbox(*this, grid_[y][x]);
                }
                placed = true;
            }
        }
    }
}


void Map::printMap(std::ostream& os) {
    for (auto row : grid_) {
        for (auto mb : row) {
            os << mb->content_;
        }
        os << std::endl;
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
    blast(r, p, location);
}

void Map::blast(int radius, int power, MapBlock* location) {
    for (auto mb : getInRadius(location, radius)) {
        //std::cerr << "distance: " << getDistance(location, mb) << std::endl;
        mb->takeDamage(power - getDistance(location, mb) * 3); //lower power over distance
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

void Map::setBlock(int x, int y, char content, Terrain t) {
    MapBlock* mb = new MapBlock(x, y, content, *this, t);
    delete grid_[y][x];
    grid_[y][x] = mb;
}

void Map::save(std::string path) {
    std::ofstream output;
    output.open(path);
    printMap(output);
    output.close();

}
