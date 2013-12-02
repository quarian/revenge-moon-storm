#include "World.hh"


World::World(GameState* parent, Map& map, std::vector<Player*> players)
        : GameState(parent), map_(map), players_(players) {}
