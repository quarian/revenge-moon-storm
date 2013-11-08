#include "MapBlock.hh"

MapBlock::MapBlock(int x, int y, std::string content, Map& map) : x_(x), y_(y), content_(content), map_(map)
{

}

MapBlock::MapBlock(const MapBlock& other) : x_(other.x_), y_(other.y_), content_(other.content_), map_(other.map_) {}

MapBlock MapBlock::operator=(const MapBlock& other) {
    if (this == &other) return *this;
    x_ = other.x_;
    y_ = other.y_;
    content_ = other.content_;
    map_ = other.map_;
    return *this;
}

bool MapBlock::isPassable() const {
    return true;
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
