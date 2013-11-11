#include "Player.hh"


Player::Player(size_t lives) : lives_(lives) { }


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
