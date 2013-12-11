#ifndef MB2_MAINMENU_HH
#define MB2_MAINMENU_HH

#include "Menu.hh"
#include "SinglePlayerMenu.hh"
#include "MultiPlayerMenu.hh"
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
    void resume() {};
    //void terminate();
    void keySelect();
    void keyEscape();
    
    //void keyRightReleased() {rightPressed_ = false}
    //void keyLeftReleased() {leftPressed_ = false}
    void keySelReleased();
    void keyEscReleased();

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
