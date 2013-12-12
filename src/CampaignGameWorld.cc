#include "CampaignGameWorld.hh"


CampaignGameWorld::CampaignGameWorld(
            GameState* parent,
            Map& map,
            Player* player,
            bool& flagVictorious) :
        World(parent, map, {player}),
        player_(player),
        flagVictorious_(flagVictorious),
        timeToExit_(-2000) {
}


CampaignGameWorld::CampaignGameWorld(
            Game& game,
            GameState*& stack,
            Map& map,
            Player* player,
            bool& flagVictorious) :
        World(game, stack, map, {player}),
        player_(player),
        flagVictorious_(flagVictorious),
        timeToExit_(-2000) {
}


void CampaignGameWorld::update(float dt) {
    if (timeToExit_ != -2000) {
        timeToExit_ -= dt;

        if (timeToExit_ < 0)
            terminate();

    } else if (player_->getActor() == nullptr || flagVictorious_) {
        timeToExit_ = 1;
        if (player_->exit())
            map_.players.erase(player_);
    }

    World::update(dt);
}
