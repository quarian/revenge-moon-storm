#include "MainMenu.hh"



MainMenu::MainMenu(Game& game, GameState*& stack) : Menu(game, stack), selectPressed_(false), escPressed_(false) { }

void MainMenu::init() {
	//background_.setTexture(game_.graphicsManager_.getTexture("background_menu.png"));
	
	setTittle("Main menu");
	addMenuSelection("Singleplayer", 50);
	addMenuSelection("Multiplayer", 50);
	addMenuSelection("Map Editor", 50);
	addMenuSelection("Exit", 50);
	
	//keySets_.push_back(PlayerInterface::ARROWS);
	//keySets_.push_back(PlayerInterface::WASD_DVORAK);

	initKeyboard();
}

void MainMenu::keySelect() {
	if (selectPressed_) return;
	selectPressed_ = true;
	
	if (selectionKeys_[selectionIndex_] == "Singleplayer")		singlePlayerSelected();
	if (selectionKeys_[selectionIndex_] == "Multiplayer")		multiPlayerSelected();
	if (selectionKeys_[selectionIndex_] == "Map Editor") 		mapEdiorSelected();
	if (selectionKeys_[selectionIndex_] == "Exit" ) 			terminate();
}

void MainMenu::keyEscape() {
	if (escPressed_) return;
	escPressed_ = true;
	terminate();
}

void MainMenu::singlePlayerSelected() {
	spawn(new SinglePlayerMenu(game_, stack_, selectPressed_, escPressed_));
}

void MainMenu::keySelReleased() {selectPressed_ = false;}
void MainMenu::keyEscReleased() {escPressed_ = false;}


void MainMenu::multiPlayerSelected() {
	spawn(new MultiPlayerMenu(game_, stack_,selectPressed_,escPressed_));
}

void MainMenu::mapEdiorSelected() {
	spawn(new MapEditor(this));
}

