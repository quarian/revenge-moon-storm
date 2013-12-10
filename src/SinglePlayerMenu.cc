#include "SinglePlayerMenu.hh"


SinglePlayerMenu::SinglePlayerMenu(Game& game, GameState*& stack, std::map<std::string, sf::Font>& fonts, sf::Sprite& background, std::vector<std::string>& playerNames, bool& selectPressed, bool& escPressed) : Menu(game, stack, fonts, background), playerNames_(playerNames), selectPressed_(selectPressed), escPressed_(escPressed), waitingCampaign_(false) { }

void SinglePlayerMenu::init() {

	setTittle("Singleplayer");

	addMenuSelection("Start", 40);
	//addMenuSelection("Name", 40);
	//addMenuSelection("Difficulty", 40);
	addMenuSelection("Campaign", 40);
	addMenuSelection("Back", 40);
	
	initKeyboard();
}
  	    
void SinglePlayerMenu::keySelect() {
	if (selectPressed_) return;
	selectPressed_ = true;
	int index = 0;
	if (selections_[selectionIndex_] == selections_[index]) {start();}
	index++;
	if (selections_[selectionIndex_] == selections_[index]) {waitingCampaign_ = true;}
	index++;
	if (selections_[selectionIndex_] == selections_[index]) {terminate();}
	//index++;
}

void SinglePlayerMenu::keyEscape() {
	if (escPressed_) return;
	escPressed_ = true;
	terminate();
}

void SinglePlayerMenu::keySelReleased() {selectPressed_ = false;}

void SinglePlayerMenu::keyEscapeReleased() {escPressed_ = false;}

void SinglePlayerMenu::start() {
	background_.setTexture(game_.graphicsManager_.getTexture("background_grid.png"));
	if (playerNames_.empty()) playerNames_.push_back("Dostojevsky");
	player_ = new Player(playerNames_[0],PlayerInterface::ARROWS_WIDE);
    spawn(new CampaignGame(this, player_));
}
