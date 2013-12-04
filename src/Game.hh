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
#include "GameState.hh"

#include "dummy_KeySettings.hh"

class GameState;

class Game {
public:
    Game();
    // sf::Clock& getClock() { return clock_; }

    // void initialize();
    void main();

    EventManager eventManager_;
    GraphicsManager graphicsManager_;
    TerrainManager terrainManager_;

    sf::Vector2f blockSize_;

    void draw(sf::Drawable& sprite) { window_.draw(sprite); }

    //static Game* singleton;


private:
    //void MainLoop();
    void handleEvents();
    void terminate();
    // void Update();
    // void Draw();
    // void Shutdown();
    
    // void InitializeMap(std::string);
    // void UpdateMap();
    // void DrawMap();
    // 
    // void InitializeWalkers(size_t playerCount);
    // void UpdateWalkers();
    // void DrawWalkers();

    GameState* stack_;
    bool isRunning_;
    std::string rootPath_;
    
    WindowManager window_;
    
    // bool isPaused_;
    // std::vector<sf::Sprite> mapSprites_;
    // std::vector<sf::Sprite> playerSprites_;
    // std::vector<Player*> players_;
    // std::vector<PlayerKeys> playerKeySettings_;
    // std::vector<Item> items_;
    
    // Map map_;
    // size_t mapWidth_;
    // size_t mapHeight_;
    
    sf::Sprite background_;
    std::map<std::string, Animation> animations_;
    std::map<std::string, sf::Texture> textures_;
    
    sf::Clock clock_;
    // sf::Time elapsedTime_;
};

#endif
