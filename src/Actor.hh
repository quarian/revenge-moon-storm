#ifndef MB2_ACTOR_HH
#define MB2_ACTOR_HH

/*
 * Actor.hh
 */

#include "Walker.hh"

class Actor : public Walker {
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
     */
    Actor(Map const&, MapBlock*, float, float, int, float);
    ~Actor();

    /* Deals the given "raw" damage to this Actor, then return true if it
     * survives. */
    virtual bool takeDamage(int);

    /* Returns whether this Actor is still alive. */
    bool isAlive() const { return health_ > 0; }

    /* Returns true if the Actor is able to dig. */
    bool isDigger() const { return digPower_ > 0; }

    virtual void update(float); // Overridden


protected:
    virtual void knock(Direction); // Overridden
    virtual void findTarget(float dt) {}
    void dig(float);


private:
    bool digging_;
    float digPower_;
    int health_;
    int maxHealth_;
    float vulnerability_;
};

#endif
