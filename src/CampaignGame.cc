#include "CampaignGame.hh"
#include "StoryScreen.hh"
#include "Store.hh"

#include <iostream>
#include <vector>
#include <string>

CampaignGame::CampaignGame(GameState* parent, Player* player) :
        GameState(parent), map_(&game_), player_(player) {}

CampaignGame::CampaignGame(Game& game, GameState*& stack, Player* player) :
        GameState(game, stack), map_(&game_), player_(player) {}


void CampaignGame::init() {
    phase_ = 0;
    player_->setLives(3);
    flagVictorious_ = false;
    storeIsNext_ = false;
    resume();
}


void CampaignGame::resume() {
    std::cout << "Called resume() on CampaignGame, phase is " << phase_ << "\n";

    if (phase_ >= 9) terminate();
    else {
        /* If victorious, advance */
        if (flagVictorious_) {
            flagVictorious_ = false;
            phase_++;
        }

        if (player_->getLives() <= 0) { // Player dead
            death();
        }
        else if (phase_ % 2 == 0) { // Some story phase
            phase_++;
            if (phase_ == 1) showStoryMoonbase();
            else if (phase_ == 3) showStoryMoonbase();
            else if (phase_ == 5) showStoryMoonbase();
            else if (phase_ == 7) showStoryMoonbase();
            else if (phase_ == 9) victory();
        }
        else if (storeIsNext_) { // Some store between game levels
            storeIsNext_ = false;
            spawn(new Store(this, player_));
        }
        else { // Actual game phase
            storeIsNext_ = true;
            if (phase_ == 1) launchLevelMoonbase();
            else if (phase_ == 3) launchLevelTunnels();
            else if (phase_ == 5) launchLevelCaverns();
            else if (phase_ == 7) launchLevelBoss();
        }
    }
}


void CampaignGame::victory() {
    std::vector<std::string> msg = {
        "Victory!"
    };
    spawn(new StoryScreen(this, msg));
}


void CampaignGame::death() {
    phase_ = 9;

    std::vector<std::string> msg = {
        "You have died!"
    };
    spawn(new StoryScreen(this, msg));
}
