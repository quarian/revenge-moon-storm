#include "CampaignGame.hh"
#include "CampaignGameWorld.hh"
#include "StoryScreen.hh"
#include "Fixtures.hh"

#include <string>
#include <vector>

void CampaignGame::showStoryBoss() {
    std::vector<std::string> msg = {
        "Story 4"
    };
    spawn(new StoryScreen(this, msg));
}


void CampaignGame::launchLevelBoss() {
    map_.loadFromFile("./maps/campaign/boss.map", game_.terrainManager_);

    map_.spawnPlayer(player_, 7, 12);
    
    spawn(new CampaignGameWorld(this, map_, player_, flagVictorious_));
}
