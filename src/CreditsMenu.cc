#include "CreditsMenu.hh"

CreditsMenu::CreditsMenu(Game& game, GameState*& stack) : Menu(game, stack) {}

void CreditsMenu::init() {
    background_.setTexture(game_.graphicsManager_.getTexture("background_menu.png"));

    setTitle("Credits");
	// use addMenuSelection third parameter to get vertical offset from default position
	addMenuSelection("",10);
	/*quarian, hegemege, alcedine, rsa*/
    addMenuSelection("Miro Nurmela", 40);
    addMenuSelection("Henri Niva", 40);
    addMenuSelection("Joonas Lipping", 40);
    addMenuSelection("Roope Savolainen", 40);
    addMenuSelection("Aalto-university", 30,200);
    addMenuSelection("press any key to exit",20,350);

    initKeyboard();
}
