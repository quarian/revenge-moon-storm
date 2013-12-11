#include "MultiPlayerMenu.hh"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>


MultiPlayerMenu::MultiPlayerMenu(Game& game, GameState*& stack, bool& selectPressed, bool& escPressed) : Menu(game, stack),  playerCount_(2), selectPressed_(selectPressed), escPressed_(escPressed), mapIndex_(0) { }

void MultiPlayerMenu::init() {

	mapNames_ = {"random","random maze"};
	readMapNames();
	
	setTittle("Multiplayer");

	addMenuSelection("Start", 40);
	addMenuSelection("Players", 40);
	updateText("Players","< Players: " + std::to_string(playerCount_)+" >");
	//addMenuSelection("Difficulty", 40);
	addMenuSelection("Map", 40);
	updateText("Map","< Map: " + mapNames_[mapIndex_]+" >");
	
	addMenuSelection("Back", 40);
	
	keySets_.push_back(PlayerInterface::WASD_DVORAK);
	keySets_.push_back(PlayerInterface::ARROWS);
	
	initKeyboard();
	
}
    
void MultiPlayerMenu::keySelect() {
	if (selectPressed_) return;
	selectPressed_ = true;

	if (selectionKeys_[selectionIndex_] == "Start") 	start();
	if (selectionKeys_[selectionIndex_] == "Back" ) 	terminate();
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
}

void MultiPlayerMenu::keyEscape() {
	if (escPressed_) return;
	escPressed_ = true;
	terminate();
}

void MultiPlayerMenu::keySelReleased() {selectPressed_ = false;}

void MultiPlayerMenu::keyEscapeReleased() {escPressed_ = false;}

void MultiPlayerMenu::start() {
	background_.setTexture(game_.graphicsManager_.getTexture("background_grid.png"));
	size_t j = 0;
	for (size_t i=0;i!=playerCount_;i++,j++) {
		if (j==keySets_.size()) j=0;
		players_.push_back(new Player(std::to_string(i+1),keySets_[i]));
	}
	spawn(new MultiplayerGame(this, players_,mapNames_[mapIndex_]));
}

void MultiPlayerMenu::readMapNames() {
    struct dirent **dircontent;
    int n,i;
    n = scandir("./maps", &dircontent, 0, versionsort);
    if (n < 0)
        perror("scandir");
    else {
        for(i =0 ; i < n; ++i) {
        	char *tmp;
			tmp = dircontent[i]->d_name;
			std::string str(tmp);
			if (str.find(".map") != std::string::npos) {
				mapNames_.push_back(str);
				std::cout << str << std::endl;
			}
            free(dircontent[i]);
        }
        free(dircontent);
    }
	for (auto n : mapNames_) std::cout << n << std::endl;
}
