#ifndef MB2_CAMPAIGNGAMEWORLD_HH
#define MB2_CAMPAIGNGAMEWORLD_HH

#include "World.hh"

class Player;

class CampaignGameWorld : public World {
public:
     CampaignGameWorld(GameState*, Map&, Player*, bool&);
     CampaignGameWorld(Game&, GameState*&, Map&, Player*, bool&);

     void update(float);

private:
     Player* player_;
     bool& flagVictorious_;
};

#endif
