#include "Player.hh"


Player::Player(std::string name, size_t lives) : name_(name), lives_(lives) { }


ControlledActor* Player::spawn(Map* map, MapBlock* block) {
    clearAvatar();
    avatar_ = new ControlledActor(*map, block, speed_, digPower_, 100, resistance_, &inventory_);
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


void Player::useItem() {
    //if (avatar_)
    //    inventory_.useCurrent(avatar_->getLocation(), avatar_->getDirection());
}


void Player::die() {
    if (clearAvatar()) lives_ -= 1;
}


bool Player::clearAvatar() {
    if (avatar_) {
        delete avatar_;
        return true;
    }
    return false;
}
