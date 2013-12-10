#ifndef MB2_SINGLEPLAYERMENU_HH
#define MB2_SINGLEPLAYERMENU_HH

#include "Menu.hh"

//#include "SinglePlayerGame.hh"
#include "CampaignGame.hh"
#include "PlayerInterface.hh"
#include "Player.hh"
#include <iostream>
/* SinglePlayerMenu
 * ================
 * 
 * 
 * 
 */

class SinglePlayerMenu : public Menu {
public:

    SinglePlayerMenu(Game&, GameState*&,std::map<std::string,sf::Font>&, sf::Sprite&, std::vector<std::string>&, bool&, bool&);

    void init();
    
    /* Ask for player name to save scores, then terminate */
    //void resume();
    //void terminate();
    //void keyRight();
    //void keyLeft();
	void keySelect();
	void keyEscape();
	
	//void keyRightReleased() {rightPressed_ = false}
    //void keyLeftReleased() {leftPressed_ = false}
    void keySelReleased();
    void keyEscapeReleased();

private:
	//void updateMenu();
	void start();
	
	std::vector<std::string>& playerNames_;
	Player* player_;
	
	bool& selectPressed_;
	bool& escPressed_;
	
	bool waitingCampaign_;
	
};

#endif
