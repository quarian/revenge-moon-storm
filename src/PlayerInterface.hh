#ifndef MB2_PLAYERINTERFACE_HH
#define MB2_PLAYERINTERFACE_HH

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "KeyInterface.hh"
#include "Direction.hh"
#include "Player.hh"

class PlayerInterface : public KeyInterface {
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
    PlayerInterface(Player*, Key=KB::Up, Key=KB::Left, Key=KB::Right, Key=KB::Down, Key=KB::L, Key=KB::K);
    
    bool operator==(KeyInterface const& other) const; // override


    /* Parse the event and, if it's relevant to the owning player, pass the
     * command onward.
     */
    void parse(sf::Event&); // override


    /* Getter and setter for the associated player. */
    Player* getPlayer() { return player_; }
    void setPlayer(Player* player) { player_ = player; }

    
private:
    Player* player_;

    Key up_;
    Key left_;
    Key right_;
    Key down_;

    Key use_;
    Key change_;

    bool useKeyState_;
    bool changeKeyState_;
};

#endif
