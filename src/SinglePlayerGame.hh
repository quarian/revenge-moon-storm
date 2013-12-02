#ifndef MB2_1PGAME_HH
#define MB2_1PGAME_HH

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


class SinglePlayerGame : public GameState {
public:
     SinglePlayerGame(GameState*, Player*);
     SinglePlayerGame(Game&, GameState*&, Player*);

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
    Player* player_;
};

#endif
