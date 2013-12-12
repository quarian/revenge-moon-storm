#include "MultiplayerGame.hh"
#include "StoryScreen.hh"
#include "Store.hh"
#include "World.hh"

#include <vector>


MultiplayerGame::MultiplayerGame(
        GameState* parent,
        std::vector<Player*> players, 
        std::string mapName,
        size_t nRounds) :
      GameState(parent),
      map_(&game_),
      players_(players),
      mapName_(mapName),
      nRounds_(nRounds),
      phase_(0) {}


MultiplayerGame::MultiplayerGame(
        Game& game,
        GameState*& stack,
        std::vector<Player*> players, 
        std::string mapName,
        size_t nRounds) :
      GameState(game, stack),
      map_(&game_),
      players_(players),
      mapName_(mapName),
      nRounds_(nRounds),
      phase_(0) {}


void MultiplayerGame::init() {
    resume();
}


void MultiplayerGame::resume() {
    if (nRounds_ > 0) {
        if (phase_ < players_.size()) {
            phase_++;
            spawn(new Store(this, players_[phase_ - 1]));
        } else {
            phase_ = 0;
            nRounds_--;
            playRound();
        }
    } else if (nRounds_ == 0) {
        nRounds_--;
        spawn(new StoryScreen(this, {"Scores:","","Nothing yet :("}));

    } else terminate();
}


void MultiplayerGame::playRound() {
    /* Load map... */
    if (mapName_=="random") map_.generateRandomMap(game_.terrainManager_);
    else if (mapName_=="random maze") map_.generateMaze(game_.terrainManager_);
    else map_.loadFromFile("./maps/"+mapName_, game_.terrainManager_);

    /* Spawn players... */
    std::vector<std::pair<int, int>> spawnPoints = {
        {1, 1},
        {62, 42},
        {1, 42},
        {62, 1}
    };

    for (size_t i = 0; i < players_.size(); i++)
        map_.spawnPlayer(players_[i], spawnPoints[i].first, spawnPoints[i].second);

    /* Launch Game! */
    spawn(new World(this, map_, players_ ));
}


void MultiplayerGame::update(float) {} // Never used -- does not take input
