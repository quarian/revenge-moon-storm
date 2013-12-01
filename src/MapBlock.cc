#include "MapBlock.hh"

#include <cmath>
//const unsigned MapBlock::NONE = 0;
//const unsigned MapBlock::WEAK = 1;
//const unsigned MapBlock::MEDIUM = 2;
//const unsigned MapBlock::STRONG = 3;
//const unsigned MapBlock::INDESTRUCTIBLE = 10;

MapBlock::MapBlock(int x, int y, std::string content, Map& map, Terrain terrain) : x_(x), y_(y), content_(content), map_(map), terrain_(terrain)
{}

MapBlock::MapBlock(const MapBlock& other) : x_(other.x_), y_(other.y_), content_(other.content_), map_(other.map_), terrain_(other.terrain_) {}

MapBlock MapBlock::operator=(const MapBlock& other) {
    if (this == &other) return *this;
    x_ = other.x_;
    y_ = other.y_;
    content_ = other.content_;
    map_ = other.map_;
    terrain_ = other.terrain_;
    return *this;
}

bool MapBlock::isPassable() const {
    return terrain_.type->passable;
}

bool MapBlock::isDiggable() const {
    return terrain_.type->diggable;
}

MapBlock* MapBlock::getBlock(Direction direction) const {
    return map_.getBlock(x_, y_, direction);
}

void MapBlock::enter(Walker* w) {
    walkers_.push_back(w);
}

void MapBlock::exit(const Walker* w) {
    std::vector<Walker*>::iterator iter = std::find_if(walkers_.begin(), walkers_.end(), [&](Walker* t)
                                                                                            { return t == w; });
    walkers_.erase(iter);
}

void MapBlock::clear() {
    terrain_.raze();
}

void MapBlock::weaken(float dmg) {
    if (dmg > terrain_.toughness)
        terrain_.raze();
    else
        terrain_.takeDamage(dmg);
}

void MapBlock::collect(Inventory* inventory) {
    for (auto iter = items_.begin(); iter != items_.end(); iter++) {
        if ((*iter)->getCollectible()) {
            inventory->collect(*iter);
            iter = items_.erase(iter);
        }
    }
}

void MapBlock::pushItem(Item* item) {
    items_.push_back(item);
}

Item* MapBlock::popItem(Item* item) {
    std::vector<Item*>::iterator iter = std::find_if(items_.begin(), items_.end(), [&](Item* i)
                                                                                     { return i == item; });
    items_.erase(iter);
    return *iter;
}

void MapBlock::takeDamage(int amount) {
    weaken(amount);
    for (auto iter = items_.begin(); iter != items_.end(); iter++) {
        bool destoryed = (*iter)->takeDamage(amount);
        if (destoryed)
            iter = items_.erase(iter);
    }
    for (auto iter = walkers_.begin(); iter != walkers_.end(); iter++) {
            bool destroyed = false;//Game::damageActor(*iter, amount);
            if (destroyed)
                iter = walkers_.erase(iter);
    }
}
