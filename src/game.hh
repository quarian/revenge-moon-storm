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
#include <vector>
#include <map>
    //#include <time.h>


#include "Walker.hh"
#include "Actor.hh"
#include "MapBlock.hh"
#include "Map.hh"
#include "WindowManager.hh"

#include "dummy_KeySettings.hh"
#include "dummy_Player.hh"

#include "MapBlock.hh"




/*****************************************************************
Game: Initializes a new game, updates and draws the game situation
******************************************************************/

class Game {
public:
    Game() : window_(), isRunning_(true), isPaused_(false), map_() {
            //sf::RenderWindow window_(sf::VideoMode(800,600),"GameWindow");
    }
    
    void Run() {
        Initialize(2,map_, textures_);
        while (window_.isOpen() && isRunning_) {
            Update();
            Draw();
        }
        Shutdown();
    }
    sf::RenderWindow& getWindow() { return window_; }
    
private:
    void Initialize(int playerCount, Map&, std::map<std::string,sf::Texture>& textures_);      // Initialize
    
    void Update();          // Update game situation, the highest level update function
    void UpdateActors(sf::Event);   //Subfunction for Update()
    
    void Draw();            // Draw game
    
    void Pause();
    
    void Shutdown();
    
    bool isRunning_;
    bool isPaused_;
    
        //sf::RenderWindow
    WindowManager window_;
    sf::Clock clock_;
    MenuKeys commonkeys_;
    std::list<dummyPlayer> actors_;
        //std::vector<*Walker>
    std::vector<Walker> players;
    
    
    std::map<std::string, sf::Texture > textures_;
    std::map<std::string, std::list<sf::Text> > texts_;
    
    Map map_;
    
    sf::Font font_;

    
};




#endif
