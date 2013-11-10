#include "Actor.hh"

Actor::Actor(Map& map, MapBlock* block, float speed, float digPower, int health=100, float resistance=0.0) :
    Walker(map, block, speed),
    digging_(false),
    digPower_(digPower),
    health_(health),
    maxHealth_(health),
    vulnerability_(1.0 - resistance) { }


bool Actor::takeDamage(int dmg) {
    health_ -= dmg * vulnerability_;
    return health_ > 0;
}


void Actor::update(float dt) {
    if (!target_)
        findTarget(dt);
    else if (!centered())
        updateLocation(dt);
    else if (digging_)
        dig(dt);
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
