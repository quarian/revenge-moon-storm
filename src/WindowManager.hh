#ifndef __Minebombers__WindowManager__
#define __Minebombers__WindowManager__
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include <iostream>

/**********************************************************************
 WindowManager includes some game specific window management functions
 to sf::RenderWindow class
**********************************************************************/

 class WindowManager : public sf::RenderWindow {
public:
    void launchWindow();
    void launchWindow(size_t width, size_t height);
    void closeWindow();

    void setSize(size_t width,size_t height);
    void setPlayMode();
    void setMenuMode(); //this&);
     
     void drawOverMap();
         //void drawAnimated();
     void drawText();
private:
    
        //void setDesktopRes(unsigned& , unsigned&);
};

#endif
