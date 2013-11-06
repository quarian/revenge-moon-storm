#include "game.hh"
#include <iostream>


void Game::Initialize() {
    commonkeys_ = CommonKeys(); //used in menu
    actors_.push_back(dummyPlayer());
    
    window_.clear(sf::Color::White);
    
    if (!font_.loadFromFile("/Users/roopesavolainen/Documents/C++/mb/minebombers2/src/roope/Minebombers/Minebombers/sansation.ttf")) {
        std::cout << "font load failed";
        return;
    }

    /*sf::Texture smile;
    if (!smile.loadFromFile("/Users/roopesavolainen/Documents/C++/mb/minebombers2/src/roope/Minebombers/Minebombers/smile.png")) {
        std::cout << "player image load failed";
        return;
     }
    textures_["smile"]=smile;
    */
    
    clock_.restart();
}

void Game::Update() {
    
    // Process events
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            isRunning_=false;
            break;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == commonkeys_.menu) {
            isRunning_=false;    // for now just closing the window
            break;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == commonkeys_.pause) {
            if (!isPaused_) isPaused_ = true;
            else isPaused_ = false;
        }
        if (!isPaused_) {
            UpdateActors(event);
        }
    }
    
    // Process event consequences
    if (!isPaused_) {
        for (auto& player : actors_) {
            // if actor.isAlive() {
                player.advancePos();
            // }
        }
    }
}

void Game::UpdateActors(sf::Event event) {
    for (auto& player : actors_) {
        if (event.type == sf::Event::KeyPressed && event.key.code == player.getKeys().north) {
            player.setDirection(Direction::NORTH);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == player.getKeys().south) {
            player.setDirection(Direction::SOUTH);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == player.getKeys().west) {
            player.setDirection(Direction::WEST);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == player.getKeys().east) {
            player.setDirection(Direction::EAST);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == player.getKeys().useSelection) {
            
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == player.getKeys().changeWeapon) {
            
        }
    }
}

void Game::Draw() {
    if (!isPaused_) {
        window_.clear(sf::Color::Black);
        
            //sf::Sprite pl;
            //pl.setTexture(textures["smile"]);
        
        //Draw player
        for (auto& player :actors_) {
            sf::Vector2f size(10,10);
            sf::RectangleShape pl(size);
            pl.setFillColor(sf::Color::White);

            pl.setPosition(player.getPos().x+5 ,player.getPos().y+5 );
            window_.draw(pl);
        }
    }
    else Pause();
    
    window_.display();
    
}

void Game::Pause() {
    sf::Text paused("Paused",font_,50);
    paused.setColor(sf::Color::Yellow);
    paused.setPosition(window_.getSize().x*0.4, window_.getSize().y*0.3);
    window_.draw(paused);
}

void Game::Shutdown() {
    window_.close();
}

