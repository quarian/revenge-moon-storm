#include "MapBlock.hh"
#include "Actor.hh"

#include <cmath>


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
    walkers_.insert(w);
}

void MapBlock::exit(Walker* w) {
    walkers_.erase(w);
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


void MapBlock::takeDamage(int amount) {
    // Weaken the terrain
    weaken(amount);

    // Weaken the items
    for (auto item : items_)
        item->takeDamage(amount);
    for (Walker* w : walkers_)
        if (Actor* a = dynamic_cast<Actor*>(w))
            a->takeDamage(amount);
}
