#ifndef MB2_MULTIPLAYERMENU_HH
#define MB2_MULTIPLAYERMENU_HH

#include "Menu.hh"

#include "MultiplayerGame.hh"
#include "PlayerInterface.hh"
#include <numeric>
/* MultiPlayerMenu
 * ================
 * 
 * 
 * 
 */

class MultiPlayerMenu : public Menu {
public:

    MultiPlayerMenu(Game&, GameState*&, bool&, bool&);
    
    ~MultiPlayerMenu() {for (Player* pl : players_) delete pl;}

    void init();
    
    /* Ask for player name to save scores, then terminate */
    //void resume();
    //void terminate();

    void keyLeft();
    void keyRight();
	void keySelect();
	void keyEscape();
	
    void keySelReleased();
    void keyEscapeReleased();
    
    /*bool waitingPlayerName() {return waitingPlayerName_;}
    void sendText(std::string name) {newName_=name;}*/

private:
	/* Creates players and spawns multiplayer game */
	void start();
	
	std::vector<PlayerInterface::KeySet> keySets_;
	size_t playerCount_;
	
	bool& selectPressed_;
	bool& escPressed_;

	/* Reads the map names from maps dir to mapNames_ vector */
	void readMapNames();
	std::vector<std::string> mapNames_;
	size_t mapIndex_;

	
};

#endif
