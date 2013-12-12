#ifndef MB2_MAINMENU_HH
#define MB2_MAINMENU_HH

#include "Menu.hh"
#include "SinglePlayerMenu.hh"
#include "MultiPlayerMenu.hh"
#include "CreditsMenu.hh"
#include "MapEditor.hh"
#include <map>

/* MainMenu
 * ================
 * 
 * 
 * 
 */

class MainMenu : public Menu {
public:

    MainMenu(Game&, GameState*&);

    void init();
    void resume() {
        initKeyboard();
        if (close_) terminate();	//Close after showing credits
    }
    void keySelect();
    void keyEscape();
    
    void keySelReleased();
    void keyEscReleased();
    
    bool close_;	//Close after showing credits

private:    
    void singlePlayerSelected();
    void multiPlayerSelected();
    void mapEdiorSelected();
    
    std::vector<std::string> playerNames_;
    //std::vector<PlayerInterface::KeySet> keySets_;
    //std::vector<Player*> players_;
    //std::map<std::string settingName,int value> gameSettings_;
    
    bool selectPressed_;
    bool escPressed_;
    //bool rightPressed_;
    //bool leftPressed_;
    

};

#endif
