#include "CampaignGame.hh"
#include "CampaignGameWorld.hh"
#include "StoryScreen.hh"
#include "Fixtures.hh"
#include "Item.hh"

#include <string>
#include <vector>


void CampaignGame::showStoryMoonbase() {
    std::vector<std::string> msg = {
        "Story 1"
    };
    spawn(new StoryScreen(this, msg));
}


void CampaignGame::launchLevelMoonbase() {
    map_.loadFromFile("./maps/campaign/moonbase.map", game_.terrainManager_);

    // Essential elements
    map_.spawnPlayer(player_, 4, 3);
    new Fixtures::LevelExit(map_, map_.getBlock(1, 14), flagVictorious_, {player_});

    spawn(new CampaignGameWorld(this, map_, player_, flagVictorious_));
}
