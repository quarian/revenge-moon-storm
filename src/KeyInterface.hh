#ifndef MB2_KEYINTERFACE_HH
#define MB2_KEYINTERFACE_HH

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

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

class KeyInterface {
protected:
    typedef sf::Keyboard KB;
    typedef sf::Keyboard::Key Key;


public:
    virtual ~KeyInterface() {}

    virtual bool operator==(KeyInterface const& other) const = 0;


    /* Parse the event and, if it's relevant to the interface, pass the
     * command onward.
     */
    virtual bool parse(sf::Event&) = 0;
};

#endif
