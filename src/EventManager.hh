#ifndef __Minebombers__EventManager__
#define __Minebombers__EventManager__
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <list>
#include <vector>

#include "WindowManager.hh"
#include "Player.hh"
#include "Triple.hh"
#include "dummy_KeySettings.hh"
#include "KeyInterface.hh"


class EventManager {
public:
    
    EventManager(WindowManager& w, bool& isRunning) :
    	window_(w), 
        isRunning_(isRunning),
    	menuKeys_(MenuKeys()) {}

    ~EventManager() { clearInterfaces(); }
    

    /* Keyboard interfaces
     *
     * Keyboard interfaces are listeners that receive all key press and release
     * events that this EventManager encounters. The caller dynamically creates
     * each KeyInterface, and registering transfers ownership to the
     * EventManager.
     */
    void registerInterface(KeyInterface*);
    // void unregisterInterface(KeyInterface*);
    void clearInterfaces();

    
    void EventLoop(sf::Event&);
    
    // If returning false return main menu, else start the gameplay
    bool StoreEventLoop(sf::Event&);
    
private:
    void PlayerEvents(sf::Event&);
    
    void BuyingEvents(sf::Event&, std::vector<bool>&);
    
    WindowManager& window_;
    std::list<KeyInterface*> keyInterfaces_;

    bool& isRunning_;
    MenuKeys menuKeys_;
    // bool& isPaused_;
};


#endif
