#ifndef MB2_WALKER_HH
#define MB2_WALKER_HH

/*
 * The Walker class represents all creatures (and other objects, such as
 * projectiles) around on the map in a continuous fashion (non-teleporting,
 * block-to-block movement).
 */

#include "Map.hh"
#include "MapBlock.hh"

class Walker {
public:
    /* Constructor: Takes as parameters the Map that it'll be placed on, the
     * specific MapBlock, and the speed at which it will move (units of
     * MapBlocks per second). */
    Walker(Map&, MapBlock*, float);
    ~Walker();

    /* Returns a pointer to the MapBlock that the Walker is currenly
     * occupying, or null if it is not on the Map. */
    MapBlock* getLocation() const { return location_; }

    /* This is the update function that *only* deals with the Walker's movement
     * from one square to the next. The inheriting class must call this
     * function from its own update() function. */
     void updateLocation(float);

    /* This is the "full" update function that each inheriting class must
     * implement. It takes the time since the last frame as a parameter. */
    virtual void update(float) = 0;

     /* Changes the direction that the Walker is facing to the given value. */
     void setDirection(Direction);

    /* Returns the direction in which the Walker is facing. */
     Direction getDirection() const { return dir_; }

     /* Controls whether the Walker is moving or not. */
     void walk() { walking_ = true; }
     void stop() { walking_ = false; }


private:
    /* Movement "in-between" two blocks is understood to happen in such a way
     * that, when the Walker is NOT centered (standing still at the center of
     * its current MapBlock) it will have a distance-from-center in EITHER
     * the x OR the y direction, represented by dx_ and dy_:
     *
     *  (-0.5, -0.5)                   (0.5, -0.5)
     *      #################################     -
     *      #               |               #      |
     *      #               |               #      |  negative
     *      #               |               #      |    dy_
     *      #               |               #      |
     *      #               |               #      |
     *      #         (0, 0)|      -->      #      |
     *      #---------------+------W--------#     -
     *      #               |               #      |
     *      #               |               #      |
     *      #               |               #      |  positive
     *      #               |               #      |    dy_
     *      #               |               #      |
     *      #               |               #      |
     *      #################################     -
     *  (-0.5, 0.5)                    (0.5, 0.5)
     *
     *      '_______________'_______________'
     *
     *          negative        positive
     *            dx_             dx_
     *
     * In the figure above, the Walker W is moving towards the right ("EAST"),
     * incrementing its dx_ by an appropriate amount each turn. The Walker
     * keeps track of whether it is moving towards or away from the center,
     * and increments or decrements its coordinates with approach(dt) or
     * depart(dt), whichever is appropriate.
     *
     * When the Walker reaches the center of its MapBlock, it "knocks" on the
     * next MapBlock (unless ordered to stop moving). knock() determines
     * whether it is possible to move to the next MapBlock, mine it, or do
     * some other operation on it. Similarly, when an EDGE is reached (some
     * coordinate reaches magnitude 0.5), the Walker attempts to move into
     * the next MapBlock. 
     */

    /* Moves towards the center of the current block, according to the given
     * delta-time. This function assumes that the dt given is less than or
     * equal to the time required to get to the center of the block, that is,
     * it assumes that the progress will not lead to the Walker actually
     * reaching the center. */
    void approach(float);

    /* Moves away from the center of the current block, according to the given
     * delta-time. This assumes that the dt is not large enough for the Walker
     * to actually leave the square. */
    void depart(float);

    /* Moves to the center of the block. */
    void center();

    /* Tries to place the Walker at the appropriate edge of the "next"
     * MapBlock. */
    void proceed();

    /* Starts mowing into the next square in the currently facing direction.
     * Inheriting classes that can dig etc. should override this! */
    virtual void knock(float);

    /* Returns true if the Walker is currently at the center of its block. */
    bool centered() const { return dx_ == 0 && dy_ == 0; }

    Map& map_;
    MapBlock* location_;
    Direction dir_;
    MapBlock* target_;

    bool entering_; // Is this Walker entering or leaving the square?
    bool walking_; // Is this Walker in continuous-walking mode?
    float speed_;
    float dx_, dy_;
};

#endif
