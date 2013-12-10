#include "CheatsInterface.hh"

CheatsInterface::CheatsInterface(bool& flagVictory) : flagVictory_(flagVictory) {}


bool CheatsInterface::parse(sf::Event& evt) {
    if (evt.type == sf::Event::KeyPressed) {
        if (evt.key.code == KB::F7) flagVictory_ = true;
        return true;
    }
    return false;
}
