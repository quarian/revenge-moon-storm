#include "MainMenu.hh"



MainMenu::MainMenu(Game& game, GameState*& stack) : Menu(game, stack), selectPressed_(false), escPressed_(false), close_(false) { }

void MainMenu::init() {
    background_.setTexture(game_.graphicsManager_.getTexture("background_menu.png"));
    
    texts_["main_title1"] = new sf::Text("Revenge of the Moon ", fonts_["batman"],60);
    sf::FloatRect dim1 = texts_["main_title1"]->getLocalBounds();
    texts_["main_title1"]->setOrigin(dim1.width/2, dim1.height/2);
    texts_["main_title1"]->setStyle(sf::Text::Bold);
    menuTexts_.push_back(texts_["main_title1"]);
    
    texts_["main_title2"] = new sf::Text("The Gathering Storm", fonts_["dark_world"],50);
    sf::FloatRect dim2 = texts_["main_title2"]->getLocalBounds();
    texts_["main_title2"]->setOrigin(dim2.width/2, dim2.height/2);
    texts_["main_title2"]->setRotation(-2);
    texts_["main_title2"]->setStyle(sf::Text::Underlined);
    texts_["main_title2"]->setColor(sf::Color(139,37,0,225));
    menuTexts_.push_back(texts_["main_title2"]);
    
    texts_["main_title1"]->setPosition(sf::Vector2f(512,40));
    texts_["main_title2"]->setPosition(sf::Vector2f(512,115));
    
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
    
    if (selectionKeys_[selectionIndex_] == "Singleplayer") {
        singlePlayerSelected();
    } else if (selectionKeys_[selectionIndex_] == "Multiplayer") {
        multiPlayerSelected();
    } else if (selectionKeys_[selectionIndex_] == "Map Editor") {
        mapEdiorSelected();
    } else if (selectionKeys_[selectionIndex_] == "Exit" ) {
        close_=true;
        spawn(new CreditsMenu(game_, stack_));
        /*terminate();*/
    }
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

