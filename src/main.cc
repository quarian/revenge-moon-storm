#include <iostream>
#include "Game.hh"
//Game* Game::singleton;

int main() {
    Game game;
    //Game::singleton = &game;
    game.main();
}
