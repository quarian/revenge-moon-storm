#ifndef MB2_WORLD_HH
#define MB2_WORLD_HH

#include <vector>

#include "GameState.hh"
#include "Map.hh"

/* GameState
 * =========
 *
 * Abstract base class for the different "states" that the game can be in: Main
 * Menu, Store, World, etc.
 */

class World : public GameState {
public:
    /* Constructor.
     *
     * Takes a reference to the Game object's pointer to the current GameState
     * as a parameter.
     */
     World(GameState*, Map&, std::vector<Player*>);

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
    Map& map_;
    std::vector<Player*> players_;
};

#endif
