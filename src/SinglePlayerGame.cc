#include "SinglePlayerGame.hh"
#include "World.hh"


SinglePlayerGame::SinglePlayerGame(
        GameState* parent,
        Player* player ) :
      GameState(parent),
      player_(player) {}


SinglePlayerGame::SinglePlayerGame(
        Game& game,
        GameState*& stack,
        Player* player ) :
      GameState(game, stack),
      player_(player) {}


void SinglePlayerGame::init() {
    map_.loadFromFile("./maps/foo2.map", game_.terrainManager_);
    spawn(new World(this, map_, {player_} ));
}


void SinglePlayerGame::resume() {
    terminate();
}


void SinglePlayerGame::update(float dt) {} // Never used -- does not take input
