#ifndef __Minebombers__game__
#define __Minebombers__game__

#include <SFML/Audio.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <SFML/System/Clock.hpp>
#include <SFML/System/String.hpp>

#include <iostream>
#include <list>
#include <map>
    //#include <time.h>


#include "Walker.hh"
#include "Actor.hh"
#include "dummy_KeySettings.hh"
#include "dummy_Map.hh"
    //#include "dummy_MapBlock.hh"

#include "dummy_Player.hh"



/*****************************************************************
Game: Initializes a new game, updates and draws the game situation
******************************************************************/

class Game {
public:
    Game(sf::RenderWindow& win) : isRunning_(true), isPaused_(false), window_(win) { }
    
    void Run() {
        Initialize();
        while (window_.isOpen() && isRunning_) {
            Update();
            Draw();
        }
        Shutdown();
    }
    sf::RenderWindow& getWindow() { return window_; }
    
private:
    void Initialize();      // Initialize
    
    void Update();          // Update game situation, the highest level update function
    void UpdateActors(sf::Event);
    
    void Draw();            // Draw game
    
    void Pause();
    
    void Shutdown();
    
    bool isRunning_;
    bool isPaused_;
    
    sf::RenderWindow& window_;
    sf::Clock clock_;
    CommonKeys commonkeys_;
    std::list<dummyPlayer> actors_;
    
    std::map<std::string, sf::Texture > textures_;
    std::map<std::string, std::list<sf::Text> > texts_;
    
    sf::Font font_;

    
};




#endif
