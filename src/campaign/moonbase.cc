#include "CampaignGame.hh"
#include "CampaignGameWorld.hh"
#include "StoryScreen.hh"
#include "Fixtures.hh"
#include "Item.hh"

#include <string>
#include <vector>


void CampaignGame::showStoryMoonbase() {
    std::vector<std::string> msg = {
        "The year is 2061.",
        "",
        "You, " + player_->getName() + ", are an excavation worker at the New",
        "Thiggrinc lunar mining colony, where the crew works day and night",
        "to provide the precious element MacGuffinium that powers the entire",
        "world economy.",
        "",
        "One night when you're sleeping peacefully in your quarters, a loud CRASH",
        "awakens you. There is a faint skittering and a hissing in the walls, but",
        "otherwise it is quiet -- too quiet. The ominous feeling grows as you",
        "hastily don your space suit. Digits flash red on the visor of your",
        "helmet:",
        "",
        "03:57",
        "",
        "The night shift should be having dinner in the next room, yet you hear",
        "nothing... protocol is to gather in the northeast mine tunnels in the",
        "case of an emergency. Maybe they're there. They must be. But something",
        "is telling you this is not the case...",
        "",
        "Fearing the worst, you grab your pack of explosives and head out."
    };
    spawn(new StoryScreen(this, msg));
}


void CampaignGame::launchLevelMoonbase() {
    map_.loadFromFile("./maps/campaign/moonbase.map", game_.terrainManager_);

    // Essential elements
    map_.spawnPlayer(player_, 4, 3);
    new Fixtures::LevelExit(map_, map_.getBlock(62, 1), flagVictorious_, {player_});

    spawn(new CampaignGameWorld(this, map_, player_, flagVictorious_));
}
