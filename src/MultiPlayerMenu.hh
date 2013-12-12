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
    
private:
	/* A MultiPlayerMenu specific selection adder */
	void addSelection(std::string key);
	/* Updates keyset selectors to match playerCount_ */
	void updateKeySetSelectors();
	
    /* Spawns MultiPlayerGame */
    void start();
    /* Creates Players */
    void initPlayers();
    
    /* Contains descriptive names for each key set */
    std::vector<std::string> keySetName_;
    /* Contains choosable KeySets */
    std::vector<PlayerInterface::KeySet> keySets_;
    /* Contains the current KeySet selection for each player */
    std::vector<size_t> keySetIndex_;

    size_t playerCount_;
    
    bool& selectPressed_;
    bool& escPressed_;

    /* Reads the map names from maps dir to mapNames_ vector */
    void readMapNames();
    std::vector<std::string> mapNames_;
    size_t mapIndex_;
    size_t rounds_;
    
    void playerKeySetRight();

    
};

#endif
