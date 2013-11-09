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

