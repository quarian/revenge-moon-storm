#include "MultiplayerGameWorld.hh"
#include <iostream>


MultiplayerGameWorld::MultiplayerGameWorld(
            GameState* parent,
            Map& map,
            std::vector<Player*> players,
            std::map<Player*, int>& wins) :
        World(parent, map, players),
        players_(players),
        wins_(wins),
        timeToExit_(-2000) {
}


MultiplayerGameWorld::MultiplayerGameWorld(
            Game& game,
            GameState*& stack,
            Map& map,
            std::vector<Player*> players,
            std::map<Player*, int>& wins) :
        World(game, stack, map, players),
        players_(players),
        wins_(wins),
        timeToExit_(-2000) {
}


void MultiplayerGameWorld::update(float dt) {
    if (timeToExit_ > -1000) {
        timeToExit_ -= dt;

        if (timeToExit_ < 0)
            terminate();

    } else if (countAlivePlayers() <= 1) {
        for (auto p : players_) {
            if (p->getActor()) {
                p->getInventory().increaseGold(1000); // Last man standing prize
                wins_[p]++;
            }
        }
        timeToExit_ = 1;
    }

    World::update(dt);
}


int MultiplayerGameWorld::countAlivePlayers() {
    int count = 0;
    for (auto p : players_)
        if (p->getActor())
            count++;
    return count;
}
