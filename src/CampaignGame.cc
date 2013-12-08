#include "CampaignGame.hh"
#include "DummyGameState.hh"

CampaignGame::CampaignGame(GameState* parent, Player* player) :
        GameState(parent), map_(&game_), player_(player) {}

CampaignGame::CampaignGame(Game& game, GameState*& stack, Player* player) :
        GameState(game, stack), map_(&game_), player_(player) {}


void CampaignGame::init() {
    phase_ = 1;
    storeIsNext_ = false;
    showStoryMoonbase();
}


void CampaignGame::resume() {
    if (phase_ == 2)
        terminate();

    if ((phase_ % 2) == 0) {
        phase_++;

        if (phase_ == 2) showStoryTunnels();
        else if (phase_ == 4) showStoryCaverns();
        else if (phase_ == 6) showStoryBoss();
        else if (phase_ == 8) victory();
    } else {
        if (storeIsNext_) {
            storeIsNext_ = false;
            spawn(new DummyGameState(this)); // TODO: replace with Store
        } else {
            //storeIsNext_ = true;
            if (phase_ == 1) launchLevelMoonbase();
            else if (phase_ == 3) launchLevelTunnels();
            else if (phase_ == 5) launchLevelCaverns();
            else if (phase_ == 7) launchLevelBoss();
        }
    }
}


void CampaignGame::victory() {
    spawn(new DummyGameState(this));
}
