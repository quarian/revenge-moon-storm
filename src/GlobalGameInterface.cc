#include "GlobalGameInterface.hh"

GlobalGameInterface::GlobalGameInterface(World* world, Key exitKey, Key pauseKey)
        : world_(world), exitKey_(exitKey), pauseKey_(pauseKey) {}



bool GlobalGameInterface::operator==(KeyInterface const& other) const {
    if (GlobalGameInterface const* pi = dynamic_cast<GlobalGameInterface const*>(&other)) {
        return world_ == pi->world_;
    } else return false;
}


void GlobalGameInterface::parse(sf::Event& evt) {
    if (evt.type == sf::Event::KeyPressed) {
        // if (evt.key.code == exitKey_)   game_->Shutdown();
        // if (evt.key.code == pauseKey_)  world_->pause();
    }
}
