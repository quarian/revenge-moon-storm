#ifndef MB2_CREDITSMENU_HH
#define MB2_CREDITSMENU_HH

#include "Menu.hh"
#include <map>

/* MainMenu
 * ================
 * 
 * 
 * 
 */

class CreditsMenu : public Menu {
public:

    CreditsMenu(Game&, GameState*&);

    void init();
    void resume() {initKeyboard();}
    void keySelect() {terminate();}
    void keyEscape() {terminate();}
    void keyDown() {}
    void keyUp() {}

private:    

};

#endif
