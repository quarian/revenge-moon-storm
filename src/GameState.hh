#ifndef MB2_GAMESTATE_HH
#define MB2_GAMESTATE_HH

#include "Game.hh"

/* GameState
 * =========
 *
 * Abstract base class for the different "states" that the game can be in: Main
 * Menu, Store, World, etc.
 */

class Game;

class GameState {
public:
    /* Constructor.
     *
     * Takes a reference to the Game object's pointer to the current GameState
     * as a parameter. Can also be initialized from a previous GameState, which
     * saves one parameter.
     */
    GameState(Game&, GameState*&);
    GameState(GameState*);

    /* The update function drives the main functionality of this game state. It
     * takes the elapsed time dt, in seconds, as a parameter.
     */
    virtual void update(float) = 0;

    /* Functions to handle whatever initial work needs to be done when this
     * game state receives control. init() is called when this object has just
     * been spawned; resume() is called on termination of a child state.
     */
    virtual void init() = 0;
    virtual void resume() = 0;


protected:
    /* The main game object, used to get access to graphics, terrain, etc.
     * manager objects.
     */
    Game& game_;

    /* The top of the state stack. */
    GameState*& stack_;

    /* Spawn a child state and give it control. */
    void spawn(GameState*);

    /* Terminate this state and give control to the parent (unless this is the
     * root state).
     */
    void terminate();


private:
    /* The previous game state. */
    GameState* parent_;
};

#endif
