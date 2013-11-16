#include "WindowManager.hh"


void WindowManager::launchWindow() {
 this->create(sf::VideoMode::getDesktopMode(), "GameWindow");
 }
 
 void WindowManager::launchWindow(size_t width, size_t height) {
 this->create(sf::VideoMode(width,height), "GameWindow");
 }
 
 void WindowManager::setSize(size_t width, size_t height) {
     this->setSize(width,height);
 }
 
 void WindowManager::setPlayMode() {
 this->setMouseCursorVisible(false);
 }
 
 void WindowManager::setMenuMode() {
 this->setMouseCursorVisible(true);
 }

// Skaalausjuttuja...?
