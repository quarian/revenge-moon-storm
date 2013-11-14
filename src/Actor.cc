#include "Actor.hh"

#include <cmath>

Actor::Actor(
    Map& map,
    MapBlock* block,
    float speed,
    float digPower,
    int health,
    float resistance,
    Inventory* inv) :
        Walker(map, block, speed),
        digging_(false),
        digPower_(digPower),
        health_(health),
        maxHealth_(health),
        vulnerability_(1.0 - resistance),
        inventory_(inv) { }


bool Actor::takeDamage(int dmg) {
    health_ -= round(dmg * vulnerability_);
    return health_ > 0;
}


bool Actor::heal(int amount) {
    if (!isAlive()) return false;
    health_ = fmin(health_ + amount, maxHealth_);
    return true;
}


void Actor::update(float dt) {
    if (!target_)
        findTarget(dt);
    else if (centered() && digging_)
        dig(dt);
    else
        updateLocation(dt);
}


void Actor::dig(float dt) {
/* TODO: uncomment when methods are available
    float timeToDig = target_->getToughness() / digPower_;
    if (dt > timeToDig) {
        target_->weakenAll();
        digging_ = false;
        update(dt - timeToDig);
    } else {
        float digAmount = digPower_ * dt;
        target_->weaken(digAmount);
        if (target_->isPassable()) digging_ = false;
    }
*/
    if (dt == 0) dt = 0; // noop to avoid g++ warning...
    target_->weaken(); // DUMMY
}


void Actor::knock(Direction dir) {
    facing_ = dir;

    target_ = location_->getBlock(facing_);
    if (target_ == nullptr) return;
    else if (!target_->isPassable()) {
        if (isDigger()) digging_ = true;
        else target_ = nullptr;
    }
}


void Actor::proceed() {
    if (!target_->isPassable()) {
        center();
        target_ = nullptr;
    } else {
        target_->enter(this);
        location_->exit(this);
        if (inventory_)
            location_->collect(inventory_);
        location_ = target_;
        dPos_ = -facing_ * 0.5;
    }
}


void Actor::findTarget(float dt) {
    if (dt == 0) dt = 0; // noop to avoid g++ warning...
}
