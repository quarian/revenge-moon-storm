#include "PlayerInterface.hh"

PlayerInterface::PlayerInterface(
        Player* player,
        Key up,
        Key left,
        Key right,
        Key down,
        Key use,
        Key change)
            : player_(player),
              up_(up),
              left_(left),
              right_(right),
              down_(down),
              use_(use),
              change_(change),
              useKeyState_(false),
              changeKeyState_(false) {}


bool PlayerInterface::operator==(KeyInterface const& other) const {
    if (PlayerInterface const* pi = dynamic_cast<PlayerInterface const*>(&other)) {
        return player_ == pi->player_;
    } else return false;
}


void PlayerInterface::parse(sf::Event& evt) {
    // Key pressed
    if (evt.type == sf::Event::KeyPressed) {
        if (evt.key.code == up_)    player_->keyDown(Direction::NORTH);
        if (evt.key.code == left_)  player_->keyDown(Direction::WEST);
        if (evt.key.code == right_) player_->keyDown(Direction::EAST);
        if (evt.key.code == down_)  player_->keyDown(Direction::SOUTH);

        if (evt.key.code == use_)    player_->useItem();
        if (evt.key.code == change_) player_->changeWeapon();
    }

    // Key released
    else if (evt.type == sf::Event::KeyReleased) {
        if (evt.key.code == up_)    player_->keyUp(Direction::NORTH);
        if (evt.key.code == left_)  player_->keyUp(Direction::WEST);
        if (evt.key.code == right_) player_->keyUp(Direction::EAST);
        if (evt.key.code == down_)  player_->keyUp(Direction::SOUTH);
    }
}