#ifndef MB2_AIACTOR_HH
#define MB2_AIACTOR_HH

/*
 * AIActor.hh
 */

#include "Actor.hh"
#include <stack>

class AIActor : public Actor {
public:
    using Actor::Actor;

protected:
    /* Formulate a plan on what to do next. */
    virtual void think() = 0;

    /* Functions that AI Actors must implement. */
    virtual void update(float);
    virtual void findTarget(float);

    std::stack<MapBlock*> path;
};

#endif
