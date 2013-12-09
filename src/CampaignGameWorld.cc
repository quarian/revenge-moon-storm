#include "CampaignGameWorld.hh"


CampaignGameWorld::CampaignGameWorld(
            GameState* parent,
            Map& map,
            Player* player,
            int& phase) :
        World(parent, map, {player}),
        player_(player),
        phase_(phase) {
}


CampaignGameWorld::CampaignGameWorld(
            Game& game,
            GameState*& stack,
            Map& map,
            Player* player,
            int& phase) :
        World(game, stack, map, {player}),
        player_(player),
        phase_(phase) {
}


void CampaignGameWorld::update(float dt) {
    /* Check termination condition... */
    if (player_->getActor() == nullptr) {
        // Player has died! Terminate and go back without advancing a level
        terminate();
    } else if (false) { // TODO: victory condition
        // Player has attained victory!
        phase_++;
        terminate();
    }

    /* If nothing special has happened, just carry on as normal. */
    World::update(dt);
}
