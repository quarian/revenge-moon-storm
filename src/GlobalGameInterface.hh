#ifndef MB2_GLOBALGAMEINTERFACE_HH
#define MB2_GLOBALGAMEINTERFACE_HH

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "KeyInterface.hh"
#include "World.hh"

/* KeyInterface
 *
 * Abstract base class for all keyboard-based input receiving (when an instance
 * is registered to an EventManager, all key press and release events that the
 * EventManager receives in its EventLoop are run by that KeyInterface instance.
 * 
 * The KeyInterface should know how the information needs to be handled -- for
 * example, if it is a controller interface for a player character, it should
 * keep a pointer to the Player object that it's controlling and take care of
 * instructing it as required.
 */

class World;

class GlobalGameInterface : public KeyInterface {
public:
    /* Constructor
     *
     * PARAMETERS
     * ==========
     *  Game*               the Game object that this interface is controlling
     *
     *  Key                 key to EXIT the game
     *  Key                 key to PAUSE the game
     */
    GlobalGameInterface(World*, Key=KB::F10, Key=KB::Pause);

    bool operator==(KeyInterface const& other) const; // override


    /* Parse the event and, if it's relevant to the interface, pass the
     * command onward.
     */
    virtual bool parse(sf::Event&);

private:
    World* world_;

    Key exitKey_;
    Key pauseKey_;
};

#endif
