#ifndef __Minebombers__EventManager__
#define __Minebombers__EventManager__
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include "WindowManager.hh"
#include "Player.hh"
#include "Triple.hh"
#include "dummy_KeySettings.hh"




class EventManager {
public:
    
    EventManager(WindowManager& w, bool& isRunning) : window_(w), menuKeys_(MenuKeys()), isRunning_(isRunning) {}
    
    void Initialize(std::vector<Player>& players, std::vector<PlayerKeys>& keys);
    
    void EventLoop(sf::Event&);
    
    // If returning false return main menu, else start the gameplay
    bool StoreEventLoop(sf::Event&);
    
private:
    void PlayerEvents(sf::Event&);
    
    void BuyingEvents(sf::Event&, std::vector<bool>&);
    
    WindowManager& window_;
    std::vector<Triple<Player, PlayerKeys, std::vector<bool>>> players_;
    MenuKeys menuKeys_;
    bool& isRunning_;
    bool isPaused_;

};


#endif
