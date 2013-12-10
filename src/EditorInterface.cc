#include "EditorInterface.hh"
#include <iostream>
#include "MapEditor.hh"

EditorInterface::EditorInterface(MapEditor& editor) : editor_(editor) {}


bool EditorInterface::operator==(KeyInterface const& other) const {
    return false;
}


bool EditorInterface::parse(sf::Event& event) {
    // Key pressed
    if (event.type == sf::Event::MouseButtonPressed) {
        editor_.handleInput(event.mouseButton.x, event.mouseButton.y);
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Z) editor_.setBrush(' ');
        if (event.key.code == sf::Keyboard::X) editor_.setBrush('s');
        if (event.key.code == sf::Keyboard::C) editor_.setBrush('S');
        if (event.key.code == sf::Keyboard::V) editor_.setBrush('W');
        if (event.key.code == sf::Keyboard::B) editor_.setBrush('#');;
        if (event.key.code == sf::Keyboard::S) editor_.saveMap();
    }
    return false;
}
