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
        dThink_(0.0) { }


void AIActor::update(float dt) {
    dThink_ -= dt;
    if (dThink_ <= 0)
        think();
    Actor::update(dt);
}


void AIActor::cancelPath() {
    while(!path_.empty())
        path_.pop();
}

void AIActor::popPath(float dt) {
    if (!path_.empty()) {
        target_ = path_.top();
        path_.pop();

        if ( fdim(target_->x_, location_->x_) + // If not neighboring
             fdim(target_->y_, location_->y_) != 1) {
            target_ = nullptr;
            cancelPath();
        }

        update(dt);
    }
}


void AIActor::pushPath(std::stack<MapBlock*> mbs, int nmax=-1) {
    if (nmax == -1) {
        while (!mbs.empty()) {
            pushPath(mbs.top());
            mbs.pop();
        }
    } else {
        while (nmax --> 0 && !mbs.empty()) {
            pushPath(mbs.top());
            mbs.pop();
        }
    }
}


void AIActor::pushPath(MapBlock* mb) {
    path_.push(mb);
}


void AIActor::setPath(std::stack<MapBlock*> mbs, int nmax=-1) {
    cancelPath();
    pushPath(mbs, nmax);
}


void AIActor::findTarget(float dt) {
    popPath(dt);
}
