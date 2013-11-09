#include "game.hh"
#include <iostream>
#include <string>


void Game::Initialize(int playerCount, Map& map_, std::map<std::string,sf::Texture>& textures_) {
    commonkeys_ = CommonKeys(); //used in menu
    actors_.push_back(dummyPlayer());
    dummyPlayer pl = dummyPlayer();
    actors_.push_back(pl);
        //walkers.push_back(&Walker(map_, map_.getBlock(10, 10), 5));
        //MapBlock mb(1,1, "#");
    
    // Initialize map
    map_.loadFromFile("/Users/roopesavolainen/Documents/C++/mb/minebombers2/src/roope/Minebombers/Minebombers/map.txt");
    
    // Add players
    for (int i=0; i!=playerCount; i++) {
        players.push_back(Walker(map_, map_.getBlock(10, 10), 5));
    }
    
    
    
    window_.clear(sf::Color::White);
    
    if (!font_.loadFromFile("/Users/roopesavolainen/Documents/C++/mb/minebombers2/src/roope/Minebombers/Minebombers/sansation.ttf")) {
        std::cout << "font load failed";
        return;
    }

    sf::Texture smile;
    if (!smile.loadFromFile("/Users/roopesavolainen/Documents/C++/mb/minebombers2/src/roope/Minebombers/Minebombers/smile.png")) {
        std::cout << "player image load failed";
        return;
     }
    textures_["smile"]=smile;
    
    
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
            isRunning_=false;    //TODO: for now just closing the window
            break;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == commonkeys_.pause) {
            if (!isPaused_) isPaused_ = true;
            else isPaused_ = false;
        }
        if (!isPaused_) {
            UpdateActors(event);
        }
        if (!isPaused_) {
            for (auto& player : actors_) {
                if (event.type == sf::Event::KeyPressed) {
                        // if actor.isAlive() {
                    player.advancePos();    //TODO: vain nappula pohjassa liikkuu
                        // }
                }
            }
        }
        
    }
    
    // Process event consequences

}

void Game::UpdateActors(sf::Event event) {
    for (auto& player : actors_) {
        if (event.type == sf::Event::KeyPressed && event.key.code == player.getKeys().north) {
            player.setDirection(Direction::NORTH);
                //Walker::setDirection(Direction::NORTH);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == player.getKeys().south) {
            player.setDirection(Direction::SOUTH);
                //Walker::setDirection(Direction::SOUTH);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == player.getKeys().west) {
            player.setDirection(Direction::WEST);
                //Walker::setDirection(Direction::WEST);

        }
        if (event.type == sf::Event::KeyPressed && event.key.code == player.getKeys().east) {
            player.setDirection(Direction::EAST);
                //Walker::setDirection(Direction::EAST);

        }
        if (event.type == sf::Event::KeyPressed && event.key.code == player.getKeys().useSelection) {
            
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == player.getKeys().changeWeapon) {
            
        }
    }
}

void Game::Draw() {
    if (!isPaused_) {
        window_.clear(sf::Color::White);
        
            //sf::Sprite pl;
            //pl.setTexture(textures["smile"]);
        
        /***************************
         Draw map
         **************************/
        //Empty content (White)
        sf::Vector2f size(10,10);
        sf::RectangleShape wh(size);
        wh.setFillColor(sf::Color::Yellow);
        //Non-empty content (Green)
        sf::RectangleShape gr(size);
        gr.setFillColor(sf::Color::Green);
    
        //if (map_.getGrid().size()==0) std::cout <<"Map is empty";
        //else std::cout<< "map size: " << map_.getGrid().size() <<" "<<map_.getGrid().front().size();
    
        /*MapBlock block = map_.getBlock(0, 0);
        int x,y;
        x=0;
        std::vector<MapBlock> blockVec;
        std::vector<std::vector<MapBlock>> blockCol;

        while (true) {
            for (std::vector<MapBlock>::iterator block; block!=blockVec.end(); block++) {
                if (!(block->content_.compare(" ")) {
                    gr.setPosition(block->x_,block->y_);
                    window_.draw(gr);
                }
                else {
                    wh.setPosition(block->x_,block->y_);
                    window_.draw(wh);
                }
            }
            x++;
            if (x>40) break;    //TODO:if last block of the grid
        }*/
        /*for (auto iter = map_.getGrid().begin(); iter != map_.getGrid().end(); iter++) {
            for (auto jiter = (*iter).begin(); jiter != (*iter).end(); jiter++) {
                if (!(jiter->content_).compare("")) {
                    gr.setPosition(jiter->x_,jiter->y_);
                    window_.draw(gr);
                }
                else {
                    gr.setPosition(jiter->x_,jiter->y_);
                    window_.draw(gr);
                }
            }
            std::cout << std::endl;
        }*/


        
            /*for (auto iter = map_.getGrid().begin(); iter != map_.getGrid().end(); iter++) {
                for (auto jiter = (*iter).begin(); jiter != (*iter).end(); jiter++) {
                    if (!(jiter->content_).compare("")) {
                        //Draw empty space
                        wh.setPosition(jiter->x_+5,jiter->y_+5);
                    }
                    else {
                        //Draw non-empty content -> jiter->content_
                        gr.setPosition(jiter->x_+5,jiter->y_+5);
                        std::cout<<"x"<<jiter->x_<<"y"<<jiter->y_;
                    }
                }
            }*/
        
        /***************************
         Draw walkers
         ***************************/
        for (auto& player :actors_) {
            sf::Sprite pl;
            pl.setTexture(textures_["smile"]);
            pl.setScale(0.5, 0.5);
            pl.setPosition(player.getPos().x+5 ,player.getPos().y+5 );
            
            //pl.setPosition(Walker::getLocation());
            //pl.setRotation(DirectionToAngle(Walker::getDirection()));
            
            window_.draw(pl);
        }
    }
    else Pause();
    
    window_.display();
    
}

void Game::Pause() {
    sf::Text paused("Paused",font_,50);
    paused.setColor(sf::Color::Red);
    paused.setPosition(window_.getSize().x*0.4, window_.getSize().y*0.3);
    window_.draw(paused);
}

void Game::Shutdown() {
    window_.close();
}

