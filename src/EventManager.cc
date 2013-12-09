#include "EventManager.hh"


void EventManager::registerInterface(KeyInterface* interface) {
    keyInterfaces_.push_back(interface);
}

// void EventManager::unregisterInterface(KeyInterface* interface) {
//     for (auto ki : keyInterfaces_) {
//         if (*interface == *ki) {
//             keyInterfaces_.remove(ki);
//         }
//     }
// }

void EventManager::clearInterfaces() {
    keyInterfaces_.clear();
}


void EventManager::EventLoop(sf::Event& event) {
    // In game event handling
        if (event.type == sf::Event::Closed) {
            isRunning_ = false;
            return;
        }
        //if (event.type == sf::Event::KeyPressed && event.key.code == menuKeys_.menu_) {
        //    isRunning_=false;//TODO: for now just closing the window
        //    return;
        //}
        //if (event.type == sf::Event::KeyPressed && event.key.code == menuKeys_.pause_) {
        //    if (!isPaused_) isPaused_ = true;
        //    else isPaused_ = false;
        //}
        //if (!isPaused_) {
            PlayerEvents(event);
            // Other in game event handling here...
        //}

        //}
}

void EventManager::PlayerEvents(sf::Event& event) {
    for (auto interface : keyInterfaces_)
        interface->parse(event);
}
