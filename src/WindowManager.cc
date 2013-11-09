#include "WindowManager.hh"


void WindowManager::launchWindow() {
 this->create(sf::VideoMode::getDesktopMode(), "GameWindow");
 }
 
 void WindowManager::launchWindow(unsigned width, unsigned height) {
 this->create(sf::VideoMode(width,height), "GameWindow");
 }
 
 void WindowManager::setSize(unsigned width, unsigned height) {
     this->setSize(width,height);
 }
 
 void WindowManager::setPlayMode() {
 this->setMouseCursorVisible(false);
 }
 
 void WindowManager::setMenuMode() {
 this->setMouseCursorVisible(true);
 }


/*void WindowManager::launchWindow(sf::RenderWindow& window) {
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
}*/


