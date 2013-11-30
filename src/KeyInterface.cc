#include "KeyInterface.hh"

KeyInterface::KeyInterface(
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



void KeyInterface::parse(sf::Event& evt) {
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


void KeyInterface::readKeyboard() {
    // Movement keys
    if (KB::isKeyPressed(up_))    player_->keyDown(Direction::NORTH);
    else                          player_->keyUp(Direction::NORTH);
    if (KB::isKeyPressed(left_))  player_->keyDown(Direction::WEST);
    else                          player_->keyUp(Direction::WEST);
    if (KB::isKeyPressed(right_)) player_->keyDown(Direction::EAST);
    else                          player_->keyUp(Direction::EAST);
    if (KB::isKeyPressed(down_))  player_->keyDown(Direction::SOUTH);
    else                          player_->keyUp(Direction::SOUTH);

    // Use Item key
    if (KB::isKeyPressed(use_)) {
        if (!useKeyState_) {
            player_->useItem();
            useKeyState_ = true;
        }
    } else useKeyState_ = false;

    // Change Weapon (item) key
    if (KB::isKeyPressed(change_)) {
        if (!changeKeyState_) {
            player_->changeWeapon();
            changeKeyState_ = true;
        }
    } else changeKeyState_ = false;
}
