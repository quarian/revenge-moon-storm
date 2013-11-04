#ifndef MB2_ACTOR_HH
#define MB2_ACTOR_HH

/*
 * Actor.hh
 */

#include "Walker.hh"

class Actor : public Walker {
public:
    /* Constructor: takes as parameters the Map that the Actor is placed on,
     * the specific MapBlock, the speed at which the actor will move on the
     * map its health and its damage resistance (as a fraction of damage
     * reduced, e.g., if 0.35 is given, the Actor suffers only 65% of the raw
     * damage dealt to it. This assumes that the health is full when the Actor
     * is initialized, that is, the maximum health is set to the initial
     * health. */
    Actor(Map const&, MapBlock*, float, int, float);
    ~Actor();

    /* Deals the given "raw" damage to this Actor, then return true if it
     * survives. */
    virtual bool takeDamage(int dmg) { health_ -= dmg * vulnerability_; }

    /* Returns whether this Actor is still alive. */
    bool isAlive() const { return health_ > 0; }

private:
    int health_;
    int maxHealth_;
    float vulnerability_;
};

#endif
