#include "GraphicsManager.hh"
#include <iostream>

void GraphicsManager::InitializeGraphics(std::string rootPath) {
    rootPath_=rootPath + "/graphics";

    //blockSize.getBlockScale();
    blockSize_ = sf::Vector2f(10,10);
    
    
    blockRect_ = sf::IntRect(sf::Vector2i(10,10),sf::Vector2i(10,10));
    
    // TODO Linkataan kaikille mapin olioille grafiikat...

    // Load textures
    if (!font_.loadFromFile(rootPath_+"/fonts/sansation.ttf")) {
        std::cout << "font load failed";
        return;
    }
    
    sf::Texture sand;
    if (!sand.loadFromFile(rootPath_+"/blocks/sand.png",blockRect_)) {
        std::cout << "player image load failed";
        return;
    }
    textures_["sand.png"]=sand;
    
    sf::Texture rock;
    if (!rock.loadFromFile(rootPath_+"/blocks/rock.png",blockRect_)) {
        std::cout << "player image load failed";
        return;
    }
    textures_["rock.png"]=rock;
    
    
    
    


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
    sf::Text paused("Paused",font_,50);
    paused.setColor(sf::Color::Yellow);
    texts_["paused"]=paused;
    
}
sf::Texture GraphicsManager::getTexture(std::string filepath) {
    if (textures_.find(filepath)==textures_.end()) {
        sf::Texture text;
        std::string path=rootPath_+filepath;
        if (!text.loadFromFile(path,blockRect_)) {
            std::cout << "Texture "+filepath+"load failed";
            throw;
        }
        else return text;
    }
    else return textures_[filepath];
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