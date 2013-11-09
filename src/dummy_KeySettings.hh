#ifndef __Minebombers__dummy_KeySettings__
#define __Minebombers__dummy_KeySettings__

    //#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
    //#include <SFML/System/String.hpp>




/*****************************************************************
 PlayerKeys: Keys for controlling the players, while playing or in store
 ******************************************************************/
class PlayerKeys {
public:
    PlayerKeys(sf::Keyboard::Key n=sf::Keyboard::Up,
               sf::Keyboard::Key w=sf::Keyboard::Left,
               sf::Keyboard::Key e=sf::Keyboard::Right,
               sf::Keyboard::Key s=sf::Keyboard::Down,
               sf::Keyboard::Key use=sf::Keyboard::L,
               sf::Keyboard::Key change=sf::Keyboard::K)
    : north_(n), west_(w), east_(e), south_(s), useSelection_(use), changeWeapon_(change) {}
    
    sf::Keyboard::Key north_;
    sf::Keyboard::Key west_;
    sf::Keyboard::Key east_;
    sf::Keyboard::Key south_;
    sf::Keyboard::Key useSelection_;
    sf::Keyboard::Key changeWeapon_;
private:
    
};

/*****************************************************************
CommonKeys: Keys for moving in menus etc.
 ******************************************************************/
class MenuKeys {
public:
    MenuKeys(sf::Keyboard::Key u=sf::Keyboard::Up,
             sf::Keyboard::Key d=sf::Keyboard::Down,
             sf::Keyboard::Key s=sf::Keyboard::Return,
             sf::Keyboard::Key p=sf::Keyboard::P,
             sf::Keyboard::Key m=sf::Keyboard::Escape) : up_(u), down_(d), sel_(s), pause_(p), menu_(m) {}
    
    sf::Keyboard::Key up_;
    sf::Keyboard::Key down_;
    sf::Keyboard::Key sel_;
    sf::Keyboard::Key menu_;
    sf::Keyboard::Key pause_;
private:
    
};


#endif