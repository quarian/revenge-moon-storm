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
    void main();

    sf::Vector2f blockSize_;

    void draw(sf::Drawable& drawable) { window_.draw(drawable); }


private:
    void handleEvents();
    void terminate();

    GameState* stack_;
    bool isRunning_;
    std::string rootPath_;
    
    WindowManager window_;
    
    sf::Sprite background_;
    std::map<std::string, Animation> animations_;
    std::map<std::string, sf::Texture> textures_;
    std::map<std::string, sf::Font> fonts_;
    
    sf::Clock clock_;


public:
    EventManager eventManager_;
    GraphicsManager graphicsManager_;
    TerrainManager terrainManager_;
};

#endif
