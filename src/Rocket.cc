#include "Rocket.hh"
#include "MapBlock.hh"
#include "Map.hh"
#include "GraphicsManager.hh"
#include "Game.hh"
#include "Item.hh"

#include <iostream>


Rocket::Rocket(Map& map, MapBlock* mb, Direction dir) :
        AIPlayerSeeker(map, mb, 0, 22.0, 1, 1), dir_(dir) {
    initSprite(map.getGame()->graphicsManager_.getAnimation("rocket"),
               sf::Color::White);
    sprite_.setFrameTime(sf::seconds(0.03f));
}


void Rocket::think() {
    MapBlock* newTarget = location_->getBlock(dir_);
    if (!newTarget) explode();
    else if (newTarget->hasWalkers()) explode();
    else pushPath(newTarget);
}

void Rocket::update(float dt) {
    if (isAlive()) {
        if (location_->hasWalkers(this)) explode();
        else if (target_ && !target_->isPassable()) explode();
        else AIPlayerSeeker::update(dt);
    }
}

void Rocket::explode() {
    health_ = -100;
    map_.blast(1.8, 30, location_);
}

bool Rocket::takeDamage(float) {
    if (isAlive()) {
        explode();
    }
    return true;
}
