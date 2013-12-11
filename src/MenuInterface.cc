#include "MenuInterface.hh"

MenuInterface::MenuInterface(Menu* menu) : menu_(menu) {}
              
bool MenuInterface::operator==(KeyInterface const& other) const {
    /*if (MenuInterface const* pi = dynamic_cast<MenuInterface const*>(&other)) {
        return true;
    } else return false;
    */
    return true;
}


bool MenuInterface::parse(sf::Event& evt) {
    // Key pressed
    if (evt.type == sf::Event::KeyPressed) {
        if (evt.key.code == sf::Keyboard::Up)    	{ menu_->keyUp(); return true; }
        if (evt.key.code == sf::Keyboard::Right)        { menu_->keyRight(); return true; }
        if (evt.key.code == sf::Keyboard::Left)    	{ menu_->keyLeft(); return true; }
        if (evt.key.code == sf::Keyboard::Down)  	{ menu_->keyDown(); return true; }
        if (evt.key.code == sf::Keyboard::Return)  	{ menu_->keySelect(); return true; }
        if (evt.key.code == sf::Keyboard::Escape) 	{ menu_->keyEscape(); return true; }
    }

    // Key released
    else if (evt.type == sf::Event::KeyReleased) {
        if (evt.key.code == sf::Keyboard::Return)  	{ menu_->keySelReleased(); return true; }
        if (evt.key.code == sf::Keyboard::Escape) 	{ menu_->keyEscReleased(); return true; }
       	//if (evt.key.code == sf::Keyboard::Up)    	menu_->keyUp();
        //if (evt.key.code == sf::Keyboard::Right)    menu_->keyRightReleased();
        //if (evt.key.code == sf::Keyboard::Left)    	menu_->keyLeftReleased();
        //if (evt.key.code == sf::Keyboard::Down)  	menu_->keyDown();

    }

	// Text input
    /*else if (menu_->waitingPlayerName()) {
		std::string str;
		sf::Text text;

		if (evt.type == sf::Event::TextEntered) {
			// Handle ASCII characters only
			if (evt.text.unicode < 128) {
				str += static_cast<char>(evt.text.unicode);
				str = text.getString();
			}
		}
		if (!str.empty()) menu_->sendText(str);
		
		return true;
	}*/
	
	return false;
}

