#include "CampaignGame.hh"
#include "CampaignGameWorld.hh"
#include "StoryScreen.hh"
#include "Fixtures.hh"

#include <string>
#include <vector>

void CampaignGame::showStoryCaverns() {
    std::vector<std::string> msg = {
        "The despair you felt earlier started to subside when you saw the",
        "gruesome trail leading to the cavern entrance.",
        "",
        "When feelings depart, they leave a hole... and they get replaced by",
        "something else.",
        "",
        "The emptiness starts filling up with anger.",
        "",
        "Then rage.",
        "",
        "You scream terrifying vow as you pass through into the cavern:",
        "",
        player_->getName() + " WILL HAVE REVENGE !!"
    };
    spawn(new StoryScreen(this, msg));
}


void CampaignGame::launchLevelCaverns() {
    map_.loadFromFile("./maps/campaign/caverns.map", game_.terrainManager_);

    map_.spawnPlayer(player_, 1, 42);
    new Fixtures::LevelExit(map_, map_.getBlock(59, 12), flagVictorious_, {player_});
    
    spawn(new CampaignGameWorld(this, map_, player_, flagVictorious_));
}
