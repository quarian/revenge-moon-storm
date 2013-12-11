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
    
    ~SinglePlayerMenu() {}

    void init();
    
    /* Ask for player name to save scores, then terminate */
    //void resume();

    //void keyRight();
    //void keyLeft();
	void keySelect();
	void keyEscape();
	
    void keySelReleased();
    void keyEscapeReleased();

private:
	void start();
	
	bool& selectPressed_;
	bool& escPressed_;
	
};

#endif
