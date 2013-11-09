#ifndef __Minebombers__GraphicsManager__
#define __Minebombers__GraphicsManager__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "AnimatedSprite.hpp"
#include <map>

#include "WindowManager.hh"

class GraphicsManager {
public:
    GraphicsManager(WindowManager& w) : window_(w) { }
    
    AnimatedSprite& getAnimatedSprite(std::string name) {
        return animatedSprites_[name];
    }
    sf::Sprite& getSprite(std::string name) {
        return sprites_[name];
    }
    sf::Text& getText(std::string name) {
        return texts_[name];
    }
    
    void setSpritePosition(std::string name, int x, int y);
    void setAnimatedSpritePosition(std::string name, int x, int y);
    void setTextPosition(std::string name, int x, int y);
    
    void InitializeGraphics();
    
private:
    std::map<std::string, sf::Sprite> sprites_;
    std::map<std::string, AnimatedSprite> animatedSprites_;
    std::map<std::string, sf::Text> texts_;
    sf::Font font_;
    
    WindowManager& window_;
};

#endif