#include "MultiplayerGame.hh"
#include "World.hh"


MultiplayerGame::MultiplayerGame(
        GameState* parent,
        std::vector<Player*> players, 
        std::string mapName ) :
      GameState(parent),
      map_(&game_),
      players_(players),
      mapName_(mapName) {}


MultiplayerGame::MultiplayerGame(
        Game& game,
        GameState*& stack,
        std::vector<Player*> players, 
        std::string mapName ) :
      GameState(game, stack),
      map_(&game_),
      players_(players),
      mapName_(mapName) {}


void MultiplayerGame::init() {
	if (mapName_=="random") map_.generateRandomMap(game_.terrainManager_);
	else if (mapName_=="random maze") map_.generateMaze(game_.terrainManager_);
    else map_.loadFromFile("./maps/"+mapName_, game_.terrainManager_);

    
    
    for (auto p : players_)
        map_.spawnPlayer(p, 1, 1);

    spawn(new World(this, map_, players_ ));
}


void MultiplayerGame::resume() {
    terminate();
}


void MultiplayerGame::update(float) {} // Never used -- does not take input
