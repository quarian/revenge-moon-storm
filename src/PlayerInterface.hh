#ifndef MB2_PLAYERINTERFACE_HH
#define MB2_PLAYERINTERFACE_HH

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "PlayerInterface.hh"
#include "KeyInterface.hh"
#include "Direction.hh"

class Player;

class PlayerInterface : public KeyInterface {
public:
    struct KeySet;

    // Some typical keysets
    static const KeySet ARROWS;
    static const KeySet ARROWS_WIDE;
    static const KeySet WASD;
    static const KeySet WASD_DVORAK;

    /* Constructor
     *
     * PARAMETERS
     * ==========
     *  Player&             the player who owns this interface
     *  KeySet              the keyset containing the relevant keys
     */
    PlayerInterface(Player*, const KeySet&);
    
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

    const KeySet& keys_;

    bool useKeyState_;
    bool changeKeyState_;
};


struct PlayerInterface::KeySet {
    Key up;
    Key left;
    Key right;
    Key down;

    Key use;
    Key change;
};


#endif
