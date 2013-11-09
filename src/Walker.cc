#include "Walker.hh"
#include <cmath>
#include <iostream>

Walker::Walker(Map& map, MapBlock* location, float speed) :
        map_(map),
        location_(location),
        target_(nullptr),
        facing_(Direction::NORTH),
        dPos_(Direction::NULLDIR),
        speed_(speed) {
    location_->enter(this);
}


void Walker::updateLocation(float dt) {
    if (!target_) return;
    else if (target_ == location_) approach(dt);
    else depart(dt);
}


void Walker::approach(float dt) {
    float timeToCenter = dPos_.length() / speed_;

    if (dt >= timeToCenter) {
        center();
        update(dt - timeToCenter);
    } else {
        float distance = dt * speed_;
        dPos_ = dPos_.in(distance);
    }
}


void Walker::depart(float dt) {
    float timeToEdge = (0.5 - dPos_.length()) / speed_;

    if (dt >= timeToEdge) {
        proceed();
        update(dt - timeToEdge);
    } else {
        float distance = dt * speed_;
        dPos_ = dPos_.out(distance, facing_);
    }
}


void Walker::reverse() {
    if (!target_) return; // Already standing still.
    facing_ = -facing_;
    target_ = target_->getBlock(facing_);
}


void Walker::center() {
    dPos_ = Direction::NULLDIR;
    target_ = nullptr;
}


void Walker::proceed() {
    if (!target_->isPassable()) {
        center();
        target_ = nullptr;
    } else {
        target_->enter(this);
        location_->exit(this);
        location_ = target_;
        dPos_ = -facing_ * 0.5;
    }
}


void Walker::knock(Direction dir) {
    facing_ = dir;

    MapBlock* target = location_->getBlock(facing_);
    if (target == nullptr) return;
    else if (!target->isPassable()) return;
    else target_ = target;
}
