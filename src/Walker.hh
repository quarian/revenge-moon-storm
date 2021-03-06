#ifndef MB2_WALKER_HH
#define MB2_WALKER_HH

/*
 * Walker.hh
 *
 * The Walker class represents all creatures (and other objects, such as
 * projectiles) around on the map in a continuous fashion (non-teleporting,
 * block-to-block movement).
 */

#include "Map.hh"
#include "Direction.hh"

#include "Animation.hpp"
#include "AnimatedSprite.hpp"

#include <map>

class Walker {
friend bool WalkerTest1(std::ostream&);

public:
    /* Constructor
     *
     * PARAMETERS
     * ==========
     *  Map const&          map that the Actor is placed on
     *  MapBlock*           initial position on the map
     *  float               movement speed (blocks per second)
     */
    Walker(Map&, MapBlock*, float);
    virtual ~Walker() {}

    /* This is the "full" update function that each inheriting class must
     * implement. It takes the time since the last frame as a parameter.
     * It is called at each game loop cycle AND whenever the Walker reaches
     * its target. */
    virtual void update(float);

    /* Death splatter. */
    virtual void splatter();

    /* Getters:
     *
     * Which way is the Walker facing?
     * Where is the Walker, in relation to the center of the block?
     * What block is the Walker in?
     */
    Direction getDirection() const { return facing_; }
    Direction getPosition() const { return dPos_; }
    MapBlock* getLocation() const { return location_; }
    virtual bool isAlive() const { return true; }

    /* Returns whether the Walker is "going somewhere". */
    bool isMoving() const { return (target_ != nullptr); }
    
    /* Initialize the animations for this Walker's sprite:
     *
     *  Idle
     *  Walking north
     *  Walking east
     *  Walking south
     *  Walking west
     */
    virtual void initSprite(Animation const&, sf::Color);

    /* Returns this Walker's sprite. */
    virtual AnimatedSprite& getSprite() { return sprite_; }



protected:
    /* This is the update function that *only* deals with the Walker's movement
     * from one square to the next. The inheriting class must call this
     * function from its own update() function. */
     void updateLocation(float);

    /* Tries to target the next square in the currently facing direction.
     * Inheriting classes that can dig etc. should override this!
     * This function should only be called when the Walker is already in the
     * center of the current square, otherwise behavior can be strange. */
    virtual void knock(Direction);

    /* Returns true if we are at the center of the square. */
    bool centered() const { return dPos_ == Direction::NULLDIR; }

    /* Movement "in-between" two blocks is understood to happen in such a way
     * that, when the Walker is NOT centered (standing still at the center of
     * its current MapBlock) it will have a distance-from-center in EITHER
     * the x OR the y direction, represented by dPos_;
     *
     *
     *  (-0.5, -0.5)                   (0.5, -0.5)
     *      ################################# 
     *      #               |               # 
     *      #               |               #
     *      #               |               #
     *      #               |               # 
     *      #               |               # 
     *      #         (0, 0)|      -->      # 
     *      #---------------+------W--------# 
     *      #               |               # 
     *      #               |               # 
     *      #               |               #
     *      #               |               #
     *      #               |               # 
     *      #               |               # 
     *      ################################# 
     *  (-0.5, 0.5)                    (0.5, 0.5)
     *
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

    /* Reverses direction. */
    void reverse();

    /* Moves the Walker the center of the block. */
    void center();

    /* Tries to place the Walker at the appropriate edge of the "next"
     * MapBlock. If this fails (which could happen if the target MapBlock has
     * become blocked while the Walker was in-transit), recenters. */
    virtual void proceed();

    Map& map_;

    MapBlock* location_; // Where am I?
    MapBlock* target_; // Where am I going?
    Direction facing_;
    Direction dPos_;

    float speed_;


    /* Animation data.
     *
     * The Walker holds four Animation objects (walking north, walking east,
     * walking south, walking west) and a sprite.
     */
    AnimatedSprite sprite_;

    /* Updates the sprite's position and frame. */
    void updateSprite(float);

    /* Updates the sprite's animation based on its facing etc. */
    void alignSprite();
};

#endif
