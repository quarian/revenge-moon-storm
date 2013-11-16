#include "GraphicsManager.hh"
#include <iostream>

void GraphicsManager::InitializeGraphics() {
    
    // Load textures
    if (!font_.loadFromFile("/graphics/fonts/sansation.ttf")) {
        std::cout << "font load failed";
        return;
    }

    //blockSize.getBlockScale(); // Window size scaling windowsize/mapsize after texture loading for realtime...
    blockSize_ = sf::Vector2f(10,10);
    sf::IntRect blockRect(sf::Vector2i(10,10),sf::Vector2i(10,10));

    sf::Texture sand;
    if (!sand.loadFromFile("graphics/blocks/sand.png",blockRect)) {
        std::cout << "player image load failed";
        return;
    }
    textures_["sand"]=sand;
    
    sf::Texture rock;
    if (!rock.loadFromFile("/graphics/blocks/rock.png",blockRect)) {
        std::cout << "player image load failed";
        return;
    }
    textures_["rock"]=rock;

    sf::Text paused("Paused",font_,50);
    paused.setColor(sf::Color::Yellow);
    texts_["paused"]=paused;
    
    
    /*Animation blue_player;
    sf::IntRect player_rect;
    player_rect.
    blue_player.addFrame(player_rect);
    */
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
    
}

void GraphicsManager::setTexture(sf::Sprite& sprite, std::string name) {
    sprite.setTexture(textures_[name]);
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