#include "Walker.hh"

#include <SFML/System/Time.hpp>
#include <cmath>

Walker::Walker(Map& map, MapBlock* location, float speed) :
        map_(map),
        location_(location),
        target_(nullptr),
        facing_(Direction::NORTH),
        dPos_(Direction::NULLDIR),
        speed_(speed) {
    location_->enter(this);
}


void Walker::update(float dt) {
    updateLocation(dt);
    updateSprite(dt);
}


void Walker::initSprite(Animation const& animation, sf::Color color) {
    sprite_.setAnimation(animation);
    sprite_.setColor(color);
    sprite_.setOrigin(8,8);
    updateSprite(0.0);
}


void Walker::updateLocation(float dt) {
    if (target_) {
        if (target_ == location_) approach(dt);
        else depart(dt);
    }
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

    target_ = location_->getBlock(facing_);
    if (target_ == nullptr) return;
    else if (!target_->isPassable()) target_ = nullptr;
}


void Walker::updateSprite(float dt) {
    alignSprite();
    this->getSprite().update(sf::seconds(dt));

    float xAbs = location_->x_ + dPos_.x();
    float yAbs = location_->y_ + dPos_.y();
    this->getSprite().setPosition(8 + xAbs*16, 8 + yAbs*16);
}


void Walker::alignSprite() {
    if (this->getSprite().getAnimation()) {
        if (facing_.angle() != Direction::UNDEFINED_ANGLE)
            this->getSprite().setRotation(facing_.angle());
    }
}
