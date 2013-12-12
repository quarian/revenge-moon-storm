#include "MultiPlayerMenu.hh"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>


MultiPlayerMenu::MultiPlayerMenu(Game& game, GameState*& stack, bool& selectPressed, bool& escPressed) : 
                Menu(game, stack),  
                playerCount_(2), 
                selectPressed_(selectPressed), 
                escPressed_(escPressed), 
                mapIndex_(0),
                rounds_(2) { }

void MultiPlayerMenu::init() {

    mapNames_ = {"random","random maze"};
    readMapNames();
    
    setTitle("Multiplayer ");

    addMenuSelection("Start", 30);
    addMenuSelection("Players", 30);
    addMenuSelection("Rounds", 30);
    updateText("Rounds","< Rounds: " + std::to_string(rounds_) +" >");    
    updateText("Players","< Players: " + std::to_string(playerCount_)+" >");
    addMenuSelection("Map", 30);
    updateText("Map","< Map: " + mapNames_[mapIndex_]+" >");
    addMenuSelection("Scrap", 30);
    updateText("Scrap","< Scrap: " + std::to_string(scrap_) +" >");    
    
    addMenuSelection("Back", 30);
    
    keySets_.push_back(PlayerInterface::WASD_DVORAK);
    keySets_.push_back(PlayerInterface::ARROWS);
    
    initKeyboard();
    
}
    
void MultiPlayerMenu::keySelect() {
    if (selectPressed_) return;
    selectPressed_ = true;

    if (selectionKeys_[selectionIndex_] == "Start") {
        initPlayers();
        start();
    } else if (selectionKeys_[selectionIndex_] == "Back") {
        terminate();
    }
}

void MultiPlayerMenu::keyRight() {
    if (selectionKeys_[selectionIndex_] == "Players") {
        if (playerCount_== 4) return;
        playerCount_++;
        updateText("Players","< Players: " + std::to_string(playerCount_)+" >");
    }
    if (selectionKeys_[selectionIndex_] == "Map") {
        mapIndex_++;
        if (mapIndex_== mapNames_.size()) mapIndex_=0;
        updateText("Map","< Map: "+ mapNames_[mapIndex_] +" >");
    }
    if (selectionKeys_[selectionIndex_] == "Scrap") {
        if (scrap_>=1000000000) return;
        scrap_+=50;
        updateText("Scrap","< Scrap: "+ std::to_string(scrap_) +" >");
    }
    if (selectionKeys_[selectionIndex_] == "Rounds") {
        if (rounds_==100) return;
        rounds_+=1;
        updateText("Rounds","< Rounds: "+ std::to_string(rounds_) +" >");
    }
}
void MultiPlayerMenu::keyLeft() {
    if (selectionKeys_[selectionIndex_] == "Players") {
        if (playerCount_== 2) return;
        playerCount_--;
        updateText("Players","< Players: " + std::to_string(playerCount_)+" >");
    }
    if (selectionKeys_[selectionIndex_] == "Map") {
        if (mapIndex_== 0) mapIndex_ = mapNames_.size();
        mapIndex_--;
        updateText("Map","< Map: "+ mapNames_[mapIndex_] +" >");
    }
    if (selectionKeys_[selectionIndex_] == "Scrap") {
        if (scrap_== 0) return;
        scrap_-=50;
        updateText("Scrap","< Scrap: "+ std::to_string(scrap_) +" >");
    } 
    if (selectionKeys_[selectionIndex_] == "Rounds") {
        if (rounds_==1) return;
        rounds_-=1;
        updateText("Rounds","< Rounds: "+ std::to_string(rounds_) +" >");
    }   
}

void MultiPlayerMenu::keyEscape() {
    if (escPressed_) return;
    escPressed_ = true;
    terminate();
}

void MultiPlayerMenu::keySelReleased() {selectPressed_ = false;}

void MultiPlayerMenu::keyEscapeReleased() {escPressed_ = false;}

void MultiPlayerMenu::initPlayers() {
    size_t j = 0;
    std::string p = "Player ";
    for (size_t i=0;i!=playerCount_;i++,j++) {
        if (j==keySets_.size()) j=0;
        players_.push_back(new Player(p+std::to_string(i+1)+".",keySets_[i]));
    }
    for (auto pl : players_) {pl->getInventory().setGold(scrap_);}
    spawnCountter_=playerCount_;
    resume();
}

void MultiPlayerMenu::start() {
    background_.setTexture(game_.graphicsManager_.getTexture("background_grid.png"));
    spawn(new MultiplayerGame(this, players_,mapNames_[mapIndex_],rounds_));
}

void MultiPlayerMenu::readMapNames() {
    struct dirent **dircontent;
    int n,i;
    n = scandir("./maps", &dircontent, 0, versionsort);
    if (n < 0) perror("scandir");
    else {
        for(i =0 ; i < n; ++i) {
            char *tmp;
            tmp = dircontent[i]->d_name;
            std::string str(tmp);
            if (str.find(".map") != std::string::npos) {
                mapNames_.push_back(str);
            }
            free(dircontent[i]);
        }
        free(dircontent);
    }
}
