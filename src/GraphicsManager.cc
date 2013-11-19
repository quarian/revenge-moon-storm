#include "GraphicsManager.hh"
#include <iostream>

void GraphicsManager::InitializeGraphics(std::string rootPath) {
    rootPath_=rootPath + "/graphics/";

    //blockSize.getBlockScale();
    blockSize_ = sf::Vector2f(10,10);
    
    
    blockRect_ = sf::IntRect(sf::Vector2i(10,10),sf::Vector2i(10,10));
    
    // TODO Linkataan kaikille mapin olioille grafiikat...

    // Load textures
    if (!font_.loadFromFile(rootPath_+"/fonts/sansation.ttf")) {
        std::cout << "font load failed";
        return;
    }
    
    loadTexture("sand.png");
    loadTexture("rock.png");
    loadTexture("sand_.png");

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
sf::Texture GraphicsManager::getTexture(std::string filename) {
    if (textures_.find(filename)==textures_.end()) {
        loadTexture(filename);
        return textures_[filename];
    }
    else return textures_[filename];
}

void GraphicsManager::loadTexture(std::string filename) {
    if (textures_.find(filename)==textures_.end()) {
        sf::Texture text;
        std::string path=rootPath_;
        std::vector<std::string> pathOptions = {"blocks/","players/","items/","misc/","fonts/"};
        int i = 0;
        if (text.loadFromFile(path+filename,blockRect_)) {
            textures_[filename] = text;
        }
        else if (text.loadFromFile(path+pathOptions[i]+filename,blockRect_)) {
            textures_[filename] = text;
        }
        else if (text.loadFromFile(path+pathOptions[i]+filename,blockRect_)) {
            textures_[filename] = text;
        }
        else if (text.loadFromFile(path+pathOptions[i]+filename,blockRect_)) {
            textures_[filename] = text;
        }
        else {
            std::cout << "Texture "+filename+"load failed"<<std::endl;
            std::cout << "Tried from";
            for (auto folder : pathOptions) {
                std::cout <<" "<<folder;
            }
        }
    }
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