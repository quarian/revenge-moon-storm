#ifndef MB2_CAMPAIGNGAMEWORLD_HH
#define MB2_CAMPAIGNGAMEWORLD_HH

#include "World.hh"

class Player;

class CampaignGameWorld : public World {
public:
     CampaignGameWorld(GameState*, Map&, Player*, int&);
     CampaignGameWorld(Game&, GameState*&, Map&, Player*, int&);

     void update(float);

private:
     Player* player_;
     int& phase_;
};

#endif
