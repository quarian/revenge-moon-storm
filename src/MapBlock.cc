#include "MapBlock.hh"
#include "Actor.hh"
#include "ControlledActor.hh"

#include <cmath>

MapBlock::MapBlock(int x, int y, char content, Map& map, Terrain terrain) : x_(x), y_(y), visible_(false), content_(content), map_(map), terrain_(terrain)
{}

MapBlock::MapBlock(const MapBlock& other) : x_(other.x_), y_(other.y_), visible_(other.visible_), content_(other.content_), map_(other.map_), terrain_(other.terrain_) {}

MapBlock MapBlock::operator=(const MapBlock& other) {
    if (this == &other) return *this;
    x_ = other.x_;
    y_ = other.y_;
    visible_ = other.visible_;
    content_ = other.content_;
    map_ = other.map_;
    terrain_ = other.terrain_;
    return *this;
}

int MapBlock::getSquareDistance(MapBlock const* other) const {
    int dx = x_ - other->x_;
    int dy = y_ - other->y_;
    return dx*dx + dy*dy;
}

int MapBlock::getManhattanDistance(MapBlock const* other) const {
    int dx = x_ - other->x_;
    int dy = y_ - other->y_;
    return fabs(dx) + fabs(dy);
}

Direction MapBlock::getFacingTo(MapBlock const* other) const {
    if (!other) return Direction::NULLDIR;
    if (other == this) return Direction::NULLDIR;

    int dx = other->x_ - x_;
    int dy = other->y_ - y_;

    if (fabs(dx) > fabs(dy)) {
        if (dx < 0) return Direction::WEST;
        else return Direction::EAST;
    } else {
        if (dy < 0) return Direction::NORTH;
        else return Direction::SOUTH;
    }
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

MapBlock* MapBlock::getRandomNeighbor(
        std::function<bool(MapBlock*)> pred) const {
    std::vector<Direction> neighbors = { Direction::NORTH, Direction::EAST, Direction::SOUTH, Direction::WEST };
    std::random_shuffle(neighbors.begin(), neighbors.end());
    for (auto n : neighbors)
        if (pred(getBlock(n)))
            return getBlock(n);
    return nullptr;
}

MapBlock* MapBlock::getRandomPassableNeighbor() const {
    return getRandomNeighbor([](MapBlock* mb){ return mb->isPassable(); });
}


void MapBlock::enter(Walker* w) {
    walkers_.insert(w);
}

void MapBlock::exit(Walker* w) {
    walkers_.erase(w);
}

void MapBlock::clear() {
    terrain_.raze();
    new Dustcloud(map_, this);
}

void MapBlock::weaken(float dmg) {
    if (dmg > terrain_.toughness) {
        terrain_.raze();
    } else
        terrain_.takeDamage(dmg);
}

void MapBlock::collect(Inventory* inventory) {
    std::vector<Item*> deadItems;
    for (auto item : items_) {
        if (item->getCollectible()) {
            if (inventory->collect(item)) //returns true if the item was picked up
                deadItems.push_back(item);
        }
    }
    for (Item* i : deadItems) {
        delete i;
        map_.popItem(i);
    }
}


void MapBlock::takeDamage(float amount) {
    // Weaken the terrain
    weaken(amount);

    // Weaken the items
    for (auto item : items_)
        item->takeDamage(amount);
    for (Walker* w : walkers_)
        if (Actor* a = dynamic_cast<Actor*>(w))
            a->takeDamage(amount);
}


std::vector<ControlledActor*> MapBlock::getPlayers() {
    std::vector<ControlledActor*> vec;
    for (auto w : walkers_) {
        if (ControlledActor* p = dynamic_cast<ControlledActor*>(w)) {
            vec.push_back(p);
        }
    }
    return vec;
}

bool MapBlock::hasWalkers(Walker* w) {
    if (!w) {
        return walkers_.begin() != walkers_.end();
    } else {
        for (auto a : walkers_)
            if (a != w) return true;
        return false;
    }
}
