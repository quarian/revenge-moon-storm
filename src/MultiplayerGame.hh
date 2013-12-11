#ifndef MB2_NPGAME_HH
#define MB2_NPGAME_HH

#include <vector>
#include <set>

#include "GameState.hh"
#include "GlobalGameInterface.hh"
#include "Map.hh"
#include "Actor.hh"
#include "MapBlock.hh"
#include "Item.hh"

/* SinglePlayerGame
 * ================
 *
 * High-level flow control of a single player game: spawns a store and then a
 * game world.
 */


class MultiplayerGame : public GameState {
public:
     MultiplayerGame(GameState*, std::vector<Player*>, std::string mapName_);
     MultiplayerGame(Game&, GameState*&, std::vector<Player*>, std::string mapName);

    /* The update function drives the main functionality of this game state. It
     * takes the elapsed time dt, in seconds, as a parameter.
     */
    void update(float);

    /* Functions to handle whatever initial work needs to be done when this
     * game state receives control. init() is called when this object has just
     * been spawned; resume() is called on termination of a child state.
     */
    void init();
    void resume();


private:
    Map map_;
    std::vector<Player*> players_;
    std::string mapName_;
};

#endif
