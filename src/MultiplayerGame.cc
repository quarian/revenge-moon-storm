#include "MultiplayerGame.hh"
#include "StoryScreen.hh"
#include "Store.hh"
#include "MultiplayerGameWorld.hh"

#include <vector>
#include <string>
#include <iostream>


MultiplayerGame::MultiplayerGame(
        GameState* parent,
        std::vector<Player*> players, 
        std::string mapName,
        int nRounds) :
      GameState(parent),
      map_(&game_),
      players_(players),
      mapName_(mapName),
      nRounds_(nRounds),
      totalRounds_(nRounds),
      phase_(0) {}


MultiplayerGame::MultiplayerGame(
        Game& game,
        GameState*& stack,
        std::vector<Player*> players, 
        std::string mapName,
        int nRounds) :
      GameState(game, stack),
      map_(&game_),
      players_(players),
      mapName_(mapName),
      nRounds_(nRounds),
      totalRounds_(nRounds),
      phase_(0) {}


void MultiplayerGame::init() {
    for (auto p : players_)
        wins_[p] = 0;
    resume();
}


void MultiplayerGame::resume() {
    if (phase_ == -1) {
        phase_++;
        showScore();
    } else if (nRounds_ > 0) {
        if (phase_ < players_.size()) {
            phase_++;
            spawn(new Store(this, players_[phase_ - 1]));
        } else {
            phase_ = -1;
            nRounds_--;
            playRound();
        }
    } else terminate();
}


void MultiplayerGame::playRound() {
    /* Load map... */
    if (mapName_=="random") {
        bool overlap = rand() % 2 == 0;
        map_.generateRandomMap(game_.terrainManager_, overlap);
    }
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
    spawn(new MultiplayerGameWorld(this, map_, players_, wins_));
}


void MultiplayerGame::showScore() {
    std::stringstream roundtitle;
    roundtitle << "Round " << (totalRounds_ - nRounds_)
               << " / "    << totalRounds_;
    std::vector<std::string> msgs = { roundtitle.str() };
    if (nRounds_ > 0) msgs.push_back("Scores:");
    else msgs.push_back("Final Scores:");
    msgs.push_back("");
    msgs.push_back("");
    msgs.push_back("Player              Wins               Scrap");

    for (auto p : players_) {
        std::stringstream playerrow;
        playerrow << p->getName() << "                     " << wins_[p]
                                  << "                     " << p->getInventory().getGold();
        msgs.push_back(playerrow.str());
    }



    spawn(new StoryScreen(this, msgs));
}


void MultiplayerGame::update(float) {} // Never used -- does not take input
