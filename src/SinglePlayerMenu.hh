#ifndef MB2_SINGLEPLAYERMENU_HH
#define MB2_SINGLEPLAYERMENU_HH

#include "Menu.hh"

#include "SinglePlayerGame.hh"
#include "CampaignGame.hh"
#include "PlayerInterface.hh"
/* SinglePlayerMenu
 * ================
 * 
 * 
 * 
 */

class SinglePlayerMenu : public Menu {
public:

    SinglePlayerMenu(Game&, GameState*&, bool&, bool&);

    void init();
    
    /* Ask for player name to save scores, then terminate */
    //void resume();

	void keySelect();
	void keyEscape();
	
    void keySelReleased();
    void keyEscapeReleased();

private:
	/* Spawns SinglePlayerGame */
	void start();
	/* Creates Players */
	void initPlayers();
	
	bool& selectPressed_;
	bool& escPressed_;
	
};

#endif
