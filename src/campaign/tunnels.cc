#include "CampaignGame.hh"
#include "CampaignGameWorld.hh"
#include "DummyGameState.hh"


void CampaignGame::showStoryTunnels() {
    spawn(new DummyGameState(this));
}


void CampaignGame::launchLevelTunnels() {
}
