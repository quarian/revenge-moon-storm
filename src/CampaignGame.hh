#ifndef MB2_CAMPAIGNGAME_HH
#define MB2_CAMPAIGNGAME_HH

#include "GameState.hh"

/* CampaignGame
 * ============
 *
 * This is the game's "Story Mode". The campaign consists of four maps, with
 * a Store (workshop) screen between maps.
 */

class CampaignGame : public GameState {
public:
    CampaignGame(GameState*, Player*);
    CampaignGame(Game&, GameState*&, Player*);

    /* There is no update for this GameState, since it is an orchestrating
     * state which does not actually take any input itself. Everything happens
     * in the init() and resume() methods.
     */
    void update(float) {}

    void init();
    void resume();

    void launchLevelMoonbase();
    void launchLevelTunnels();
    void launchLevelCaverns();
    void launchLevelBoss();

    void showStoryMoonbase();
    void showStoryTunnels();
    void showStoryCaverns();
    void showStoryBoss();

    void victory();

private:
    Map map_;
    Player* player_;
    int phase_;
    bool storeIsNext_;
};


/* STORY PANES */
class StoryPane1 : public GameState {
};

#endif
