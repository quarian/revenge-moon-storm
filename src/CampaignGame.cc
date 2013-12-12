#include "CampaignGame.hh"
#include "DummyGameState.hh"
#include "Store.hh"

#include <iostream>

CampaignGame::CampaignGame(GameState* parent, Player* player) :
        GameState(parent), map_(&game_), player_(player) {}

CampaignGame::CampaignGame(Game& game, GameState*& stack, Player* player) :
        GameState(game, stack), map_(&game_), player_(player) {}


void CampaignGame::init() {
    phase_ = 1;
    player_->setLives(3);
    flagVictorious_ = false;
    storeIsNext_ = false;
    resume();
}


void CampaignGame::resume() {
    std::cout << "Called resume() on CampaignGame, phase is " << phase_ << "\n";

    if (phase_ >= 6) terminate();
    else {
        /* If the player won the last round, move on to the next phase */
        if (flagVictorious_) {
            flagVictorious_ = false;
            phase_ += 1;
        }

        /* If out of lives, exit */
        if (player_->getLives() <= 0) {
            phase_ = 6; // telophase!
            death();
            // terminate();
        }
        /* If the player has beat all the levels */
        else if (phase_ == 5) {
            phase_++;
            victory();
        }

        else if (storeIsNext_) {
            storeIsNext_ = false;
            spawn(new Store(this, player_)); // TODO: replace with Store
        } else {
            storeIsNext_ = true;
            if (phase_ == 1) launchLevelMoonbase();
            else if (phase_ == 2) launchLevelTunnels();
            else if (phase_ == 3) launchLevelCaverns();
            else if (phase_ == 4) launchLevelBoss();
        }
    }
}


void CampaignGame::victory() {
    spawn(new DummyGameState(this));
}


void CampaignGame::death() {
    spawn(new DummyGameState(this));
}
