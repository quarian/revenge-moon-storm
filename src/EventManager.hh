#ifndef __Minebombers__EventManager__
#define __Minebombers__EventManager__
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include "WindowManager.hh"
#include "ControlledActor.hh"
#include "dummy_KeySettings.hh"
#include <list>
#include <vector>
#include <utility>


class EventManager {
public:
    EventManager(WindowManager& w, std::vector<ControlledActor/*Player*/> actors, bool& isRunning) : window_(w), menuKeys_(MenuKeys()), isRunning_(isRunning) {
        std::vector<bool> activeInput(7,false);
        int playerCount = actors.size();
        PlayerKeys keys = PlayerKeys();
        for (int i=0; i<playerCount; i++) {
            std::pair<PlayerKeys,std::vector<bool>> io(keys,activeInput);
            std::pair<ControlledActor/*Player*/,std::pair<PlayerKeys,std::vector<bool>> > triple(actors[i],io);

            players_.push_back(triple);
        }
    }
    
    void EventLoop();
    void PlayerEvents(sf::Event&);
    
    ControlledActor& getActor(int i) {
            return players_[i].first;
    }
        
    PlayerKeys& getKeys(int i) {
        return players_[i].second.first;
    }
    std::vector<bool>& getActiveInput(int i) {
        return players_[i].second.second;
    }

    
private:
    WindowManager& window_;
    std::vector<std::pair<ControlledActor/*Player*/,std::pair<PlayerKeys,std::vector<bool>>> players_;
    MenuKeys menuKeys_;
    bool& isRunning_;
    bool isPaused_;
    
};


#endif