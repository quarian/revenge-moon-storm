#include "Menu.hh"
#include <iostream>

Menu::Menu(Game& game, GameState*& stack) : 
            GameState(game, stack),
            fonts_(game_.graphicsManager_.fonts_),
            texts_(game_.graphicsManager_.texts_),
            background_(game_.background_),
            selectionIndex_(0), 
            spawnCountter_(0),
            scrap_(100) { }
              
Menu::Menu(GameState* stack) : 
            GameState(stack),
            fonts_(game_.graphicsManager_.fonts_),
            texts_(game_.graphicsManager_.texts_),
            background_(game_.background_), 
            spawnCountter_(0),
            scrap_(100) { }    
              
void Menu::initKeyboard() {
    game_.eventManager_.clearInterfaces();
    game_.eventManager_.registerInterface(new MenuInterface(this));

}

void Menu::update(float dt) {
    updateMenu();
    drawMenu();
}

void Menu::resume() {
    background_.setTexture(game_.graphicsManager_.getTexture("background_menu.png"));
    initKeyboard();

    //if (spawnCountter_<0) {
    //    for (auto pl : players_) delete pl;
    //    terminate();
    //}
    //else if    (spawnCountter_==0) {
    //    spawnCountter_--;
    //    start();
    //}
    //else {
    //    spawn(new Store(this,players_[spawnCountter_-1]));
    //    spawnCountter_--;
    //}
}

void Menu::drawMenu() {
    for (auto t : menuTexts_) { 
        game_.draw(*t);
    }
}

void Menu::updateMenu() {
    for (auto textPtr : menuTexts_) {
        if (textPtr == texts_[selectionKeys_[selectionIndex_]]/*.second*/) {
            textPtr->setColor(sf::Color::Red);
            textPtr->setStyle(sf::Text::Bold);
        }
        else {
            textPtr->setColor(sf::Color::White);
            textPtr->setStyle(sf::Text::Regular);
        }
    }
}

void Menu::setTitle(std::string tittle) {
    texts_[tittle] = new sf::Text(tittle, fonts_["batman"],80);
    sf::FloatRect dim = texts_[tittle]->getLocalBounds();
    texts_[tittle]->setOrigin(dim.width/2, dim.height/2);
    texts_[tittle]->setPosition(sf::Vector2f(512,50));
    menuTexts_.push_back(texts_[tittle]);
}

void Menu::addMenuSelection(std::string selectionName, int FontSize, int verticalPos) {
    selectionKeys_.push_back(selectionName);
    sf::Vector2f pos(512,verticalPos+FontSize*2*(1+selectionKeys_.size()));
    texts_[selectionName] = new sf::Text(selectionName, fonts_["batman"],FontSize);
    sf::FloatRect dim = texts_[selectionName]->getLocalBounds();
    texts_[selectionName]->setOrigin(dim.width/2, dim.height/2);
    texts_[selectionName]->setPosition(pos);
    menuTexts_.push_back(texts_[selectionName]);
}

void Menu::updateText(std::string key, std::string NewStr) {
    texts_[key]->setString(NewStr);
    sf::FloatRect dim;
    dim = texts_[key]->getLocalBounds();
    texts_[key]->setOrigin(dim.width/2, dim.height/2);

}

void Menu::keyDown() {
    selectionIndex_++;
    if (selectionIndex_==selectionKeys_.size()) selectionIndex_ = 0;
}

void Menu::keyUp() {
    if (selectionIndex_==0) selectionIndex_ = selectionKeys_.size();
    selectionIndex_--;
}
