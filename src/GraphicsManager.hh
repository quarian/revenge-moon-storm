#ifndef __Minebombers__GraphicsManager__
#define __Minebombers__GraphicsManager__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "AnimatedSprite.hpp"
#include <map>
#include <deque>

#include "WindowManager.hh"

class GraphicsManager {
public:
    GraphicsManager(WindowManager& w, sf::Vector2f& blockSize, std::map<std::string, sf::Texture>& textures,
    				std::map<std::string, Animation>& animations) :
						 	window_(w),
						 	blockSize_(blockSize),
						 	textures_(textures),
						 	animations_(animations),
						 	playerColorsIndex_(0) { }

    // Loads all predefined textures and creates animations
    void InitializeGraphics(std::string rootPath);
    
    // Returns the texture named with the input parameter filename (e.g. texture.png), 
    // loads it from the  graphics folder if it isn't yet initialized.
    sf::Texture& getTexture(std::string filename);
    
    // Returns the animation with the key name.
    Animation const& getAnimation(std::string name);
    
    // Returns new color for each player
    sf::Color getPlayerColor();
    
    void setTextPosition(std::string name, int x, int y);
    

    
private:
    WindowManager& window_;
	
    sf::Vector2f& blockSize_;
    sf::IntRect blockRect_;

    std::string rootPath_;
    std::deque<std::string> pathOptions_;
    void frontToEnd();
    
    std::map<std::string, sf::Texture>& textures_;   
    std::map<std::string, Animation>& animations_;
    sf::Font font_;
    size_t playerColorsIndex_;
    
    //std::map<std::string, sf::Sprite> sprites_;
    //std::map<std::string, AnimatedSprite> animatedSprites_;
    std::map<std::string, sf::Text> texts_;
    

    void loadTexture(std::string filename);

};

#endif
