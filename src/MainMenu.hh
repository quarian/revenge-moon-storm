#ifndef MB2_MAINMENU_HH
#define MB2_MAINMENU_HH

#include "Menu.hh"
#include "SinglePlayerMenu.hh"
#include <map>

/* MainMenu
 * ================
 * 
 * 
 * 
 */

class MainMenu : public Menu {
public:

    MainMenu(Game&, GameState*&,std::map<std::string,sf::Font>&, sf::Sprite&);

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
	
	std::vector<std::string> playerNames_;
	//std::map<std::string settingName,int value> gameSettings_;
	
	bool selectPressed_;
    bool escPressed_;
    //bool rightPressed_;
    //bool leftPressed_;
    

};

#endif
