#include "game.hh"

Game::Game() : eventManager_(window_, isRunning_), graphicsManager_(window_,blockSize_,textures_,animations_) {
    rootPath_ = "/Users/roopesavolainen/Documents/C++/mb/minebombers2/src/roope/Minebombers/Minebombers";
    isRunning_ = true;
    window_.launchWindow(800, 600);
    eventManager_.Initialize(players_, playerKeySettings_);
    graphicsManager_.InitializeGraphics(rootPath_);
}

void Game::Launch() {
    InitializeMap();
    InitializeWalkers(2);
    eventManager_.Initialize(players_, playerKeySettings_);
    MainLoop();
}

void Game::MainLoop() {
    while (window_.isOpen() && isRunning_) {
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
}

void Game::Draw() {
    window_.clear(sf::Color::White);
    DrawMap();
    window_.display();
    
    
}

void Game::Shutdown() {
    window_.close();

}

  ///////////////////////////
 /* Map related functions */
///////////////////////////

void Game::InitializeMap() {
    map_.loadFromFile(rootPath_+"/map.txt");
    //map_.printMap();
    mapWidth_ = map_.getWidth();
    mapHeight_ = map_.getHeight();
    std::cout<<"Current map width "<< mapWidth_ <<", height "<< mapHeight_ <<" blocks."<<std::endl;
    
}

void Game::UpdateMap() {
    
    // TODO: MIETI TEHOKKAAKSI JA ULKOISTA JOS MAHDOLLISTA
    sf::Texture& rock =textures_["rock"];
    for (int x=0; x!=mapWidth_; x++) {
        for (int y=0; y!=mapHeight_; y++) {
            std::string blockContent = map_.getBlock(x, y)->content_;
            if (blockContent=="#") {
                sf::Sprite block;
                block.setTexture(rock);
                block.setPosition(x*blockSize_.x, y*blockSize_.y);
                mapSprites_.push_back(block);
            }
        }
    }
}
void Game::DrawMap() {
    for (int i=0; i!=mapSprites_.size(); i++) {
        window_.draw(mapSprites_[i]);
    }
}

  /////////////////////////////
 /* Walker related functions*/
/////////////////////////////

void Game::InitializeWalkers(size_t playerCount) {
    for (int i = 0; i!=playerCount; i++) {
        players_.push_back(Player());
    }
}
void Game::UpdateWalkers() {
    for (auto player : players_) {
            //player.getActor()->update(float...);
    }
}

void Game::DrawWalkers() {
    for (int i = 0; i!=players_.size(); i++) {
        
    }
}

//void Game::Launch() {
////    std::cout << "launch ";
////    win_.create(sf::VideoMode(800,600), "GameWindow");
//    window_.launchWindow(800,600);
//    window_.display();
//    sf::sleep(sf::seconds(2));
//    std::cout<<"window launched"<<std::endl;
////    std::vector<size_t> gameSelections = Menu();
//    Initialize(map_, 2, 2);
//    isRunning_=true;
////    std::cout << "RUN";
//    Run();
//}
//
//std::vector<size_t> Game::Menu() {
//        //window_.setMenuMode();
//    size_t playerCount = 2;
//    size_t playerLives = 2;
//    return {playerCount, playerLives};
//}
//
//
//void Game::Initialize(Map& map_, size_t playerCount, size_t playerLives) {
//    //window_.setPlayMode();
//        //graphicsManager_.InitializeGraphics();
//    
//    //Initialize players
////    for (int i=0; i!=playerCount; i++) {
////        players_.push_back(Player(playerLives));
////        playerKeySettings_.push_back(PlayerKeys());//TODO
////    }
//        //eventManager_.Initialize(players_, playerKeySettings_);
//    
//    // Initialize map
//        //map_.intitialize(players or playercount, vihujenmäärä/vaikeusaste?, );
//    map_.loadFromFile("map.txt");
//    
//    clock_.restart();
//}
//
//void Game::HandleEvents() {
////    if (inStore_)
////        inStore_ = eventManager_.StoreEventLoop();
////    else
////        eventManager_.EventLoop();
//}
//
//
//void Game::Update() {
//
//}
//
//void Game::Draw() {
//    // Draw map
//    window_.clear(sf::Color::White);
//    window_.display();
//}
//
//void Game::Pause() {
//        //window_.draw(graphicsManager_.getText("paused"));
//}
//
//void Game::Shutdown() {
//        //window_.close();
//}
