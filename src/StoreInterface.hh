#ifndef MB2_STOREINTERFACE_HH
#define MB2_STOREINTERFACE_HH

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "KeyInterface.hh"
#include "Player.hh"
#include "Store.hh"

class StoreInterface : public KeyInterface {
public:
    struct KeySet { //This is here so we dont need to pass it as pointer or reference
        Key up;
        Key left;
        Key right;
        Key down;

        Key buy;
        Key sell;
    };

    StoreInterface(Store*);
    bool operator==(KeyInterface const& other) const; // overridé
    bool parse(sf::Event&); // override


    
private:
    Store* store_;
    Player* player_;

    bool buyKeyState_;
    bool sellKeyState_;

    KeySet keys_;
};





#endif
