#ifndef MB2_MULTIPLAYERMENU_HH
#define MB2_MULTIPLAYERMENU_HH

#include "Menu.hh"

#include "MultiplayerGame.hh"
#include "PlayerInterface.hh"
#include "Player.hh"
#include <iostream>
/* MultiPlayerMenu
 * ================
 * 
 * 
 * 
 */

class MultiPlayerMenu : public Menu {
public:

    MultiPlayerMenu(Game&, GameState*&,std::map<std::string,sf::Font>&, sf::Sprite&, std::vector<std::string>&, bool&, bool&);

    void init();
    
    /* Ask for player name to save scores, then terminate */
    //void resume();
    //void terminate();

    void keyLeft();
    void keyRight();
	void keySelect();
	void keyEscape();
	
	//void keyRightReleased() {rightPressed_ = false}
    //void keyLeftReleased() {leftPressed_ = false}
    void keySelReleased();
    void keyEscapeReleased();
    
    bool waitingPlayerName() {return waitingPlayerName_;}
    void sendText(std::string name) {newName_=name;}

private:
	//void updateMenu();
	void start();
	
	//void addPlayer();
	void askPlayerName();
	void removePlayer();
	
	std::vector<std::string>& playerNames_;
	std::vector<PlayerInterface::KeySet> keySets_;
	std::vector<Player*> players_;
	
	bool& selectPressed_;
	bool& escPressed_;
	
	
	std::string newName_;
	bool waitingPlayerName_;
	bool waitingMapSelect_;
	

	
};

#endif
