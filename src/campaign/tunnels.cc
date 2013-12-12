#include "CampaignGame.hh"
#include "CampaignGameWorld.hh"
#include "StoryScreen.hh"
#include "Fixtures.hh"

#include <string>
#include <vector>

void CampaignGame::showStoryTunnels() {
    std::vector<std::string> msg = {
        "Story 2"
    };
    spawn(new StoryScreen(this, msg));
}


void CampaignGame::launchLevelTunnels() {
    map_.loadFromFile("./maps/campaign/tunnels.map", game_.terrainManager_);

    // Essential elements
    map_.spawnPlayer(player_, 6, 36);
    new Fixtures::LevelExit(map_, map_.getBlock(62, 1), flagVictorious_, {player_});
    
    spawn(new CampaignGameWorld(this, map_, player_, flagVictorious_));
}
