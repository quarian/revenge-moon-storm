#include "CampaignGame.hh"
#include "CampaignGameWorld.hh"
#include "StoryScreen.hh"
#include "Fixtures.hh"

#include <string>
#include <vector>

void CampaignGame::showStoryCaverns() {
    std::vector<std::string> msg = {
        "Story 3"
    };
    spawn(new StoryScreen(this, msg));
}


void CampaignGame::launchLevelCaverns() {
    map_.loadFromFile("./maps/campaign/caverns.map", game_.terrainManager_);

    map_.spawnPlayer(player_, 1, 1);
    new Fixtures::LevelExit(map_, map_.getBlock(49, 36), flagVictorious_, {player_});
    
    spawn(new CampaignGameWorld(this, map_, player_, flagVictorious_));
}
