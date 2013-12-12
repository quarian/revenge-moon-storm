#include "CampaignGame.hh"
#include "CampaignGameWorld.hh"
#include "StoryScreen.hh"
#include "Fixtures.hh"

#include <string>
#include <vector>

void CampaignGame::showStoryBoss() {
    std::vector<std::string> msg = {
        "As your hands touch the mystical electric vortex, your skin tingling with",
        "the strange cold sensation, you hear a deep, dramatic voice -- except",
        "that it's not really a voice; the words are materializing directly into",
        "your head...",
        "",
        "\"TRESSSPASSSER ISSS ATT THE THRESSHHHOLLLD...\"",
        "",
        "\"YOUU HAVE DUGG INTO THE BRREEDING LAIRRR...\"",
        "",
        "\"YOUU WILL BE OBBLITTTTERATED...\"",
        "",
        "",
        "",
        "You let loose a wordless cry of pure animal hatred: \"Bring it on!\""
    };
    spawn(new StoryScreen(this, msg));
}


void CampaignGame::launchLevelBoss() {
    map_.loadFromFile("./maps/campaign/boss.map", game_.terrainManager_);

    map_.spawnPlayer(player_, 7, 12);
    
    spawn(new CampaignGameWorld(this, map_, player_, flagVictorious_));
}
