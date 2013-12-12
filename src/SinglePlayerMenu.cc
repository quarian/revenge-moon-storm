#include "SinglePlayerMenu.hh"


SinglePlayerMenu::SinglePlayerMenu(Game& game, GameState*& stack, bool& selectPressed, bool& escPressed) : 
				Menu(game, stack), 
				selectPressed_(selectPressed), 
				escPressed_(escPressed) { }

void SinglePlayerMenu::init() {

	setTitle("Singleplayer ");

	addMenuSelection("Start", 40);
	//addMenuSelection("Name", 40);
	//addMenuSelection("Difficulty", 40);
	//addMenuSelection("Campaign", 40);
	addMenuSelection("Back", 40);
	
	initKeyboard();
}
  	    
void SinglePlayerMenu::keySelect() {
	if (selectPressed_) return;
	selectPressed_ = true;
	
	if (selectionKeys_[selectionIndex_] == "Start") {
            initPlayers();
            start();
        } else if (selectionKeys_[selectionIndex_] == "Back" ) 	terminate();
}

void SinglePlayerMenu::keyEscape() {
	if (escPressed_) return;
	escPressed_ = true;
	terminate();
}

void SinglePlayerMenu::keySelReleased() {selectPressed_ = false;}

void SinglePlayerMenu::keyEscapeReleased() {escPressed_ = false;}

void SinglePlayerMenu::initPlayers() {
	players_.push_back(new Player("1",PlayerInterface::ARROWS_WIDE));
	spawnCountter_=players_.size();
	resume();
}

void SinglePlayerMenu::start() {
	background_.setTexture(game_.graphicsManager_.getTexture("background_grid.png"));
    spawn(new CampaignGame(this, players_[0]));
}

