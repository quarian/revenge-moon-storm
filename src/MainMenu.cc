#include "MainMenu.hh"



MainMenu::MainMenu(Game& game, GameState*& stack, std::map<std::string, sf::Font>& fonts, sf::Sprite& background) : Menu(game, stack, fonts, background), selectPressed_(false), escPressed_(false) { }

void MainMenu::init() {
	background_.setTexture(game_.graphicsManager_.getTexture("background_menu.png"));
	
	texts_["menu_title"] = new sf::Text("Main menu", fonts_["dark_world"],80);
	texts_["menu_title"]->setPosition(sf::Vector2f(60,30));

	addMenuSelection("Singleplayer", 50);
	addMenuSelection("MultiPlayer", 50);
	addMenuSelection("Exit", 50);

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
	spawn(new SinglePlayerMenu(game_, stack_, fonts_, background_, playerNames_,selectPressed_,escPressed_));
}

void MainMenu::keySelReleased() {selectPressed_ = false;}
void MainMenu::keyEscReleased() {escPressed_ = false;}


void MainMenu::multiPlayerSelected() {
//	std::cout << "MultiPlayerSelected" << std::endl;
//	spawn(new SinglePlayerMenu(game_, stack_,fonts_,background_,playerNames_));
//	if (playerNames_.empty()) playerNames_.push_back("Dostojevsky");
//	for (auto const& name : playerNames_)
//		Player* pl = new Player(name);
	// Player* dostojevsky = new Player("Dostojevsky", PlayerInterface::WASD_DVORAK);
	// stack_ = new MultiplayerGame(*this, stack_, {kafka, dostojevsky});
}

