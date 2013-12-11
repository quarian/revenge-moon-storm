#include "CampaignGame.hh"
#include "CampaignGameWorld.hh"
#include "DummyGameState.hh"
#include "Fixtures.hh"


// void CampaignGame::showStoryBoss() {
//     spawn(new DummyGameState(this));
// }


void CampaignGame::launchLevelBoss() {
    map_.loadFromFile("./maps/campaign/boss.map", game_.terrainManager_);

    map_.spawnPlayer(player_, 7, 12);
    
    spawn(new CampaignGameWorld(this, map_, player_, flagVictorious_));
}
