#ifndef MB2_AIACTOR_HH
#define MB2_AIACTOR_HH

/*
 * AIActor.hh
 */

#include "Actor.hh"
#include <stack>

class AIActor : public Actor {
public:
    /* Constructor
     *
     * PARAMETERS
     * ==========
     *  Map const&          map that the Actor is placed on
     *  MapBlock*           initial position on the map
     *  float               movement speed (blocks per second)
     *  float               digging power (0.0 if can't dig)
     *  int                 maximum health (also starting health)
     *  float               damage resistance; 0.0 - 1.0
     *  Inventory*          where collected items go -- if nullptr, doesn't collect
     */
    AIActor(Map&, MapBlock*, float, float=0.0, int=100, float=0.0, Inventory* =nullptr);

    /* Functions that AI Actors must implement. */
    virtual void update(float);


protected:
    /* Formulate a plan on what to do next. */
    virtual void think() = 0;

    virtual void findTarget(float);

    /* How long until the next thought? */
    float dThink_;


    /* The AIActor keeps, as a stack of pointers, a sequence of MapBlocks that
     * it is currently walking along. These functions to deal with the path
     * stack. */

    /* Cancels the currently planned path. */
    void cancelPath();

    /* Continue moving along the path. This is the function that findTarget()
     * is meant to call when simply continuing onwards is called for. */
    void popPath(float);
    void pushPath(std::stack<MapBlock*>, int);
    void pushPath(MapBlock*);
    void setPath(std::stack<MapBlock*>, int);

private:
    std::stack<MapBlock*> path_;
};

#endif
