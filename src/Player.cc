#include "Player.hh"

#include <iostream>


Player::Player(std::string name, size_t lives) :
    speed_(2.0f),
    digPower_(2.0f),
    resistance_(0.0f),
    lives_(lives),
    name_(name),
    currentItem_(""),
    avatar_(nullptr) { }

Player::~Player() {
    clearAvatar();
}


ControlledActor* Player::spawn(Map& map, MapBlock* block) {
    clearAvatar();
    avatar_ = new ControlledActor(map, block, speed_, digPower_, 100, resistance_, &inventory_);
    return avatar_;
}


void Player::keyUp(Direction dir) {
    if (avatar_)
        avatar_->keyUp(dir);
}


void Player::keyDown(Direction dir) {
    if (avatar_)
        avatar_->keyDown(dir);
}


void Player::changeWeapon() {
    currentItem_ = inventory_.getNextItem(currentItem_);
}


void Player::useItem() {
    if (avatar_)
        inventory_.useItem(currentItem_, avatar_->getLocation()->getMap(), avatar_->getLocation(), avatar_->getDirection() );
}


void Player::die() {
    if (clearAvatar()) lives_ -= 1;
}


bool Player::clearAvatar() {
    if (avatar_) {
        delete avatar_;
        avatar_ = nullptr;
        return true;
    }
    return false;
}
