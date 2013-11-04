#ifndef MB2_WALKER_HH
#define MB2_WALKER_HH

/*
 * The Walker class represents all creatures (and other objects, such as
 * projectiles) around on the map in a continuous fashion (non-teleporting,
 * block-to-block movement).
 */

#include "dummy_Map.hh"
#include "dummy_MapBlock.hh"
#include "dummy_Direction.hh"

class Walker {
public:
    /* Constructor: Takes as parameters the Map that it'll be placed on, the
     * specific MapBlock, and the speed at which it will move (units of
     * MapBlocks per second). */
    Walker(Map const&, MapBlock*, float);
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
    Map& map_;
    MapBlock* location_;
    Direction dir_ = Direction::NORTH;

    bool entering_ = false; // Is this Walker entering or leaving the square?
    bool walking_ = false; // Is this Walker in continuous-walking mode?
    float speed_;
    float dx_, dy_;
};

#endif
