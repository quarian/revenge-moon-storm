#include "Actor.hh"


class ControlledActor : public Actor {
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
    ControlledActor(Map&, MapBlock*, float, float, int, float);
    ~ControlledActor();


    /* Tells the Actor when orders to move in some direction start/stop. */
    void keyDown(Direction);
    void keyUp(Direction);
    void setKey(Direction, bool);

protected:
    /* Contains information on what keys are down. */
    bool northKeyDown_;
    bool eastKeyDown_;
    bool southKeyDown_;
    bool westKeyDown_;

    /* What's the currently "active" keypress? If multiple keys are
     * simultaneously down, this is the MOST RECENTLY depressed key. If the
     * most recent key is released, if some other key remains depressed, it
     * becomes the active order (the keys are checked in order NESW). */
    Direction orders_;

    void findTarget(float); // Overridden
};
