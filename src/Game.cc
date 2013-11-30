#include "Game.hh"

Game::Game() : eventManager_(window_, isRunning_), graphicsManager_(window_,blockSize_,textures_,animations_), map_(Map(this)) {
    rootPath_ = ".";
    isRunning_ = true;
    window_.launchWindow();
    eventManager_.Initialize(players_, playerKeySettings_);
    graphicsManager_.InitializeGraphics(rootPath_);
    background_.setTexture(graphicsManager_.getTexture("background_grid.png"));
}

Game::~Game() {
    for (auto p : players_) delete p;
}

void Game::Launch() {
    InitializeMap();
    InitializeWalkers(1);
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
    UpdateWalkers();
}

void Game::Draw() {
    window_.clear(sf::Color::White);
    window_.draw(background_);
    DrawMap();
    DrawWalkers();
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
    map_.loadFromFile(rootPath_+"/map64.txt");
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
    	Player* newPlayer = new Player(playerNames[i],2);
    	newPlayer->spawn(map_, map_.getBlock(i+1,i+1))->initSprite(
                graphicsManager_.getAnimation("walking_player"));
        players_.push_back(newPlayer);
        eventManager_.registerInterface(KeyInterface(newPlayer));
        //playerKeySettings_.push_back(PlayerKeys()); //TODO: Different key setting for each player
    }
    // Other walkers
}


void Game::UpdateWalkers() {
    for (auto player : players_)
        player->getActor()->update(static_cast<float>(elapsedTime_.asSeconds()));
	
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
    // sf::Sprite sp;
    // sp.setColor(sf::Color::Black);
    // sp.setPosition(1,1);
    for (auto player : players_) {
        window_.draw(player->getActor()->getSprite());
        // window_.draw(sp);
        // *player.getActor()->getSprite());
    }
}
