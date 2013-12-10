#include "MainMenu.hh"



MainMenu::MainMenu(Game& game, GameState*& stack, std::map<std::string, sf::Font>& fonts, sf::Sprite& background) : Menu(game, stack, fonts, background), selectPressed_(false), escPressed_(false) { }

void MainMenu::init() {
	//background_.setTexture(game_.graphicsManager_.getTexture("background_menu.png"));
	
	setTittle("Main menu");
	addMenuSelection("Singleplayer", 50);
	addMenuSelection("MultiPlayer", 50);
	addMenuSelection("Exit", 50);
	
	//keySets_.push_back(PlayerInterface::ARROWS);
	//keySets_.push_back(PlayerInterface::WASD_DVORAK);

	initKeyboard();
}

void MainMenu::keySelect() {
	if (selectPressed_) return;
	selectPressed_ = true;
	int index = 0;
	if (selections_[selectionIndex_] == selections_[index])
		singlePlayerSelected();
	index++;
	if (selections_[selectionIndex_] == selections_[index])
		multiPlayerSelected();
	index++;
	if (selections_[selectionIndex_] == selections_[index])
		terminate();
	//index++;
}

void MainMenu::keyEscape() {
	if (escPressed_) return;
	escPressed_ = true;
	terminate();
}

void MainMenu::singlePlayerSelected() {
	spawn(new SinglePlayerMenu(game_, stack_, fonts_, background_, playerNames_, selectPressed_, escPressed_));
	
	// pasted from singleplayer menu
	/*background_.setTexture(game_.graphicsManager_.getTexture("background_grid.png"));
	if (playerNames_.empty()) playerNames_.push_back("Dostojevsky");
	Player* player_ = new Player("Pertti",PlayerInterface::ARROWS_WIDE);
    spawn(new CampaignGame(this, player_));*/
}

void MainMenu::keySelReleased() {selectPressed_ = false;}
void MainMenu::keyEscReleased() {escPressed_ = false;}


void MainMenu::multiPlayerSelected() {
	spawn(new MultiPlayerMenu(game_, stack_, fonts_, background_, playerNames_,selectPressed_,escPressed_));
}

