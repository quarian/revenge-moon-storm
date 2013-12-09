#include "MenuInterface.hh"

MenuInterface::MenuInterface(Menu* menu) : menu_(menu) {/*keys_ = ARROWS;*/}
              
bool MenuInterface::operator==(KeyInterface const& other) const {
    /*
    if (PlayerInterface const* pi = dynamic_cast<PlayerInterface const*>(&other)) {
        return player_ == pi->player_;
    } else return false;
    */
    return true;
}


void MenuInterface::parse(sf::Event& evt) {
    // Key pressed
    if (evt.type == sf::Event::KeyPressed) {
        if (evt.key.code == sf::Keyboard::Up)    	menu_->keyUp();
        if (evt.key.code == sf::Keyboard::Right)    menu_->keyRight();
        if (evt.key.code == sf::Keyboard::Left)    	menu_->keyLeft();
        if (evt.key.code == sf::Keyboard::Down)  	menu_->keyDown();
        if (evt.key.code == sf::Keyboard::Return)  	menu_->keySelect();
        if (evt.key.code == sf::Keyboard::Escape) 	menu_->keyEscape();
    }

    // Key released
    else if (evt.type == sf::Event::KeyReleased) {
        if (evt.key.code == sf::Keyboard::Return)  	menu_->keySelReleased();
        if (evt.key.code == sf::Keyboard::Escape) 	menu_->keyEscReleased();
       	//if (evt.key.code == sf::Keyboard::Up)    	menu_->keyUp();
        //if (evt.key.code == sf::Keyboard::Right)    menu_->keyRightReleased();
        //if (evt.key.code == sf::Keyboard::Left)    	menu_->keyLeftReleased();
        //if (evt.key.code == sf::Keyboard::Down)  	menu_->keyDown();

    }
}

