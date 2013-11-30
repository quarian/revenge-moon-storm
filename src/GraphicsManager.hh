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
    GraphicsManager(WindowManager& w, sf::Vector2f& blockSize, std::map<std::string, sf::Texture>& textures, std::map<std::string, Animation>& animations) : window_(w), blockSize_(blockSize), textures_(textures) , animations_(animations) { }
    
    /*AnimatedSprite& getAnimatedSprite(std::string name) {
        return animatedSprites_[name];
    }
    sf::Sprite& getSprite(std::string name) {
        return sprites_[name];
    }
    sf::Text getText(std::string name) {
        return texts_[name];
    }*/
    
    void setTexture(sf::Sprite&, std::string );
    
    sf::Texture& getTexture(std::string filename);
    Animation const& getAnimation(std::string name);
    
    void setSpritePosition(std::string name, int x, int y);
    void setAnimatedSpritePosition(std::string name, int x, int y);
    void setTextPosition(std::string name, int x, int y);
    
    void InitializeGraphics(std::string rootPath);
    
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
    
    //std::map<std::string, sf::Sprite> sprites_;
    //std::map<std::string, AnimatedSprite> animatedSprites_;
    std::map<std::string, sf::Text> texts_;
    

    void loadTexture(std::string filename);

};

#endif
