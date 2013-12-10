#ifndef MB2_EDITOR_INTERFACE_HH
#define MB2_EDITOR_INTERFACE_HH

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

#include "PlayerInterface.hh"
#include "KeyInterface.hh"

class MapEditor;

class EditorInterface : public KeyInterface {
public:
    
    EditorInterface(MapEditor&);
    
    bool operator==(KeyInterface const& other) const; // override

    bool parse(sf::Event&); // override

private:
    MapEditor& editor_;

    
};

#endif
