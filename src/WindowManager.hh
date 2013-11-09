#ifndef __Minebombers__WindowManager__
#define __Minebombers__WindowManager__
#include <SFML/Graphics.hpp>

class WindowManager : public sf::RenderWindow {
public:
    void launchWindow();
    void launchWindow(unsigned width, unsigned height);
    void setSize(unsigned width,unsigned height);
    void setPlayMode();
    void setMenuMode(); //this&);
private:
    
        //void setDesktopRes(unsigned& , unsigned&);
};


/*class WindowManager {
public:
    void launchWindow(sf::RenderWindow&);
    void launchWindow(sf::RenderWindow&, unsigned width, unsigned height);
    void setSize(sf::RenderWindow&, unsigned width, unsigned height);
    void setPlayMode(sf::RenderWindow&);
    void setMenuMode(sf::RenderWindow&);
    
private:

        //void setDesktopRes(unsigned& , unsigned&);
};


void WindowManager::launchWindow(sf::RenderWindow& window) {
    window.create(sf::VideoMode::getDesktopMode(), "GameWindow");
}

void WindowManager::launchWindow(sf::RenderWindow& window, unsigned width, unsigned height) {
    window.create(sf::VideoMode(width,height), "GameWindow");
}

void WindowManager::setSize(sf::RenderWindow& window, unsigned width, unsigned height) {
    window.setSize(sf::Vector2u(width, height));
}

void WindowManager::setPlayMode(sf::RenderWindow& window) {
    window.setMouseCursorVisible(false);
}

void WindowManager::setPlayMode(sf::RenderWindow& window) {
    window.setMouseCursorVisible(true);
}
*/



#endif
