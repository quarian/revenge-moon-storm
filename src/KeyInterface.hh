#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "Direction.hh"
#include "Player.hh"

class KeyInterface {
    typedef sf::Keyboard KB;
    typedef sf::Keyboard::Key Key;

public:
    /* Constructor
     *
     * PARAMETERS
     * ==========
     *  Player&             the player who owns this interface
     *
     *  Key                 key to move UP
     *  Key                 key to move LEFT
     *  Key                 key to move RIGHT
     *  Key                 key to move DOWN
     *
     *  Key                 key to USE ITEM
     *  Key                 key to CYCLE ITEM
     */
    KeyInterface(Player&, Key=KB::Up, Key=KB::Left, Key=KB::Right, Key=KB::Down, Key=KB::L, Key=KB::K);


    /* Parse the event and, if it's relevant to the owning player, pass the
     * command onward. */
    void parse(sf::Event&);


private:
    Player& player_;

    Key up_;
    Key left_;
    Key right_;
    Key down_;

    Key use_;
    Key change_;
};
