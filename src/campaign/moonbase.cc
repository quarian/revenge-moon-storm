#include "CampaignGame.hh"
#include "CampaignGameWorld.hh"
#include "DummyGameState.hh"
#include "Fixtures.hh"


// void CampaignGame::showStoryMoonbase() {
//     spawn(new DummyGameState(this));
// }


void CampaignGame::launchLevelMoonbase() {
    map_.loadFromFile("./maps/campaign/moonbase.map", game_.terrainManager_);

    map_.spawnPlayer(player_, 4, 3);
    new Fixtures::LevelExit(map_, map_.getBlock(1, 14), flagVictorious_, {player_});
    
    spawn(new CampaignGameWorld(this, map_, player_, flagVictorious_));
}
