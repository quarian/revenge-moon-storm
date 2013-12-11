#include "MainMenu.hh"
#include "PlayerInterface.hh"
#include "GlobalGameInterface.hh"
#include "SinglePlayerGame.hh"
#include "MultiplayerGame.hh"
#include "EditorInterface.hh"
#include "MapEditor.hh"
#include "CampaignGame.hh"
#include "DummyGameState.hh"
#include "Game.hh"

// For rand!
#include <time.h>
#include <stdlib.h>

Game::Game() : stack_(nullptr),
               isRunning_(true),
               rootPath_("."),
               // isPaused_(true),
               editor_(false),
               map_filename_("new.map"),
               eventManager_(window_, isRunning_),
               graphicsManager_(window_,blockSize_,textures_,animations_,fonts_),
               terrainManager_(graphicsManager_) {
    
    window_.launchWindow();
    graphicsManager_.initializeGraphics(rootPath_);
    terrainManager_.init("terrain.cfg");
    // eventManager_.registerInterface(new GlobalGameInterface(this));
    background_.setTexture(graphicsManager_.getTexture("background_grid.png"));
}

Game::Game(bool editor, std::string map_filename) : stack_(nullptr),
               isRunning_(true),
               rootPath_("."),
               // isPaused_(true),
               editor_(editor),
               map_filename_(map_filename),
               eventManager_(window_, isRunning_),
               graphicsManager_(window_,blockSize_,textures_,animations_,fonts_),
               terrainManager_(graphicsManager_) {
    
    window_.launchWindow();
    graphicsManager_.initializeGraphics(rootPath_);
    terrainManager_.init("terrain.cfg");
    // eventManager_.registerInterface(new GlobalGameInterface(this));
    background_.setTexture(graphicsManager_.getTexture("background_grid.png"));
}

Game::~Game() {
    if (window_.isOpen())
        window_.close();
}


void Game::main() {
    srand(time(NULL)); // Init rand
	//stack_ = new MainMenu(*this, stack_, fonts_, background_);
	
    //Player* kafka = new Player("Kafka");
    //Player* dostojevsky = new Player("Dostojevsky", PlayerInterface::WASD_DVORAK);
    if (editor_) {
        stack_ = new MapEditor(*this, stack_, map_filename_);
    }
    else
        stack_ = new MainMenu(*this, stack_, fonts_, background_);
    //stack_ = new SinglePlayerGame(*this, stack_, kafka);
    //stack_ = new MultiplayerGame(*this, stack_, {kafka, dostojevsky});
    //stack_ = new CampaignGame(*this, stack_, kafka);
    // stack_ = new MultiplayerGame(*this, stack_, {kafka, dostojevsky});
    //stack_ = new CampaignGame(*this, stack_, kafka);
    // stack_ = new DummyGameState(*this, stack_);
    stack_ = new MainMenu(*this, stack_, fonts_, background_);

    clock_.restart();
    stack_->init();

    while (stack_) {
        if (!stack_->alive()) {
            delete stack_;
            if (stack_)
                stack_->resume();
        }
        else if (!window_.isOpen() || !isRunning_) {
            terminate();
        } else {
            window_.clear(sf::Color::White);
            window_.draw(background_);
            handleEvents();
            stack_->update(clock_.restart().asSeconds());
            window_.display();
        }
    }

    //delete kafka;
    //delete dostojevsky;
}


void Game::handleEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        eventManager_.EventLoop(event);
    }
}


void Game::terminate() {
    while (stack_)
        delete stack_;
}
