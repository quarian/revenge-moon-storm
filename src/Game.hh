#ifndef __Minebombers__game__
#define __Minebombers__game__

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/String.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "WindowManager.hh"
#include "Player.hh"
#include "Map.hh"
#include "GraphicsManager.hh"
#include "EventManager.hh"

#include "dummy_KeySettings.hh"

class Game {
public:
    Game();
    
    void Launch();
    
    sf::Clock& getClock() {return clock_;}
    
private:
    void MainLoop();
    void HandleEvents();
    void Update();
    void Draw();
    void Shutdown();
    
    void InitializeMap();
    void UpdateMap();
    void DrawMap();
    
    void InitializeWalkers(size_t playerCount);
    void UpdateWalkers();
    void DrawWalkers();
    
    std::string rootPath_;
    
    WindowManager window_;
    EventManager eventManager_;
    GraphicsManager graphicsManager_;
    
    bool isRunning_;
    std::vector<sf::Sprite> mapSprites_;
    std::vector<Player> players_;
    std::vector<PlayerKeys> playerKeySettings_;
    std::vector<Item> items_;
    
    Map map_;
    size_t mapWidth_;
    size_t mapHeight_;
    sf::Vector2f blockSize_;
    
    std::map<std::string, Animation> animations_;
    std::map<std::string, sf::Texture> textures_;
    
    sf::Clock clock_;
};



/*****************************************************************
Game: Initializes a new game, updates and draws the game situation
******************************************************************/

//class Game {
//public:
//    Game() : isRunning_(false), inStore_(false)/*,graphicsManager_(window_)*//*, eventManager_(window_, isRunning_)*/ { }
//    
//    void Launch();
//
//        //WindowManager& getWindow() { return window_; }
//        
//private:
//    void Run() {
//        while (window_.isOpen() && isRunning_) {
//            Update();
//            Draw();
//            sf::sleep(sf::seconds(1));
//        }
//        Shutdown();
//    }
//    
//    void Initialize(Map&,size_t,size_t);
//    void HandleEvents();
//    void Update();
//    void Draw();
//    void Pause();
//    void Shutdown();
//    std::vector<size_t> Menu(); //Return player count and player lives
//    
//    bool isRunning_;
//    bool inStore_;
//    
//    WindowManager window_;
//        //GraphicsManager graphicsManager_;
//        //EventManager eventManager_;
//    
//    Map map_;
//    sf::Clock clock_;
//    
//        //std::vector<Player> players_;
//        //std::vector<PlayerKeys> playerKeySettings_;
//
//    
//};




#endif
