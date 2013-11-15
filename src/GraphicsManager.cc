#include "GraphicsManager.hh"
#include <iostream>

void GraphicsManager::InitializeGraphics() {
    
    // TODO
    
    if (!font_.loadFromFile("/Users/roopesavolainen/Documents/C++/mb/minebombers2/src/roope/Minebombers/Minebombers/sansation.ttf")) {
        std::cout << "font load failed";
        return;
    }
    
    /*
    sf::Texture smiletex;
    if (!smiletex.loadFromFile("/Users/roopesavolainen/Documents/C++/mb/minebombers2/src/roope/Minebombers/Minebombers/smile.png")) {
        std::cout << "player image load failed";
        return;
    }
    std::cout<<" load done";
    
    sf::Sprite smile;
    smile.setTexture(smiletex);
    smile.setScale(10, 10);
    sprites_["smile"]=smile;
    */
    sf::Text paused("Paused",font_,50);
    paused.setColor(sf::Color::Yellow);
    texts_["paused"]=paused;
    
}

void GraphicsManager::setSpritePosition(std::string name, int x, int y) {
    sprites_[name].setPosition(x, y);
}

void GraphicsManager::setAnimatedSpritePosition(std::string name, int x, int y) {
    animatedSprites_[name].setPosition(x, y);
}

void GraphicsManager::setTextPosition(std::string name, int x, int y) {
    texts_[name].setPosition(x, y);
}
