#ifndef MB2_MENU_HH
#define MB2_MENU_HH

#include "GameState.hh"
#include "GlobalGameInterface.hh"
#include "MenuInterface.hh"
#include <iostream>
/* MainMenu
 * ================
 * 
 * 
 * 
 */
class MenuInterface;

class Menu : public GameState {
public:

	Menu(Game&, GameState*&,std::map<std::string, sf::Font>&, sf::Sprite&);
	Menu(GameState* stack, std::map<std::string, sf::Font>& fonts, sf::Sprite& background);
	virtual ~Menu() {}
	
    /* The update function drives the main functionality of this game state. It
     * takes the elapsed time dt, in seconds, as a parameter.
     */
    void update(float);

    /* Functions to handle whatever initial work needs to be done when this
     * game state receives control. init() is called when this object has just
     * been spawned; resume() is called on termination of a child state.
     */
    virtual void init() = 0;
    virtual void resume();
    //void terminate();
    virtual void start() {}
    
    void keyDown();
    void keyUp();
    virtual void keyLeft();
    virtual void keyRight();
    virtual void keySelect() = 0;
    virtual void keyEscape() = 0;
	
	//virtual void keyRightReleased() = 0;
    //virtual void keyLeftReleased() = 0;
    virtual void keySelReleased() {}//= 0;
    virtual void keyEscReleased() {}//=0;
    
    virtual bool waitingPlayerName() {return false;}
    virtual void sendText(std::string) {}

protected:
	
	virtual void updateMenu();
	virtual void drawMenu();

	void setTittle(std::string tittle);
	virtual void addMenuSelection(std::string selectionName, int FontSize);
	virtual void addMenuSelectionRight(std::string selectionName, int , int fontSize= 30);
	virtual void addMenuSelectionLeft(std::string selectionName, int , int fontSize= 30);

	std::map<std::string, sf::Font>& fonts_;
    std::map<std::string, sf::Text*> texts_;
    std::map<std::string, sf::Text*> sidetexts_;
    sf::Sprite& background_;
        
    int selectionIndex_;
    std::vector<std::string> selections_;
    //std::vector<sf::Vector2f> selectorPos_;
    
    void initKeyboard();
    //MenuInterface* interface_;

};

#endif
