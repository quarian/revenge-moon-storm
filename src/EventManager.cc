#include "EventManager.hh"


void EventManager::Initialize(std::vector<Player>& players, std::vector<PlayerKeys>& keys) {
    
    for (int i=0; i<players.size(); i++) {
        triple<Player, PlayerKeys, std::vector<bool>>
            trip(players[i],keys[i], std::vector<bool>(7,false));
        players_.push_back(trip);
    }
    
}

void EventManager::EventLoop(sf::Event& event) {
    // In game event handling
        if (event.type == sf::Event::Closed) {
            isRunning_=false;
            return;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == menuKeys_.menu_) {
            isRunning_=false;//TODO: for now just closing the window
            return;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == menuKeys_.pause_) {
            if (!isPaused_) isPaused_ = true;
            else isPaused_ = false;
        }
        if (!isPaused_) {
            PlayerEvents(event);
            // Other in game event handling here...
        }

        //}
}

void EventManager::PlayerEvents(sf::Event& event) {
    std::cout<<"EventLoop";
    for (size_t i = 0; i<players_.size(); i++) {
        
        Player& player = players_[i].first;
        PlayerKeys& keys = players_[i].second;
        std::vector<bool>& ActiveInput = players_[i].third;
        
        size_t inputNum=0;
        
        // NORTH
        if (event.type == sf::Event::KeyPressed && event.key.code == keys.north_ && !ActiveInput[inputNum]) {
            player.keyDown(Direction::NORTH);
            ActiveInput[inputNum]=true;
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == keys.north_  && ActiveInput[inputNum]) {
            player.keyUp(Direction::NORTH);
            ActiveInput[inputNum]=false;
        }
        inputNum++;
        // SOUTH
        if (event.type == sf::Event::KeyPressed && event.key.code == keys.south_  && !ActiveInput[inputNum]) {
            player.keyDown(Direction::SOUTH);
            ActiveInput[inputNum]=true;
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == keys.south_  && ActiveInput[inputNum]) {
            player.keyUp(Direction::SOUTH);
            ActiveInput[inputNum]=false;
        }
        inputNum++;
        // WEST
        if (event.type == sf::Event::KeyPressed && event.key.code == keys.west_  && !ActiveInput[inputNum]) {
            player.keyDown(Direction::WEST);
            ActiveInput[inputNum]=true;
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == keys.west_  && ActiveInput[inputNum]) {
            player.keyUp(Direction::WEST);
            ActiveInput[inputNum]=false;
        }
        inputNum++;
        // EAST
        if (event.type == sf::Event::KeyPressed && event.key.code == keys.east_  && !ActiveInput[inputNum]) {
            player.keyDown(Direction::EAST);
            ActiveInput[inputNum]=true;
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == keys.west_  && ActiveInput[inputNum]) {
            player.keyUp(Direction::EAST);
            ActiveInput[inputNum]=false;
        }
        inputNum++;

        // Other player control handling, use, nextWeapon etc.
    }
}

bool EventManager::StoreEventLoop(sf::Event& event) {
    std::cout<<"StoreEventLoop";
//    sf::Event event;
//    bool AllPlayersReady=false;
//    std::vector<bool> playerReady(players_.size(),false);
//    
//        if (event.type == sf::Event::Closed) {
//            isRunning_=false;
//            return false;
//        }
//        if (event.type == sf::Event::KeyPressed && event.key.code == menuKeys_.menu_) {
//            return false; // Jump back to mainmenu
//        }
//        BuyingEvents(event,playerReady);
//        
//        // Check if all the players are ready
//        size_t readyCount = 0;
//        for (int i = 0; i!=players_.size(); i++) {
//            if (!playerReady[i]) {
//                readyCount++;
//            }
//        }
//        if (readyCount==players_.size()) AllPlayersReady=true;
//    }
    return true;
}

void EventManager::BuyingEvents(sf::Event& event, std::vector<bool>& playerReady) {
//    for (size_t i = 0; i<players_.size(); i++) {
//        
//        Player& player = players_[i].first;
//        PlayerKeys& keys = players_[i].second;
//        
//        //Buying input handling
//        
//            //TODO
//        
//        
//    }
    

}