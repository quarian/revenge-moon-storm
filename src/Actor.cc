#include "Actor.hh"

#include <cmath>
#include <iostream>

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
        digPowerInitial_(digPower),
        health_(health),
        maxHealth_(health),
        vulnerability_(1.0 - resistance),
        inventory_(inv) {
}


Actor::~Actor() {
    location_->exit(this);
}


bool Actor::takeDamage(float dmg) {
    health_ -= dmg * vulnerability_;
    return health_ > 0;
}


bool Actor::heal(float amount) {
    if (!isAlive()) return false;
    health_ = fmin(health_ + amount, maxHealth_);
    return true;
}


void Actor::update(float dt) {
    if (inventory_)
        digPower_ = digPowerInitial_ + inventory_->getExtraMiningPower();

    if (!target_)
        findTarget(dt);
    else if (centered() && digging_)
        dig(dt);
    else
        updateLocation(dt);
    updateSprite(dt);
}

void Actor::initSprite(Animation const& walking, Animation const& digging, sf::Color color) {
    sprite_.setAnimation(walking);
    sprite_.setColor(color);
    sprite_.setOrigin(8,8);
    
    spriteDigger_.setAnimation(digging);
    spriteDigger_.setColor(color);
    spriteDigger_.setFrameTime(sf::milliseconds(90));
    spriteDigger_.setOrigin(8,8);
    
    updateSprite(0.0);
}

void Actor::initSprite(Animation const& walking, sf::Color color) {
    sprite_.setAnimation(walking);
    sprite_.setColor(color);
    sprite_.setOrigin(8,8);
    
    updateSprite(0.0);
}

AnimatedSprite& Actor::getSprite() {
	if (digging_) {
		return spriteDigger_;
	}
	return sprite_;
}

void Actor::dig(float dt) {
    float timeToDig = target_->getToughness() / digPower_;
    if (dt > timeToDig) {
        target_->clear();
        digging_ = false;
        update(dt - timeToDig);
    } else {
        float digAmount = digPower_ * dt;
        target_->weaken(digAmount);
        if (target_->isPassable()) digging_ = false;
    }
    // target_->weaken(dt * digPower_); // DUMMY
}


void Actor::knock(Direction dir) {
    facing_ = dir;
    digging_ = false;

    target_ = location_->getBlock(facing_);
    if (target_ == nullptr) return;
    else if (!target_->isPassable()) {
        if (target_->isDiggable() && isDigger()) digging_ = true;
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
                         // This isn't pure virtual to facilitate tests
}
