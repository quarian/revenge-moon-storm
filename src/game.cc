#include "game.hh"
#include <iostream>
#include <string>

void Game::Launch() {
    window_.launchWindow();
    std::vector<size_t> play = Menu();
    Initialize(map_, play[0], play[1]);
    isRunning_=true;
    Run();
}

std::vector<size_t> Game::Menu() {
    window_.setMenuMode();
    size_t playerCount = 2;
    size_t playerLives = 2;
    return {playerCount, playerLives};
}


void Game::Initialize(Map& map_, size_t playerCount, size_t playerLives) {
    window_.setPlayMode();
    graphicsManager_.InitializeGraphics();
    //Initialize players
    for (int i=0; i!=playerCount; i++) {
        players_.push_back(Player(playerLives));
        playerKeySettings_.push_back(PlayerKeys());//TODO
    }
    eventManager_.Initialize(players_, playerKeySettings_);
    // Initialize map
    map_.loadFromFile("map.txt");
    
    clock_.restart();
}

void Game::Update() {
    bool PlayersReadyToPlay = eventManager_.StoreEventLoop();
    if (PlayersReadyToPlay) {
        eventManager_.EventLoop();
    }
}

void Game::Draw() {
    window_.clear(sf::Color::White);
}

void Game::Pause() {
    window_.draw(graphicsManager_.getText("paused"));
}

void Game::Shutdown() {
    window_.close();
}
