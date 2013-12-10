#include "Menu.hh"

Menu::Menu(Game& game, GameState*& stack, std::map<std::string, sf::Font>& fonts, sf::Sprite& background) : 
            GameState(game, stack),
      	    fonts_(fonts),
      	    background_(background),
      	    selectionIndex_(0)/*,
      	    interface_(new MenuInterface(this))*/ { }
      	    
Menu::Menu(GameState* stack, std::map<std::string, sf::Font>& fonts, sf::Sprite& background) : 
            GameState(stack),
      	    fonts_(fonts),
      	    background_(background)/*,
      	    interface_(new MenuInterface(this))*/ { }    
      	    
void Menu::initKeyboard() {
    game_.eventManager_.clearInterfaces();
    game_.eventManager_.registerInterface(new MenuInterface(this));

}

void Menu::update(float dt) {
	updateMenu();
	drawMenu();
}

void Menu::resume() {
	initKeyboard();
    terminate();
}

void Menu::drawMenu() {
	for (auto it = texts_.begin(); it != texts_.end(); it++) { 
		game_.draw(*it->second);
	}
	/*for (auto it = sidetexts_.begin(); it != sidetexts_.end(); it++) { 
		game_.draw(*it->second);
	}*/
		
}

void Menu::updateMenu() {
	for (auto s: texts_) {
		if (s.first == selections_[selectionIndex_]) {
			s.second->setColor(sf::Color::Red);
			s.second->setStyle(sf::Text::Bold);
		}
		else {
			s.second->setColor(sf::Color::White);
			s.second->setStyle(sf::Text::Regular);
		}
	}
}

void Menu::setTittle(std::string tittle) {
	texts_[tittle] = new sf::Text(tittle, fonts_["dark_world"],80);
	sf::FloatRect dim = texts_[tittle]->getLocalBounds();
	texts_[tittle]->setOrigin(dim.width/2, dim.height/2);
	texts_[tittle]->setPosition(sf::Vector2f(512,50));
}

void Menu::addMenuSelection(std::string selectionName, int FontSize) {
		selections_.push_back(selectionName);
		sf::Vector2f pos(512,FontSize*2*(1+selections_.size()));
		texts_[selectionName] = new sf::Text(selectionName, fonts_["dark_world"],FontSize);
		sf::FloatRect dim = texts_[selectionName]->getLocalBounds();
		texts_[selectionName]->setOrigin(dim.width/2, dim.height/2);
		texts_[selectionName]->setPosition(pos);
		//selectorPos_.push_back(pos);
}

void Menu::addMenuSelectionRight(std::string selectionName, int row, int FontSize) {
		/*selections_.push_back(selectionName);
		sf::Vector2f pos(712,FontSize*2*(1+row));
		sidetexts_[selectionName] = new sf::Text(selectionName, fonts_["dark_world"],FontSize);
		sf::FloatRect dim = texts_[selectionName]->getLocalBounds();
		sidetexts_[selectionName]->setOrigin(dim.width/2, dim.height/2);
		sidetexts_[selectionName]->setPosition(pos);*/
}
void Menu::addMenuSelectionLeft(std::string selectionName, int row, int FontSize) {
		/*selections_.push_back(selectionName);
		sf::Vector2f pos(312,FontSize*2*(1+row));
		sidetexts_[selectionName] = new sf::Text(selectionName, fonts_["dark_world"],FontSize);
		sf::FloatRect dim = texts_[selectionName]->getLocalBounds();
		sidetexts_[selectionName]->setOrigin(dim.width/2, dim.height/2);
		sidetexts_[selectionName]->setPosition(pos);*/
}

void Menu::keyDown() {
	selectionIndex_++;
	if (selectionIndex_==selections_.size()) selectionIndex_ = 0;
}

void Menu::keyUp() {
	selectionIndex_--;
	if (selectionIndex_<0) selectionIndex_ = selections_.size()-1;
}

void Menu::keyRight() {keySelect();}
void Menu::keyLeft() {}
