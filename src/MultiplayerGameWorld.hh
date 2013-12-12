#ifndef MB2_MULTIPLAYERGAMEWORLD_HH
#define MB2_MULTIPLAYERGAMEWORLD_HH

#include "World.hh"

class Player;

class MultiplayerGameWorld : public World {
public:
     MultiplayerGameWorld(GameState*, Map&, std::vector<Player*>);
     MultiplayerGameWorld(Game&, GameState*&, Map&, std::vector<Player*>);

     void update(float);

private:
     std::vector<Player*> players_;

     int countAlivePlayers();
};

#endif
