#include "PlayerInterface.hh"
#include "GlobalGameInterface.hh"
#include "SinglePlayerGame.hh"
#include "MultiplayerGame.hh"
#include "CampaignGame.hh"
#include "Game.hh"

// For rand!
#include <time.h>
#include <stdlib.h>

Game::Game() : stack_(nullptr),
               isRunning_(true),
               rootPath_("."),
               // isPaused_(true),
               eventManager_(window_, isRunning_),
               graphicsManager_(window_,blockSize_,textures_,animations_,fonts_),
               terrainManager_(graphicsManager_) {
    
    window_.launchWindow();
    graphicsManager_.initializeGraphics(rootPath_);
    terrainManager_.init("terrain.cfg");
    // eventManager_.registerInterface(new GlobalGameInterface(this));
    background_.setTexture(graphicsManager_.getTexture("background_grid.png"));
}


void Game::main() {
    srand(time(NULL)); // Init rand

    Player* kafka = new Player("Kafka");
    Player* dostojevsky = new Player("Dostojevsky", PlayerInterface::WASD_DVORAK);

    // stack_ = new SinglePlayerGame(*this, stack_, kafka);
    // stack_ = new MultiplayerGame(*this, stack_, {kafka, dostojevsky});
    stack_ = new CampaignGame(*this, stack_, kafka);

    clock_.restart();
    stack_->init();

    while (stack_) {
        if (!window_.isOpen() || !isRunning_) {
            terminate();
            break;
        }

        window_.clear(sf::Color::White);
        window_.draw(background_);
        handleEvents();
        stack_->update(clock_.restart().asSeconds());
        window_.display();
    }

    delete kafka;
    delete dostojevsky;
}


void Game::handleEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        eventManager_.EventLoop(event);
    }
}


void Game::terminate() {
    while (stack_)
        stack_->kill();
}
