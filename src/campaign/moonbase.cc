#include "CampaignGame.hh"
#include "CampaignGameWorld.hh"
#include "DummyGameState.hh"


void CampaignGame::showStoryMoonbase() {
    spawn(new DummyGameState(this));
}


void CampaignGame::launchLevelMoonbase() {
    map_.loadFromFile("./maps/campaign/moonbase.map", game_.terrainManager_);

    // TODO: special elements...
    
    spawn(new CampaignGameWorld(this, map_, player_, phase_));
}
