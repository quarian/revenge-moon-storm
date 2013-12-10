#ifndef MB2_MENUINTERFACE_HH
#define MB2_MENUINTERFACE_HH

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "KeyInterface.hh"
//#include "KeyInterface.hh"
#include "Menu.hh"

class Menu;

class MenuInterface : public KeyInterface {
public:
    /* Constructor
     *
     * PARAMETERS
     * ==========
     *  Menu*               the menu that's being controlled by this interface
     */
    MenuInterface(Menu*);
    bool operator==(KeyInterface const& other) const;

    /* Parse the event and, if it's relevant to the menu, act on it. */
    bool parse(sf::Event&);

    
private:
    Menu* menu_;


};



#endif
