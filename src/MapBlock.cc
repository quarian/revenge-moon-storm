#include "MapBlock.hh"
const unsigned MapBlock::NONE = 0;
const unsigned MapBlock::WEAK = 1;
const unsigned MapBlock::MEDIUM = 2;
const unsigned MapBlock::STRONG = 3;
const unsigned MapBlock::INDESTRUCTIBLE = 10;

MapBlock::MapBlock(int x, int y, std::string content, Map& map, unsigned toughness) : x_(x), y_(y), content_(content), map_(map), toughness_(toughness)
{
    if (content_.compare("#") == 0)
        toughness_ = STRONG;
}

MapBlock::MapBlock(const MapBlock& other) : x_(other.x_), y_(other.y_), content_(other.content_), map_(other.map_), toughness_(other.toughness_) {}

MapBlock MapBlock::operator=(const MapBlock& other) {
    if (this == &other) return *this;
    x_ = other.x_;
    y_ = other.y_;
    content_ = other.content_;
    map_ = other.map_;
    toughness_ = other.toughness_;
    return *this;
}

bool MapBlock::isPassable() const {
    return toughness_ == NONE;
}

MapBlock* MapBlock::getBlock(Direction direction) {
    return map_.getBlock(x_, y_, direction);
}

void MapBlock::enter(Walker* w) {
    walkers_.push_back(w);
}

void MapBlock::exit(const Walker* w) {
    std::vector<Walker*>::iterator iter = std::find_if(walkers_.begin(), walkers_.end(), [&](Walker* t)
                                                                                            {return t == w; });
    walkers_.erase(iter);
}

void MapBlock::weaken() {
    if (toughness_ != NONE && toughness_ != INDESTRUCTIBLE)
        toughness_--;
}
