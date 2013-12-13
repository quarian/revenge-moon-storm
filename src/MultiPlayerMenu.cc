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
    background_.setTexture(game_.graphicsManager_.getTexture("background_menu.png"));
    mapNames_ = {"random (w/ overlap)","random (w/o overlap)","random maze"};
    keySetName_ = {"Arrows R_Ctrl R_Shft","WSDA Space L_Alt","Arrows Space L_Alt",".AEO Space L_Alt"};
    keySets_ = {PlayerInterface::ARROWS,PlayerInterface::WASD,PlayerInterface::ARROWS_WIDE,PlayerInterface::WASD_DVORAK};
    readMapNames();
    
    setTitle("Multiplayer ");
    addSelection("Start");
    /*
    addSelection("Players");
    updateText("Players","< Players: " + std::to_string(playerCount_)+" >");
    */
    
    addSelection("Rounds");
    updateText("Rounds","< Rounds: " + std::to_string(rounds_) +" >");
    
    for (size_t plIndex=0; plIndex!=playerCount_; plIndex++) keySetIndex_.push_back(0);
    updateKeySetSelectors();

    /*
    plIndex++;
    addSelection("Keyset2");
    keySetIndex_[plIndex]=1;
    updateText("Keyset2","< Player 2 KeySet: " + keySetName_[keySetIndex_[plIndex]] +" >");
    */
      
    addSelection("Map");
    updateText("Map","< Map: " + mapNames_[mapIndex_]+" >");
    addSelection("Scrap");
    updateText("Scrap","< Scrap: " + std::to_string(scrap_) +" >");    
    
    addSelection("Back");
    
    initKeyboard();
    
}

void MultiPlayerMenu::updateKeySetSelectors() {
    // Take care that there is as much keySetSelection_ as there is players 
    if (keySetIndex_.size()<playerCount_) {
        while (keySetIndex_.size()==playerCount_)
            keySetIndex_.push_back(0);
    }
    
    for (size_t plIndex=0; plIndex!=playerCount_; plIndex++) {
        std::string n(std::to_string(plIndex+1));
        std::string key("Keyset"+n);
        keySetIndex_[plIndex]=plIndex;
        addSelection(key);
        std::string str("< Player"+n+" KeySet: " + keySetName_[keySetIndex_[plIndex]] +" >");
        updateText(key,str);
    }
}

void MultiPlayerMenu::addSelection(std::string key) {
    int verticalOffset = 130;
    int fontSize = 20;
    addMenuSelection(key,fontSize,verticalOffset);
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

// Should never be called if playerCount is more then keySetIndex_.size()
/*void MultiPlayerMenu::playerKeySetRight() {

    for (size_t plIndex=0; plIndex!=playerCount_; plIndex++) {
        std::string n(std::to_string(plIndex+1));
        std::string key("Keyset"+n);
        
        if (selectionKeys_[selectionIndex_] == key) {
            keySetIndex_[plIndex]++;
            if (keySetIndex_[plIndex]== keySetName_.size()) keySetIndex_[plIndex]=0;
            updateText(v,"< Player 1 KeySet: "+ keySetName_[keySetIndex_[plIndex]] +" >");
        }
    }
}*/


void MultiPlayerMenu::keyRight() {

    /*if (selectionKeys_[selectionIndex_] == "Players") {
        if (playerCount_== 4) return;
        playerCount_++;
        updateText("Players","< Players: " + std::to_string(playerCount_)+" >");
    }*/
    
    int plIndex = 0;
    if (selectionKeys_[selectionIndex_] == "Keyset1") {
        keySetIndex_[plIndex]++;
        if (keySetIndex_[plIndex]== keySetName_.size()) keySetIndex_[plIndex]=0;
        updateText("Keyset1","< Player 1 KeySet: "+ keySetName_[keySetIndex_[plIndex]] +" >");
    }
    plIndex++;
    if (selectionKeys_[selectionIndex_] == "Keyset2") {
        keySetIndex_[plIndex]++;
        if (keySetIndex_[plIndex]== keySetName_.size()) keySetIndex_[plIndex]=0;
        updateText("Keyset2","< Player 2 KeySet: "+ keySetName_[keySetIndex_[plIndex]] +" >");
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
    /*if (selectionKeys_[selectionIndex_] == "Players") {
        if (playerCount_== 2) return;
        playerCount_--;
        updateText("Players","< Players: " + std::to_string(playerCount_)+" >");
    }*/
    int plIndex=0;
    if (selectionKeys_[selectionIndex_] == "Keyset1") {
        if (keySetIndex_[plIndex]== 0) keySetIndex_[plIndex] = keySetName_.size();
        keySetIndex_[plIndex]--;
        updateText("Keyset1","< Player 1 KeySet: "+ keySetName_[keySetIndex_[plIndex]] +" >");
    }
     if (selectionKeys_[selectionIndex_] == "Keyset2") {
        if (keySetIndex_[plIndex]== 0) keySetIndex_[plIndex] = keySetName_.size();
        keySetIndex_[plIndex]--;
        updateText("Keyset2","< Player 2 KeySet: "+ keySetName_[keySetIndex_[plIndex]] +" >");
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
    //size_t j = 0;
    std::string p = "Player ";
    for (size_t i=0;i!=playerCount_;i++/*,j++*/) {
        //if (j==keySets_.size()) j=0;
        players_.push_back(new Player(p+std::to_string(i+1)+".",keySets_[keySetIndex_[i]]));
    }
    for (auto pl : players_) {pl->getInventory().setGold(scrap_);}
    spawnCountter_=playerCount_;
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


void MultiPlayerMenu::resume() {
    for (auto p : players_) delete p;
    players_.clear();
    Menu::resume();
}
