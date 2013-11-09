#ifndef __Minebombers__WindowManager__
#define __Minebombers__WindowManager__
#include <SFML/Graphics.hpp>


/**********************************************************************
 WindowManager includes some game specific window management functions
 to sf::RenderWindow class
**********************************************************************/

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

#endif
