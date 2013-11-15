#ifndef __Minebombers__game__
#define __Minebombers__game__

#include <SFML/Audio.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <SFML/System/Clock.hpp>
#include <SFML/System/String.hpp>

#include <iostream>
#include <vector>
#include <map>


#include "WindowManager.hh"
#include "Player.hh"
#include "Map.hh"
#include "GraphicsManager.hh"
#include "EventManager.hh"

#include "dummy_KeySettings.hh"
    //#include "Drawable.hh"
    //#include "dummy_Player.hh"



/*****************************************************************
Game: Initializes a new game, updates and draws the game situation
******************************************************************/

class Game {
public:
    Game() : isRunning_(false), graphicsManager_(window_), eventManager_(window_, isRunning_) { }
    
    void Launch();

    WindowManager& getWindow() { return window_; }
        
private:
    void Run() {
        while (window_.isOpen() && isRunning_) {
            Update();
            Draw();
        }
        Shutdown();
    }
    
    void Initialize(Map&,size_t,size_t);
    void Update();
    void Draw();
    void Pause();
    void Shutdown();
    bool isRunning_;
    std::vector<size_t> Menu(); //Return player count and player lives
    
    
    WindowManager window_;
    GraphicsManager graphicsManager_;
    EventManager eventManager_;
    
    Map map_;
    sf::Clock clock_;
    
    std::vector<Player> players_;
    std::vector<PlayerKeys> playerKeySettings_;
};


#endif
