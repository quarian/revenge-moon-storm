#include "PlayerInterface.hh"
#include "GlobalGameInterface.hh"
#include "Game.hh"

Game::Game() : eventManager_(window_, isRunning_,isPaused_),
               graphicsManager_(window_,blockSize_,textures_,animations_),
               terrainManager_(graphicsManager_),
               map_(Map(this)) {
    rootPath_ = ".";
    isRunning_ = true;
    isPaused_= false;
    window_.launchWindow();
    graphicsManager_.InitializeGraphics(rootPath_);
    terrainManager_.init("terrain.cfg");
    eventManager_.registerInterface(new GlobalGameInterface(this));
    background_.setTexture(graphicsManager_.getTexture("background_grid.png"));
}


Game::~Game() {
    for (auto p : players_) delete p;
}

void Game::Launch() {
    InitializeMap("foo2");
    InitializeWalkers(1);
    MainLoop();
    
}


  ///////////////////
 /* The Main Loop */
///////////////////

void Game::MainLoop() {
    while (window_.isOpen() && isRunning_) {
    	elapsedTime_ = clock_.restart();
        HandleEvents();
        if (isPaused_) continue;
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

void Game::InitializeMap(std::string filename) {
    std::string mapPath = rootPath_ + "/maps/" + filename + ".map";
    std::cout << "loading map from: " << mapPath << std::endl;
    map_.loadFromFile(mapPath, terrainManager_);
    //map_.printMap();
    mapWidth_ = map_.getWidth();
    mapHeight_ = map_.getHeight();
    std::cout<<"Current map width " << mapWidth_ << ", height " << mapHeight_ << " blocks." << std::endl;
    //window_.launchWindow(mapWidth_*16, mapHeight_*16);
}


void Game::UpdateMap() {
    for (size_t x=0; x!=mapWidth_; x++) {
        for (size_t y=0; y!=mapHeight_; y++) {
            sf::Sprite block;
            block.setTexture(map_.getBlock(x,y)->getTexture());
            block.setPosition(x*blockSize_.x, y*blockSize_.y);
            mapSprites_.push_back(block);
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
                graphicsManager_.getAnimation("walking_player"), graphicsManager_.getPlayerColor());
        players_.push_back(newPlayer);
        eventManager_.registerInterface(new PlayerInterface(newPlayer));
        //playerKeySettings_.push_back(PlayerKeys()); //TODO: Different key setting for each player
    }
    /*    
     float AICount = 3;
     float AISpeed = 1;
     float AIDigPower = 1;
     float AIDamageResistance = 0.5;
    for (size_t i = 0; i!=AICount; i++) {
    	 AIActor* newAI = new AIActor(map_, map_.map_.getBlock(i+3,i+3)), AISpeed, AIDigPower, int=100, AIDamageResistance, Inventory* =nullptr);
    
    }
    */
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
