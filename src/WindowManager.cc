#include "WindowManager.hh"


void WindowManager::launchWindow() {
    this->create(sf::VideoMode(1024,768), "GameWindow");
}

void WindowManager::launchWindow(size_t width, size_t height) {
    this->create(sf::VideoMode(width,height), "GameWindow");
}

void drawGameArea(sf::Sprite &sprite, float x, float y) {
    y+=64;
    if (y>768 && y<64) {
        std::cout<<"DRAWING FAILED: Drawing position out of game area."<<" y: "<< y <<std::endl;
    }
    if (x>1024 && x<0) {
        std::cout<<"DRAWING FAILED: Drawing position out of game area."<<" x: "<< x <<std::endl;
    }
    sprite.setPosition(x, y);
}


void WindowManager::setPlayMode() {
    this->setMouseCursorVisible(false);
}

void WindowManager::setMenuMode() {
    this->setMouseCursorVisible(true);
}

