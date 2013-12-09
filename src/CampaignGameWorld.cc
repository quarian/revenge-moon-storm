#include "CampaignGameWorld.hh"


CampaignGameWorld::CampaignGameWorld(
            GameState* parent,
            Map& map,
            Player* player,
            bool& flagVictorious) :
        World(parent, map, {player}),
        player_(player),
        flagVictorious_(flagVictorious) {
}


CampaignGameWorld::CampaignGameWorld(
            Game& game,
            GameState*& stack,
            Map& map,
            Player* player,
            bool& flagVictorious) :
        World(game, stack, map, {player}),
        player_(player),
        flagVictorious_(flagVictorious) {
}


void CampaignGameWorld::update(float dt) {
    /* If player is dead or victorious, terminate the world */
    if (player_->getActor() == nullptr || flagVictorious_)
        terminate();

    /* If nothing special has happened, just carry on as normal. */
    World::update(dt);
}
