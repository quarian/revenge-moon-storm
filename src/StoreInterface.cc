#include "StoreInterface.hh"

StoreInterface::StoreInterface(
        Store* store)
            : store_(store),
              player_(store->getPlayer()),
              buyKeyState_(false),
              sellKeyState_(false) {
                //copy the keys from the player keyset
                auto p_keys = store->getPlayer()->getInterface()->getKeySet();
                keys_.up = p_keys.up;
                keys_.left = p_keys.left;
                keys_.right = p_keys.right;
                keys_.down = p_keys.down;
                keys_.buy = p_keys.use;
                keys_.sell = p_keys.change;
              }


bool StoreInterface::operator==(KeyInterface const& other) const {
    if (StoreInterface const* pi = dynamic_cast<StoreInterface const*>(&other)) {
        return player_ == pi->player_;
    } else return false;
}


void StoreInterface::parse(sf::Event& evt) {
    // Key pressed
    if (evt.type == sf::Event::KeyPressed) {
        if (evt.key.code == keys_.up)    store_->keyDown(Direction::NORTH);
        if (evt.key.code == keys_.left)  store_->keyDown(Direction::WEST);
        if (evt.key.code == keys_.right) store_->keyDown(Direction::EAST);
        if (evt.key.code == keys_.down)  store_->keyDown(Direction::SOUTH);

        if (evt.key.code == keys_.buy)   store_->buyItem();
        if (evt.key.code == keys_.sell)  store_->sellItem();
    }

    // Key released
    // Keyup not needed for store
    /*else if (evt.type == sf::Event::KeyReleased) {
        if (evt.key.code == keys_.up)    store_->keyUp(Direction::NORTH);
        if (evt.key.code == keys_.left)  store_->keyUp(Direction::WEST);
        if (evt.key.code == keys_.right) store_->keyUp(Direction::EAST);
        if (evt.key.code == keys_.down)  store_->keyUp(Direction::SOUTH);
    }*/
}
