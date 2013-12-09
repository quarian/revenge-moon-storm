#include "MultiplayerGame.hh"
#include "World.hh"


MultiplayerGame::MultiplayerGame(
        GameState* parent,
        std::vector<Player*> players ) :
      GameState(parent),
      map_(&game_),
      players_(players) {}


MultiplayerGame::MultiplayerGame(
        Game& game,
        GameState*& stack,
        std::vector<Player*> players ) :
      GameState(game, stack),
      map_(&game_),
      players_(players) {}


void MultiplayerGame::init() {
    map_.loadFromFile("./maps/foo2.map", game_.terrainManager_);

    //map_.generateRandomMap(game_.terrainManager_);
    for (auto p : players_)
        map_.spawnPlayer(p, 1, 1);

    spawn(new World(this, map_, players_ ));
}


void MultiplayerGame::resume() {
    terminate();
}


void MultiplayerGame::update(float) {} // Never used -- does not take input
