#include "CampaignGame.hh"
#include "CampaignGameWorld.hh"
#include "DummyGameState.hh"
#include "Fixtures.hh"


// void CampaignGame::showStoryBoss() {
//     spawn(new DummyGameState(this));
// }


void CampaignGame::launchLevelBoss() {
    map_.loadFromFile("./maps/campaign/boss.map", game_.terrainManager_);

    map_.spawnPlayer(player_, 1, 1);
    new Fixtures::LevelExit(map_, map_.getBlock(49, 36), flagVictorious_, {player_});
    
    spawn(new CampaignGameWorld(this, map_, player_, flagVictorious_));
}
