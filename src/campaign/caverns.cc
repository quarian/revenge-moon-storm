#include "CampaignGame.hh"
#include "CampaignGameWorld.hh"
#include "DummyGameState.hh"


void CampaignGame::showStoryCaverns() {
    spawn(new DummyGameState(this));
}


void CampaignGame::launchLevelCaverns() {
}
