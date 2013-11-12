#include "EventManager.hh"
#include "triple.hh"


void EventManager::Initialize(std::vector<Player&> players /*Player specific keyconfs in a vector*/) {
    
    std::vector<bool> activeInput(7,false);
    PlayerKeys keys = PlayerKeys();     //TODO
    for (int i=0; i<players_.size(); i++) {
        triple<Player&, PlayerKeys&, std::vector<bool>> trip(players[i], keys, activeInput)
        players_.push_back(trip);
);
    }
    
}

void EventManager::EventLoop() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            isRunning_=false;
            break;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == menuKeys_.menu_) {
            isRunning_=false;//TODO: for now just closing the window
            break;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == menuKeys_.pause_) {
            if (!isPaused_) isPaused_ = true;
            else isPaused_ = false;
        }
        if (!isPaused_) {
            PlayerEvents(event);
            // Other in game event handling here...
        }

    }
}

void EventManager::PlayerEvents(sf::Event& event) {
    for (int i = 0; i<players_.size(); i++) {
        
        Player player = players_[i].first();
        PlayerKeys keys = players_[i].second();
        std::vector<bool> ActiveInput = players_[i].third();
        
        // NORTH
        if (event.type == sf::Event::KeyPressed && event.key.code == keys.north_ && !ActiveInput[0]) {
            player.keyDown(Direction::NORTH);
            ActiveInput[0]=true;
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == keys.north_  && ActiveInput[0]) {
            player.keyUp(Direction::NORTH);
            ActiveInput[0]=false;
        }
        // SOUTH
        if (event.type == sf::Event::KeyPressed && event.key.code == keys.south_  && !ActiveInput[1]) {
            player.keyDown(Direction::SOUTH);
            ActiveInput[1]=true;
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == keys.south_  && ActiveInput[1]) {
            player.keyUp(Direction::SOUTH);
            ActiveInput[1]=false;

        }
        // WEST
        if (event.type == sf::Event::KeyPressed && event.key.code == keys.west_  && !ActiveInput[2]) {
            player.keyDown(Direction::WEST);
            ActiveInput[2]=true;

        }
        if (event.type == sf::Event::KeyReleased && event.key.code == keys.west_  && ActiveInput[2]) {
            player.keyUp(Direction::WEST);
            ActiveInput[2]=false;

        }
        // EAST
        if (event.type == sf::Event::KeyPressed && event.key.code == keys.east_  && !ActiveInput[3]) {
            player.keyDown(Direction::EAST);
            ActiveInput[3]=true;


        }
        if (event.type == sf::Event::KeyReleased && event.key.code == keys.west_  && ActiveInput[3]) {
            player.keyUp(Direction::EAST);
            ActiveInput[3]=false;
        }
        // Other player control handling, use, nextWeapon etc.
    }
}