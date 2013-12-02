#include "GlobalGameInterface.hh"

GlobalGameInterface::GlobalGameInterface(Game* game, Key exitKey, Key pauseKey)
        : game_(game), exitKey_(exitKey), pauseKey_(pauseKey) {}



bool GlobalGameInterface::operator==(KeyInterface const& other) const {
    if (GlobalGameInterface const* pi = dynamic_cast<GlobalGameInterface const*>(&other)) {
        return game_ == pi->game_;
    } else return false;
}


void GlobalGameInterface::parse(sf::Event& evt) {
    if (evt.type == sf::Event::KeyPressed) {
        // if (evt.key.code == exitKey_)   game_->Shutdown();
        if (evt.key.code == pauseKey_)  game_->togglePause();
    }
}
