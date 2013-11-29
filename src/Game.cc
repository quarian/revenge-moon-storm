#include "Game.hh"

Game::Game() : eventManager_(window_, isRunning_), graphicsManager_(window_,blockSize_,textures_,animations_) {
    rootPath_ = ".";
    isRunning_ = true;
    window_.launchWindow();
    eventManager_.Initialize(players_, playerKeySettings_);
    graphicsManager_.InitializeGraphics(rootPath_);
}

void Game::Launch() {
    InitializeMap();
    InitializeWalkers(1);	//TODO
    //eventManager_.Initialize(players_, playerKeySettings_);
    MainLoop();
    
}

  ///////////////////
 /* The Main Loop */
///////////////////

void Game::MainLoop() {
    while (window_.isOpen() && isRunning_) {
    	elapsedTime_=clock_.restart();
        HandleEvents();
        Update();
        Draw();

    }
    Shutdown();
}

void Game::HandleEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        eventManager_.EventLoop(event);
    }
}

void Game::Update() {
    UpdateMap();
    //UpdateWalkers();
}

void Game::Draw() {
    window_.clear(sf::Color::White);
    DrawMap();
    //DrawWalkers();
    window_.display();
    
    
}

void Game::Shutdown() {
    window_.close();

}

  ///////////////////////////
 /* Map related functions */
///////////////////////////

void Game::InitializeMap() {
	std::cout << "loading map from: "<< rootPath_<<"/map.txt"<<std::endl;
    map_.loadFromFile(rootPath_+"/map.txt");
    //map_.printMap();
    mapWidth_ = map_.getWidth();
    mapHeight_ = map_.getHeight();
    std::cout<<"Current map width "<< mapWidth_ <<", height "<< mapHeight_ <<" blocks."<<std::endl;
    //window_.launchWindow(mapWidth_*16, mapHeight_*16);
    
}

void Game::UpdateMap() {
    sf::Texture& Indestructible =graphicsManager_.getTexture("Indestructible.png");
    for (size_t x=0; x!=mapWidth_; x++) {
        for (size_t y=0; y!=mapHeight_; y++) {
            std::string blockContent = map_.getBlock(x, y)->content_;
            if (blockContent=="#") {
                sf::Sprite block;
                if (map_.getBlock(x, y)->toughness_) {
                    block.setTexture(Indestructible);
                    block.setPosition(x*blockSize_.x, y*blockSize_.y);
                    mapSprites_.push_back(block);
                }
            }
        }
    }
}
void Game::DrawMap() {
    for (size_t i=0; i!=mapSprites_.size(); i++) {
        window_.draw(mapSprites_[i]);
    }
    mapSprites_.clear();
    
}

  ///////////////////////////////
 /* Walker related functions  */
///////////////////////////////

void Game::InitializeWalkers(size_t playerCount) {
	//TODO
    std::vector<std::string> playerNames = {"ukko","nooa","jaakko","kulta"};
    for (size_t i = 0; i!=playerCount; i++) {
    	Player newPlayer = Player(playerNames[i],2);
    	newPlayer.getActor()->initSprite(
    		graphicsManager_.getAnimation("walking_payer"),
    		graphicsManager_.getAnimation("walking_payer"),
    		graphicsManager_.getAnimation("walking_payer"),
    		graphicsManager_.getAnimation("walking_payer"),
    		graphicsManager_.getAnimation("walking_payer"));
    		
        players_.push_back(newPlayer);
        playerKeySettings_.push_back(PlayerKeys()); //TODO: Different key setting for each player
    }
    /*for (size_t i = 0; i!=playerCount; i++) {
    	
        players_[i].spawn(&map_, map_.getBlock(3, 3));
    }*/
    
    // Other walkers
}
void Game::UpdateWalkers() {
	for (auto& player : players_) {
		player.getActor()->update(static_cast<float>(elapsedTime_.asMicroseconds()));
	}
	
    /*sf::Texture& texture = graphicsManager_.getTexture("sand.png");
    
    for (auto& player : players_) {
        player.getActor()->Walker::update(1.0); //player.getActor()->update(float...);
        sf::Sprite playerBlock;
        playerBlock.setTexture(texture);
        playerBlock.setPosition(player.getActor()->getLocation()->x_*blockSize_.x, player.getActor()->getLocation()->y_*blockSize_.y);
        std::cout <<"x: "<<player.getActor()->getLocation()->x_ <<" y: "<<player.getActor()->getLocation()->y_;
        playerSprites_.push_back(playerBlock);
    }
    */
}

void Game::DrawWalkers() {
	sf::Sprite sp;
	sp.setColor(sf::Color::Black);
	sp.setPosition(1,1);
	for (auto& player : players_) {
        window_.draw(sp);//*player.getActor()->getSprite());
    }
}
