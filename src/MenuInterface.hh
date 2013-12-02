#ifndef MB2_MENUINTERFACE_HH
#define MB2_MENUINTERFACE_HH

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "KeyInterface.hh"
#include "Direction.hh"
#include "Player.hh"

class MenuInterface : public KeyInterface {
public:
    /* Constructor
     *
     * PARAMETERS
     * ==========
     *  Menu*               the menu that's being controlled by this interface
     *
     *  Key                 key to SELECT OPTION
     *  Key                 key to GO BACK
     */
    MenuInterface(Player*, Key=KB::Enter, Key=KB::Backspace);
    
    bool operator==(KeyInterface const& other) const override;


    /* Parse the event and, if it's relevant to the menu, act on it. */
    void parse(sf::Event&) override;

    
private:
    Menu* menu_;

    Key select_;
    Key back_;
};

#endif
