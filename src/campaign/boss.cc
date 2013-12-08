#include "CampaignGame.hh"
#include "CampaignGameWorld.hh"
#include "DummyGameState.hh"


void CampaignGame::showStoryBoss() {
    spawn(new DummyGameState(this));
}


void CampaignGame::launchLevelBoss() {
}
