#include "Walker.hh"

#include <SFML/System/Time.hpp>
#include <cmath>

Walker::Walker(Map& map, MapBlock* location, float speed) :
        map_(map),
        location_(location),
        target_(nullptr),
        facing_(Direction::NORTH),
        dPos_(Direction::NULLDIR),
        speed_(speed),
        sprite_(new AnimatedSprite()) {
    location_->enter(this);
}


Walker::~Walker() {
    clearAnimations();
    delete sprite_;
}


void Walker::initSprite(
        Animation const& animationI,
        Animation const& animationN,
        Animation const& animationE,
        Animation const& animationS,
        Animation const& animationW
    ) {
    clearAnimations();

    animations_[Direction::NULLDIR] = new Animation(animationI);
    animations_[Direction::NORTH] = new Animation(animationN);
    animations_[Direction::EAST] = new Animation(animationE);
    animations_[Direction::SOUTH] = new Animation(animationS);
    animations_[Direction::WEST] = new Animation(animationW);

    alignSprite();
}


void Walker::updateLocation(float dt) {
    if (target_) {
        if (target_ == location_) approach(dt);
        else depart(dt);
    }

    updateSprite(dt);
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
    sprite_->update(sf::seconds(dt));

    // float xAbs = location_->x_ + dPos_.x();
    // float yAbs = location_->y_ + dPos_.y();
    // TODO: placment
}


void Walker::alignSprite() {
    if (!animations_.empty()) {
        Animation const* animation;
        if (target_) animation = animations_[facing_];
        else animation = animations_[facing_];

        if (sprite_->getAnimation() != animation)
            sprite_->setAnimation(*animation);
    }
}


void Walker::clearAnimations() {
    for (auto a : animations_) delete a.second;
    animations_.clear();
}
