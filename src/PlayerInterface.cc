#include "PlayerInterface.hh"
#include "Player.hh"

PlayerInterface::PlayerInterface(
        Player* player,
        const KeySet& keys)
            : player_(player),
              keys_(keys),
              useKeyState_(false),
              changeKeyState_(false) {}


bool PlayerInterface::operator==(KeyInterface const& other) const {
    if (PlayerInterface const* pi = dynamic_cast<PlayerInterface const*>(&other)) {
        return player_ == pi->player_;
    } else return false;
}


bool PlayerInterface::parse(sf::Event& evt) {
    // Key pressed
    if (evt.type == sf::Event::KeyPressed) {
        if (evt.key.code == keys_.up)    {  player_->keyDown(Direction::NORTH);
        									return true; }
        if (evt.key.code == keys_.left)  {  player_->keyDown(Direction::WEST);
        									return true; }
        if (evt.key.code == keys_.right) {  player_->keyDown(Direction::EAST);
        									return true; }
        if (evt.key.code == keys_.down)  {  player_->keyDown(Direction::SOUTH);
        									return true; }

        if (evt.key.code == keys_.use)    { player_->useItem();
        									return true; }
        if (evt.key.code == keys_.change) { player_->changeWeapon();
        									return true; }
    }

    // Key released
    else if (evt.type == sf::Event::KeyReleased) {
        if (evt.key.code == keys_.up)    { player_->keyUp(Direction::NORTH);
        									return true; }
        if (evt.key.code == keys_.left)  { player_->keyUp(Direction::WEST);
        									return true; }
        if (evt.key.code == keys_.right) { player_->keyUp(Direction::EAST);
        									return true; }
        if (evt.key.code == keys_.down)  { player_->keyUp(Direction::SOUTH);
        									return true; }
    }
    
    return false;
}


const PlayerInterface::KeySet PlayerInterface::ARROWS = {
    sf::Keyboard::Up, sf::Keyboard::Left,
    sf::Keyboard::Right, sf::Keyboard::Down,
    sf::Keyboard::RControl, sf::Keyboard::RShift };

const PlayerInterface::KeySet PlayerInterface::ARROWS_WIDE = {
    sf::Keyboard::Up, sf::Keyboard::Left,
    sf::Keyboard::Right, sf::Keyboard::Down,
    sf::Keyboard::Space, sf::Keyboard::LAlt };

const PlayerInterface::KeySet PlayerInterface::WASD = {
    sf::Keyboard::W, sf::Keyboard::A,
    sf::Keyboard::D, sf::Keyboard::S,
    sf::Keyboard::Space, sf::Keyboard::LAlt };

const PlayerInterface::KeySet PlayerInterface::WASD_DVORAK = {
    sf::Keyboard::Comma, sf::Keyboard::A,
    sf::Keyboard::E, sf::Keyboard::O,
    sf::Keyboard::Space, sf::Keyboard::LAlt };
