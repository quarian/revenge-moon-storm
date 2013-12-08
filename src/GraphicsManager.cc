#include "GraphicsManager.hh"
#include <iostream>

void GraphicsManager::initializeGraphics(std::string rootPath) {
    rootPath_=rootPath + "/graphics";
    pathOptions_ = {"/blocks","/players","/items","/misc"};

    blockSize_ = sf::Vector2f(16,16);

    // Load textures
    if (!font_.loadFromFile(rootPath_+"/fonts/sansation.ttf")) {
        std::cout << "Font load from "<<rootPath_+"/fonts/sansation.ttf failed"<<std::endl;
        return;
    }

    std::cout<<"Loading textures to textures_[filename.png]"<<std::endl;
    //Load from /blocks
    loadTexture("Strong.png");
    loadTexture("Medium.png");
    loadTexture("Weak.png");
    loadTexture("Indestructible.png");
    loadTexture("Sand.png");
    loadTexture("fow.png");
    loadTexture("unexplored.png");
	
	//Load from /players
	frontToEnd();
    loadTexture("player_standing.png");
    //loadTexture("player_walking1.png");
    //loadTexture("player_walking2.png");
    loadTexture("player_spritesheet.png");
    loadTexture("digger_spritesheet.png");
    loadTexture("little_bug.png");
    
    //Load from  /items
	frontToEnd();
    loadTexture("Goldbar.png");
    loadTexture("explosion_spritesheet.png");
	//Load from /misc
	frontToEnd();
	loadTexture("wtf.png");
	loadTexture("background_grid.png");
    loadTexture("blood_splatter.png");
    loadTexture("bug_splat.png");
	
	// Create animations
	Animation standingPlayer;
	standingPlayer.setSpriteSheet(getTexture("player_spritesheet.png"));
    standingPlayer.addFrame(sf::IntRect(0,0,16,16));
    animations_["standing_player"] = standingPlayer;
	
    Animation walkingPlayer;
    walkingPlayer.setSpriteSheet(getTexture("player_spritesheet.png"));
    walkingPlayer.addFrame(sf::IntRect(0,0,16,16));
    walkingPlayer.addFrame(sf::IntRect(16,0,16,16));
    walkingPlayer.addFrame(sf::IntRect(16*2,0,16,16));
    animations_["walking_player"] = walkingPlayer;
    
    Animation diggingPlayer;
    diggingPlayer.setSpriteSheet(getTexture("digger_spritesheet.png"));
    diggingPlayer.addFrame(sf::IntRect(0,0,16,16));
    diggingPlayer.addFrame(sf::IntRect(16,0,16,16));
    diggingPlayer.addFrame(sf::IntRect(16*2,0,16,16));
    diggingPlayer.addFrame(sf::IntRect(16*3,0,16,16));
    diggingPlayer.addFrame(sf::IntRect(16*4,0,16,16));
    animations_["digging_player"] = diggingPlayer;

    Animation tinyBug;
    tinyBug.setSpriteSheet(getTexture("little_bug.png"));
    tinyBug.addFrame(sf::IntRect(0,0,16,16));
    tinyBug.addFrame(sf::IntRect(16,0,16,16));
    tinyBug.addFrame(sf::IntRect(16*2,0,16,16));
    tinyBug.addFrame(sf::IntRect(16*3,0,16,16));
    animations_["tiny_bug"] = tinyBug;
    
    frontToEnd();
    Animation explosion1;
    explosion1.setSpriteSheet(getTexture("explosion_spritesheet.png"));

    explosion1.addFrame(sf::IntRect(0,0,16,16));
    explosion1.addFrame(sf::IntRect(16,0,16,16));
    explosion1.addFrame(sf::IntRect(16*2,0,16,16));
    explosion1.addFrame(sf::IntRect(16*3,0,16,16));
    explosion1.addFrame(sf::IntRect(16*4,0,16,16));
    
    animations_["explosion_1"] = explosion1;
    
    
   
    /*sf::Text paused("Paused",font_,50);
    paused.setColor(sf::Color::Yellow);
    texts_["paused"]=paused;
    */
}

void GraphicsManager::frontToEnd() {
	pathOptions_.push_back(pathOptions_.front());
	pathOptions_.pop_front();
}

sf::Color GraphicsManager::getPlayerColor() {
	    std::vector<sf::Color> playerColors = {
	    			sf::Color(154,205,50),
					sf::Color(238,64,0),
					sf::Color(154,205,50),
					sf::Color(79,148,205),
					sf::Color(180,82,205),
					sf::Color(0,205,205),
					sf::Color(205,205,0)};
		if (playerColorsIndex_+1<playerColors.size()) playerColorsIndex_=0; // Looping through the same colors if more than 
		sf::Color retColor = playerColors[playerColorsIndex_];
		playerColorsIndex_++;
		return retColor;
}



//void GraphicsManager::createRotated(sf::Texture orginal) {
//}

sf::Texture& GraphicsManager::getTexture(std::string filename) {
    if (textures_.find(filename)==textures_.end()) {
        loadTexture(filename);
    }
    return textures_[filename];
}

void GraphicsManager::loadTexture(std::string filename) {
    if (textures_.find(filename)==textures_.end()) {
        sf::Texture texture;

        for (size_t i = 0; i!=pathOptions_.size(); i++) {
            std::string path = rootPath_+pathOptions_[i];
            if (texture.loadFromFile(rootPath_+pathOptions_[i]+"/"+filename)) {
            	std::cout << "Loaded texture:"<<rootPath_+pathOptions_[i]+"/"+filename << std::endl;
                texture.setSmooth(true);
                textures_[filename] = texture;
                return;
            }
        }
        if (texture.loadFromFile(rootPath_+"/"+filename)) {
            textures_[filename] = texture;
            return;
        }
        std::cout << "Texture "+filename+"load failed"<<std::endl;
        std::cout << "Tried from load images from:"<< std::endl << rootPath_ <<std::endl;
        for (auto folder : pathOptions_) {
            std::cout <<rootPath_<<folder<<std::endl;
        }
    	if (texture.loadFromFile(rootPath_+"/misc/wtf.png")) {
        	textures_[filename] = texture;
        	return;
    	}
    	else {
    		throw "WTF: Texture load failed!";
    	}
        
    }
}
Animation const& GraphicsManager::getAnimation(std::string name) {
	return animations_[name];
}


/*
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
*/
