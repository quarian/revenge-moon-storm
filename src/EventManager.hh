#ifndef __Minebombers__EventManager__
#define __Minebombers__EventManager__
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "WindowManager.hh"
#include "ControlledActor.hh"
#include "dummy_KeySettings.hh"
#include "Player.hh"
#include "Triple.hh"



class EventManager {
public:
    EventManager(WindowManager& w, bool& isRunning) : window_(w), menuKeys_(MenuKeys()), isRunning_(isRunning) {}
    
    void Initialize(std::vector<Player&> players, std::vector<PlayerKeys>& keys);
    
    void EventLoop();
    
private:
    void PlayerEvents(sf::Event&);
    
    WindowManager& window_;
        //std::vector<triple<Player&, PlayerKeys&, std::vector<bool>>> players_;
    MenuKeys menuKeys_;
    bool& isRunning_;
    bool isPaused_;

};


#endif