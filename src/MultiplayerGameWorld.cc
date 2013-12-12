#include "MultiplayerGameWorld.hh"


MultiplayerGameWorld::MultiplayerGameWorld(
            GameState* parent,
            Map& map,
            std::vector<Player*> players) :
        World(parent, map, players),
        players_(players) {
}


MultiplayerGameWorld::MultiplayerGameWorld(
            Game& game,
            GameState*& stack,
            Map& map,
            std::vector<Player*> players) :
        World(game, stack, map, players),
        players_(players) {
}


void MultiplayerGameWorld::update(float dt) {
    /* If player is dead or victorious, terminate the world */
    if (countAlivePlayers() <= 1) {
        for (auto p : players_) {
            if (p->getActor()) {
                p->getInventory().increaseGold(1000); // Last man standing prize
            }
        }
        terminate();
    }

    /* If nothing special has happened, just carry on as normal. */
    World::update(dt);
}


int MultiplayerGameWorld::countAlivePlayers() {
    int count = 0;
    for (auto p : players_)
        if (p->getActor())
            count++;
    return count;
}
