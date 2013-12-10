#include "MultiPlayerMenu.hh"


MultiPlayerMenu::MultiPlayerMenu(Game& game, GameState*& stack, std::map<std::string, sf::Font>& fonts, sf::Sprite& background, std::vector<std::string>& playerNames, bool& selectPressed, bool& escPressed) : Menu(game, stack, fonts, background), playerNames_(playerNames), selectPressed_(selectPressed), escPressed_(escPressed), waitingPlayerName_(false), waitingMapSelect_(false) { }

void MultiPlayerMenu::init() {

	setTittle("Multiplayer");

	addMenuSelection("Start", 40);
	addMenuSelection("Players", 40);
	addMenuSelectionRight("Add player",2,30); addMenuSelectionLeft("Remove player", 2, 30);
	//addMenuSelection("Difficulty", 40);
	addMenuSelection("Map", 40);
	addMenuSelection("Back", 40);
	
	keySets_.push_back(PlayerInterface::WASD_DVORAK);
	keySets_.push_back(PlayerInterface::ARROWS);
	
	initKeyboard();
}
  	    
void MultiPlayerMenu::keySelect() {
	if (selectPressed_) return;
	selectPressed_ = true;
	int index = 0;
	if (selections_[selectionIndex_] == selections_[index] && !waitingPlayerName_ && !waitingMapSelect_) {start();}
	index++;
	
	if (selections_[selectionIndex_] == selections_[index] && !waitingPlayerName_ && !waitingMapSelect_) { askPlayerName(); /*playerNames_.push_back();*/}
	if (selections_[selectionIndex_] == selections_[index] && waitingPlayerName_ && !waitingMapSelect_) { playerNames_.push_back(newName_); }
	index++;
	if (selections_[selectionIndex_] == selections_[index] && !waitingPlayerName_ && !waitingMapSelect_) {/*mapSelect();*/}
	if (selections_[selectionIndex_] == selections_[index] && !waitingPlayerName_ && waitingMapSelect_) {}
	index++;
	if (selections_[selectionIndex_] == selections_[index] && !waitingPlayerName_ && !waitingMapSelect_) {terminate();}
	//index++;
}

void MultiPlayerMenu::keyRight() {
	/*if (selections_[selectionIndex_] == selections_[1] && waitingCampaign_) {
		askPlayerName();
	}
	if (selections_[selectionIndex_] == selections_[1] && !waitingCampaign_) {
		playerNames_.push_back(newName_);
	}*/
}

void MultiPlayerMenu::keyLeft() {
	/*if (selections_[selectionIndex_] == selections_[1] && waitingPlayerName_) {
		waitingPlayerName_=false;
		//sf::sleep(sf::milliseconds(10));
	}
	if (selections_[selectionIndex_] == selections_[1] && !waitingPlayerName_) {
		removePlayer();
	}*/
}



void MultiPlayerMenu::keyEscape() {
	if (escPressed_) return;
	escPressed_ = true;
	terminate();
}

//void MultiPlayerMenu::addPlayer() {
//	
//}

void MultiPlayerMenu::askPlayerName() {
	waitingPlayerName_ = true;
	addMenuSelectionRight(newName_, 30,1);
}

void MultiPlayerMenu::removePlayer() {
	if (playerNames_.empty()) return;
	playerNames_.pop_back();	
}

void MultiPlayerMenu::keySelReleased() {selectPressed_ = false;}

void MultiPlayerMenu::keyEscapeReleased() {escPressed_ = false;}

void MultiPlayerMenu::start() {
	background_.setTexture(game_.graphicsManager_.getTexture("background_grid.png"));
	if (playerNames_.empty()) {
		playerNames_= {"Obama", "Putin"};
	}
	int i = 0;
	for (auto& name : playerNames_) {
		players_.push_back(new Player(name,keySets_[i]));
		i++;
	}
	spawn(new MultiplayerGame(this, players_));
}
