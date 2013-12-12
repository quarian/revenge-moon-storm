#include "CampaignGame.hh"
#include "CampaignGameWorld.hh"
#include "StoryScreen.hh"
#include "Fixtures.hh"

#include <string>
#include <vector>

void CampaignGame::showStoryTunnels() {
    std::vector<std::string> msg = {
        "Despair sets in as you descend the mine shaft. Up until now you've been",
        "able to tell yourself that everything will be fine once you reach the",
        "emergency zone, that once you're at the ladder, you'd hear the familiar,",
        "reassuring voices of your crewmates...",
        "",
        "Not Rudyard, whose body you saw in the dining hall...",
        "Nor Alice, whose empty stare you will never be able to forget...",
        "But Marcus, Albert, Linda, and the others... someone has to be alive...",
        "",
        "But all you hear is more skittering. And something else... Explosions,",
        "in the distance..."
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
