#ifndef __Minebombers__game__
#define __Minebombers__game__

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
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
    void Game::UpdateWalkers()
    void DrawWalkers();
    
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

#endif
