#ifndef MB2_MULTIPLAYERGAMEWORLD_HH
#define MB2_MULTIPLAYERGAMEWORLD_HH

#include "World.hh"

#include <map>

class Player;

class MultiplayerGameWorld : public World {
public:
     MultiplayerGameWorld(GameState*, Map&, std::vector<Player*>, std::map<Player*, int>&);
     MultiplayerGameWorld(Game&, GameState*&, Map&, std::vector<Player*>, std::map<Player*, int>&);

     void update(float);

private:
     std::vector<Player*> players_;

     int countAlivePlayers();
     std::map<Player*, int>& wins_;
     float timeToExit_;
};

#endif
