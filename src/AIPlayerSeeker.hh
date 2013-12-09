#ifndef MB2_AIPLAYERSEEKER_HH
#define MB2_AIPLAYERSEEKER_HH

/*
 * AIPlayerSeeker.hh
 *
 * A type of AI actor that just finds the nearest Player and plots a path to it.
 *
 * When this monster enters a MapBlock inhabited by a Player, it deals a fixed
 * amount of daamge to it.
 */

#include "AIActor.hh"
#include "AStar.hh"

class AIPlayerSeeker : public AIActor {
public:
    /* Constructor
     *
     * PARAMETERS
     * ==========
     *  Map const&          map that the Actor is placed on
     *  MapBlock*           initial position on the map
     *  float               damage (per hit)
     *  float               movement speed (blocks per second)
     *  int                 maximum health (also starting health)
     *  int                 line of sight (player detect)
     */
    AIPlayerSeeker(Map&, MapBlock*, float=15, float=10.0, int=50, int=10);


protected:
    float damage_;
    int LOS_;
    int LOS2_;

    float queuedSleep_;
    void queueSleep();

    /* Formulate a plan on what to do next. */
    virtual void think();

    /* Overridden to enable damage dealing. */
    virtual void proceed();

    /* How many steps to plan ahead if the target player is at the given
     * distance? */
    virtual int planPathLength(float) const;
};

#endif
