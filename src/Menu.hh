#ifndef MB2_MENU_HH
#define MB2_MENU_HH

#include "GameState.hh"
#include "GlobalGameInterface.hh"
#include "Store.hh"
#include "MenuInterface.hh"
#include "Player.hh"

/* Menu
 * ================
 * An abstract base class fot all menus
 * 
 */
class MenuInterface;

class Menu : public GameState {
public:

    Menu(Game&, GameState*&);
    Menu(GameState* stack);
    
    virtual ~Menu() {for (Player* pl : players_) delete pl; /*Should also delete all menus sf::Texts*/}
    
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
    
    virtual void keyDown();
    virtual void keyUp();
    virtual void keyLeft() {}
    virtual void keyRight() {}
    virtual void keySelect() = 0;
    virtual void keyEscape() {terminate();};
    
    virtual void keySelReleased() {}//= 0;
    virtual void keyEscReleased() {}//=0;

protected:
    
    virtual void updateMenu();
    virtual void drawMenu();

    virtual void setTitle(std::string tittle);
    virtual void addMenuSelection(std::string selectionName, int FontSize, int verticalOffset=0);
    void updateText(std::string key, std::string NewStr);

    /* Global maps containing all fonts and texts of the game */
    std::map<std::string, sf::Font>& fonts_;
    std::map<std::string, sf::Text*>& texts_;
    
    /* Pointers to texts which are drawed while in current menu */
    std::vector<sf::Text*> menuTexts_;

    sf::Sprite& background_;

    size_t selectionIndex_;
    std::vector<std::string> selectionKeys_;
    
    void initKeyboard();
    
    std::vector<Player*> players_;
    /*Player initial scarp */
    int scrap_;
    
    /* spawnCounter gets the value of players_.size() after players have been created
     * when 0 resume terminates 
     * when 1 resume() spawn a PlayerGame when more 
     * then 1 resume() spawns stores for Players in players_ 
     */
    int spawnCountter_;
};

#endif
