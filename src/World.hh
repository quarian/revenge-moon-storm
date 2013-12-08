#ifndef MB2_WORLD_HH
#define MB2_WORLD_HH

#include <vector>
#include <set>

#include "GameState.hh"
#include "GlobalGameInterface.hh"
#include "Map.hh"
#include "Actor.hh"
#include "MapBlock.hh"
#include "Item.hh"
#include "WorldGUI.hh"

/* World
 * =====
 *
 * Game world state. This is the game "in action", that is, players move around
 * and collect treasures and all that.
 */

class World : public GameState {
public:
     World(GameState*, Map&, std::vector<Player*>);
     World(Game&, GameState*&, Map&, std::vector<Player*>);

    /* The update function drives the main functionality of this game state. It
     * takes the elapsed time dt, in seconds, as a parameter.
     */
    virtual void update(float);

    /* Functions to handle whatever initial work needs to be done when this
     * game state receives control. init() is called when this object has just
     * been spawned; resume() is called on termination of a child state.
     */
    void init();
    void resume();

    void pause();


protected:
    Map& map_;
    std::vector<Player*> players_;
    WorldGUI gui_;

    void cull();
    void updateAll(float);
    void drawMapObjects();
    void drawGUI();

    void initKeyboard();
};

#endif
