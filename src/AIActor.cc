#include "AIActor.hh"

#include <cmath>


AIActor::AIActor(
    Map& map,
    MapBlock* block,
    float speed,
    float digPower,
    int health,
    float resistance,
    Inventory* inv) :
        Actor(map, block, speed, digPower, health, resistance, inv),
        needThink_(true) { }


void AIActor::update(float dt) {
    if (needThink_)
        think();
    Actor::update(dt);
}


void AIActor::cancelPath() {
    path_.clear();
    needThink_ = true;
}

void AIActor::popPath(float dt) {
    if (!path_.empty()) {
        target_ = path_.front();
        path_.pop_front();

        while (target_ == location_ && !path_.empty()) {
            target_ = path_.front();
            path_.pop_front();
        }

        Direction facing = location_->getFacingTo(target_);
        if (facing != Direction::NULLDIR)
            facing_ = facing;

    } else target_ = nullptr;
}


void AIActor::pushPath(std::deque<MapBlock*> mbs, int nmax=-1) {
    if (nmax == -1) {
        while (!mbs.empty()) {
            pushPath(mbs.front());
            mbs.pop_front();
        }
    } else {
        while (nmax --> 0 && !mbs.empty()) {
            pushPath(mbs.front());
            mbs.pop_front();
        }
    }
}


void AIActor::pushPath(MapBlock* mb) {
    path_.push_back(mb);
}


void AIActor::setPath(std::deque<MapBlock*> mbs, int nmax=-1) {
    cancelPath();
    pushPath(mbs, nmax);
}


void AIActor::findTarget(float dt) {
    popPath(dt);
    if (target_) {
        if (location_->getManhattanDistance(target_) != 1) { // Not neighboring
            target_ = nullptr;
            cancelPath();
            needThink_ = true;
        } else update(dt);
    } else needThink_ = true;
}
